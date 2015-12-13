/*
 * branch.c
 *
 *  Created on: Aug 27, 2012
 *      Author: kevin
 */

#include "cpu6502.h"
#include "branch.h"

void do_branch(addr)
{
	if (addr & 0x80) {
		cpu->pc += (0xFF00 | addr);
	} else {
		cpu->pc += addr;
	}
}

void branch_if(uint8_t field, bool is_set)
{
	uint8_t  addr;

	addr = get_immediate();
	cpu->pc += 2;
	if (is_set == status_is_set(&cpu->status, field)) {
		do_branch(addr);
	}
}

void bcs(void)
{
	branch_if(ST_CARRY, TRUE);
}

void bcc(void)
{
	branch_if(ST_CARRY, FALSE);
}

void beq(void)
{
	branch_if(ST_ZERO, TRUE);
}

void bne(void)
{
	branch_if(ST_ZERO, FALSE);
}

void bmi(void)
{
	branch_if(ST_NEG, TRUE);
}

void bpl(void)
{
	branch_if(ST_NEG, FALSE);
}

void bvs(void)
{
	branch_if(ST_OVRFL, TRUE);
}
void bvc(void)
{
	branch_if(ST_OVRFL, FALSE);
}


