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
	cpu->ac = stack_pop();
}

void plp(void)
{
	cpu->status = stack_pop();
}
