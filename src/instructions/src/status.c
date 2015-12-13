/*
 * status.c
 *
 *  Created on: Aug 27, 2012
 *      Author: kevin
 */

#include "cpu6502.h"
#include "status.h"

void clc(void)
{
	status_reg_clr(&cpu->status, ST_CARRY);
}

void cld(void)
{
	status_reg_clr(&cpu->status, ST_DEC);
}

void cli(void)
{
	status_reg_clr(&cpu->status, ST_IRQ);
}

void clv(void)
{
	status_reg_clr(&cpu->status, ST_OVRFL);
}

void sec(void)
{
	status_reg_set(&cpu->status, ST_CARRY);
}

void sed(void)
{
	status_reg_set(&cpu->status, ST_DEC);
}

void sei(void)
{
	status_reg_set(&cpu->status, ST_IRQ);
}
