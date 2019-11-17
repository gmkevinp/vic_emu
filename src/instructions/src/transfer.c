/*
 * transfer.c
 *
 *  Created on: Aug 27, 2012
 *      Author: kevin
 */
#include "cpu6502.h"
#include "transfer.h"

static void set_status(uint8_t val)
{
	uint8_t  flags;

	flags = (val)? 0: ST_ZERO;
	flags |= (val & 0x80)? ST_NEG: 0;
	status_reg_mask_and_set(&cpu->status,
							ST_ZERO | ST_NEG,
							flags);
}

void tax(void)
{
	cpu->x = cpu->ac;
	set_status(cpu->x);
}

void tay(void)
{
	cpu->y = cpu->ac;
	set_status(cpu->y);
}

void tsx(void)
{
	cpu->x = cpu->sp;
	set_status(cpu->x);
}

void txa(void)
{
	cpu->ac = cpu->x;
	set_status(cpu->ac);
}

void txs(void)
{
	cpu->sp = cpu->x;
}

void tya(void)
{
	cpu->ac = cpu->y;
	set_status(cpu->ac);
}

