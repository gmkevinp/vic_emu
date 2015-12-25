/*
 * stack.c
 *
 *  Created on: Aug 29, 2012
 *      Author: kevin
 */
#include "cpu6502.h"
#include "stack.h"

void pha(void)
{
	stack_push(cpu->ac);
}

void php(void)
{
	stack_push(cpu->status);
}

void pla(void)
{
	status_reg_t  flags;

	cpu->ac = stack_pop();

	flags = (!cpu->ac) ? ST_ZERO: 0;
	flags |= (cpu->ac & 0x80) ? ST_NEG: 0;
	status_reg_mask_and_set(&cpu->status, ST_ZERO | ST_NEG, flags);
}

void plp(void)
{
	status_reg_mask_and_set(&cpu->status, 0xFF, stack_pop());
}
