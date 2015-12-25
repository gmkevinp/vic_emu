/*
 * brk.c
 *
 *  Created on: Aug 26, 2012
 *      Author: kevin
 */
#include <stdio.h>
#include "cpu6502.h"
#include "brk.h"

void brk(void)
{
	uint16_t  ret_addr;
	uint16_t  jmp_addr;
	uint16_t  addr_hi;
	uint16_t  addr_lo;

	status_reg_set(&cpu->status, ST_BRK);

	/* Save return address to stack */
	ret_addr = (cpu->pc+2);
	addr_hi = (ret_addr & 0xFF00) >> 8;
	addr_lo = (ret_addr & 0x00FF);
	stack_push(addr_hi);
	stack_push(addr_lo);
	stack_push(cpu->status);

	jmp_addr = mem_read16(cpu->mem, 0xFFFE);
	pc_reg_set(&cpu->pc, jmp_addr);
}
