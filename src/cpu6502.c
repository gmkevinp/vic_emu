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
#include "branch.h"

cpu6502_st *cpu;

static uint16_t vic_scrn_2_ascii(uint8_t c) {
	if (c < 27) {
		return ('@' + c);
	} else {
		return c;
	}
}

static void cpu6502_dump_screen(void)
{
	uint16_t   screen;
	uint8_t    row;
	uint8_t    col;

	screen = cpu->mem->ram[0x288] << 8;
	printf ("Screen Memory: 0x%04X\n", screen);
	for (row = 0; row < 23; row++) {
		for (col = 0; col < 22; col++) {
			uint8_t  byte;
			byte = cpu->mem->ram[screen++];
			printf ("%c", vic_scrn_2_ascii(byte));
		}
		printf ("\n");
	}
}

static void cpu6502_where(cpu6502_st *cpu)
{
//	static bool started = FALSE;

	switch (cpu->pc) {
	case 0xFD22:
//		cpu->trace = 1;
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
		cpu->trace = 1;
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

//		if (!started) {
//			cpu->pc = 0x400; // Run 6502 Functional test
//			started = TRUE;
//		} else {
//			cpu6502_halt("Finished startup\n");
//		}
		break;
	case 0xE404:
		printf ("Print startup message\n");
		break;
	case 0xDDDF:
		printf ("Print FAC1\n");
		printf ("0x61: 0x%02X\n", cpu->mem->ram[0x61]);
		printf ("0x62: 0x%02X\n", cpu->mem->ram[0x62]);
		printf ("0x63: 0x%02X\n", cpu->mem->ram[0x63]);
		printf ("0x64: 0x%02X\n", cpu->mem->ram[0x64]);
		printf ("0x65: 0x%02X\n", cpu->mem->ram[0x65]);
		printf ("0x66: 0x%02X\n", cpu->mem->ram[0x66]);
//		cpu->mem->ram[0x61] = 0x82;
//		cpu->mem->ram[0x62] = 0x40;
//		cpu->mem->ram[0x63] = 0x00;
//		cpu->mem->ram[0x64] = 0x00;
//		cpu->mem->ram[0x65] = 0x00;
//		cpu->mem->ram[0x66] = 0x00;
		break;
	default:
		break;
	}
}

static void cpu6502_trace(inst_db_entry_st *op_data)
{
	uint16_t          arg16;
	uint8_t           arg8;
	uint8_t          *pc;
	char              tmp[20];

	pc = &cpu->mem->ram[cpu->pc];
	fprintf (cpu->ofp, "0x%04X: ", cpu->pc);

	switch (op_data->sz) {
		case 1:
			fprintf (cpu->ofp, "%02X       %-15s", *pc, op_data->format);
			break;

		case 2:
			arg8 = mem_bd_read8(cpu->mem, cpu->pc + 1);
			if (is_branch_op(op_data->opcode)) {
				arg16 = calc_branch_addr(cpu->pc, arg8);
				sprintf (tmp, op_data->format, arg16);
			} else {
				sprintf (tmp, op_data->format, arg8);
			}
			fprintf (cpu->ofp, "%02X %02X    %-15s", *pc, *(pc+1), tmp);
			break;

		case 3:
			arg16 = mem_bd_read16(cpu->mem, cpu->pc + 1);
			sprintf (tmp, op_data->format, arg16);
			fprintf (cpu->ofp, "%02X %02X %02X %-15s", *pc, *(pc+1), *(pc+2), tmp);
			break;
	}
	fprintf (cpu->ofp, "\tSR:%02X AC:%02X X:%02X Y:%02X SP:%02X",
			cpu->status, cpu->ac, cpu->x, cpu->y, cpu->sp);
	fprintf (cpu->ofp, "\tRD: 0x%04X: 0x%02X; WR: 0x%04X: 0x%02X\n",
			cpu->mem->last_rd_addr, cpu->mem->last_rd_val,
			cpu->mem->last_wr_addr, cpu->mem->last_wr_val);

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
//	if (cpu->n_inst == 1250000) {
	if (cpu->n_inst == 1500000) {
		cpu6502_halt("Hit Instruction Limit");
	}
}

static inst_db_entry_st *cpu6502_fetch(void)
{
	uint8_t opcode;

	opcode = mem_bd_read8(cpu->mem, cpu->pc);
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

	cpu->ofp = fopen("trace", "w");
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
