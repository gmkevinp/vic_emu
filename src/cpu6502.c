/*
 * cpu6502.c
 *
 *  Created on: Aug 26, 2012
 *      Author: kevin
 */
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "cpu6502.h"
#include "inst_db.h"

cpu6502_st *cpu;

static void cpu6502_dump_screen(void)
{
	uint16_t   addr;
	uint8_t    row;
	uint8_t    col;

	addr = 7680;
	for (row = 0; row <= 23; row++) {
		for (col = 0; col <= 22; col++) {
			uint8_t  byte;
			byte = cpu->mem->ram[addr++];
			printf ("%02X", byte);
		}
		printf ("\n");
	}
}

static void cpu6502_where(cpu6502_st *cpu)
{
	switch (cpu->pc) {
	case 0xFD22:
		printf ("Start up\n");
		break;
	case 0xFD52:
		printf ("Restore I/O vectors\n");
		break;
	case 0xFDF9:
		printf ("Initialize I/O Registers\n");
		break;
	case 0xFDEB:
		cpu6502_halt("Memory Check Infinite Loop");
		break;
	case 0xFD8D:
		printf ("Initialize Low RAM (0x0000-0x03FF)\n");
		break;
	case 0xFDAD:
		printf ("RAM Test starting...\n");
		break;
	case 0xE518:
		printf ("Initialize Hardware\n");
		break;
	case 0xE378:
		printf ("BASIC start\n");
		break;
	case 0xE64F:
		printf ("Write char and Wait for key\n");
		cpu6502_dump_screen();
		break;
	default:
		break;
	}
}

static void cpu6502_trace(inst_db_entry_st *op_data)
{
	uint16_t          arg16;
	uint8_t           arg8;
	char              tmp[20];

	fprintf (cpu->ofp, "0x%08X - 0x%04X: ", cpu->n_inst, cpu->pc);

	switch (op_data->sz) {
		case 1:
			fprintf (cpu->ofp, "%-15s", op_data->format);
			break;

		case 2:
			arg8 = mem_read8(cpu->mem, cpu->pc + 1);
			sprintf (tmp, op_data->format, arg8);
			fprintf (cpu->ofp, "%-15s", tmp);
			break;

		case 3:
			arg16 = mem_read16(cpu->mem, cpu->pc + 1);
			sprintf (tmp, op_data->format, arg16);
			fprintf (cpu->ofp, "%-15s", tmp);
			break;
	}
	fprintf (cpu->ofp, "\tSR:%02X AC:%02X X:%02X Y:%02X SP:%02X C1:%02X C2:%02X ($C1):%02X\n",
			cpu->status, cpu->ac, cpu->x, cpu->y, cpu->sp,
			cpu->mem->ram[0xC1], cpu->mem->ram[0xC2], cpu->mem->ram[mem_read16(cpu->mem, 0xC1)]);
}

static void cpu6502_do_inst(inst_db_entry_st *op_data)
{
	cpu6502_where(cpu);
	if (cpu->trace) {
		cpu6502_trace(op_data);
	}
	op_data->func();
	op_data->exec_count++;
	if (op_data->pc_adv) {
		pc_reg_inc(&cpu->pc, op_data->sz);
	}
	cpu->n_inst++;
	if (cpu->n_inst == 1250000) {
		cpu6502_halt("Hit Instruction Limit");
	}
}

static inst_db_entry_st *cpu6502_fetch(void)
{
	uint8_t opcode;

	opcode = mem_read8(cpu->mem, cpu->pc);
	return &cpu->inst.inst_data[opcode];
}

void cpu6502_halt(const char* str)
{
	printf ("Halt: %s\n", str);
	cpu->halt = 1;

//	cpu6502_dump_inst_exec_count(cpu);
	cpu6502_dump(cpu);
}

void cpu6502_init(cpu6502_st *cpu_in, mem_st *mem)
{
	cpu = cpu_in;
	memset(cpu, 0, sizeof(*cpu));
	status_reg_init(&cpu->status);
	stack_init();
	cpu_in->mem = mem;
	inst_init(&cpu->inst);
	pc_reg_init(&cpu->pc, cpu->mem);
}

void cpu6502_dump(cpu6502_st *cpu)
{
	printf ("   PC  SR AC XR YR SP\n");
	printf ("; %04X %02X %02X %02X %02X %02X\n",
			cpu->pc, cpu->status, cpu->ac, cpu->x, cpu->y, cpu->sp);
//	mem_dump(cpu->mem);
}

void cpu6502_dump_inst_exec_count(cpu6502_st *cpu)
{
	uint8_t op;

	for (op = 0; op < 0xFF; op++) {
		inst_db_entry_st *op_data;

		op_data = &cpu->inst.inst_data[op];
		if (op_data->exec_count) {
			printf("%d: %6d %-15s\n", op, op_data->exec_count, op_data->format);
		}
	}
}

void cpu6502_run(cpu6502_st *cpu)
{
	cpu->ofp = fopen("trace", "w");
	while (!cpu->halt) {
		cpu6502_clk();
	}
}

void cpu6502_step(void)
{
	inst_db_entry_st *op_data;

	op_data = cpu6502_fetch();
	cpu6502_do_inst(op_data);
}

void cpu6502_clk(void)
{
	inst_db_entry_st *op_data;

	if (!cpu->wait_cycles) {
		cpu6502_step();
		op_data = cpu6502_fetch();
		cpu->wait_cycles = op_data->n_cycles;
	}
	cpu->wait_cycles--;
}
