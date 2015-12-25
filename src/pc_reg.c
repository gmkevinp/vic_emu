/*
 * pc_reg.c
 *
 *  Created on: Aug 26, 2012
 *      Author: kevin
 */
#include <stdio.h>
#include "pc_reg.h"
#include "mem.h"

void pc_reg_init(pc_reg_t *pc, mem_st *mem)
{
	uint16_t  addr;

	addr = mem_bd_read8(mem, 0xFFFD) << 8 |
		   mem_bd_read8(mem, 0xFFFC);

	*pc = addr;
}

void pc_reg_dump(pc_reg_t *pc)
{
	printf("PC: 0x%04X\n", *pc);
}

void pc_reg_inc(pc_reg_t *pc, uint8_t bytes)
{
	*pc = *pc + bytes;
}

void pc_reg_set(pc_reg_t *pc, uint16_t addr)
{
	*pc = addr;
}
