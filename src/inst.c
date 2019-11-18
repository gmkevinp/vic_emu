/*
 * inst.c
 *
 *  Created on: Aug 26, 2012
 *      Author: kevin
 */
#include <stdio.h>
#include <stdlib.h>
#include "cpu6502.h"
#include "inst.h"
#include "inst_db.h"

void unsupported_opcode(void);

static inst_db_entry_st unsupported =
{ .sz = 1, .format = "???", .func = unsupported_opcode, };

void unsupported_opcode(void)
{
    uint8_t  opcode;

    opcode = mem_bd_read8(cpu->mem, cpu->pc);
    printf ("[0x%04X]: 0x%02X - WARNING: Unknown opcode\n", cpu->pc, opcode);
    cpu6502_halt("Unsupport opcode");
}

void inst_init(inst_st *inst)
{
    uint16_t  i;
    uint16_t  opcode;

    for (opcode = 0; opcode <= 255; opcode++) {
        inst->inst_data[opcode] = unsupported;
    }
    for (i=0; i<inst_db_num_entries; i++) {
        inst->inst_data[inst_db[i].opcode] = inst_db[i];
    }
}

uint8_t get_immediate(void)
{
    return mem_bd_read8(cpu->mem, cpu->pc + 1);
}

uint16_t get_zero_page_addr(uint8_t offset)
{
    uint8_t      addr;

    addr = mem_bd_read8(cpu->mem, cpu->pc + 1);
    return ((addr + offset) & 0xFF);
}

uint16_t get_indirect_addr(void)
{
    uint16_t     addr;

    addr = mem_bd_read16(cpu->mem, cpu->pc + 1);
    addr = mem_bd_read16(cpu->mem, addr);
    return  addr;
}

uint16_t get_absolute_addr(uint8_t offset)
{
    uint16_t     addr;

    addr = mem_bd_read16(cpu->mem, cpu->pc + 1);
    return  addr + offset;
}

uint16_t get_indirect_x_addr(void)
{
    uint16_t      addr;
    uint8_t       addr_hi;
    uint8_t       addr_lo;

    addr = mem_bd_read8(cpu->mem, cpu->pc + 1);
    addr = ((addr + cpu->x) & 0xFF);
    addr_lo = mem_bd_read8(cpu->mem, addr);
    addr_hi = mem_bd_read8(cpu->mem, addr + 1);
    addr = (addr_hi << 8) | addr_lo;
    return addr;
}

uint16_t get_indirect_y_addr(void)
{
    uint16_t      addr;

    addr = mem_bd_read8(cpu->mem, cpu->pc + 1);
    addr = mem_bd_read16(cpu->mem, addr) + cpu->y;
    return addr;
}
