/*
 * load.c
 *
 *  Created on: Aug 29, 2012
 *      Author: kevin
 */

#include <stdlib.h>
#include <stdio.h>
#include "cpu6502.h"
#include "load.h"

static uint8_t load_val(uint8_t val)
{
	status_reg_t  flags;

	flags = (!val) ? ST_ZERO: 0;
	flags |= (val & 0x80) ? ST_NEG: 0;
	status_reg_mask_and_set(&cpu->status, ST_ZERO | ST_NEG, flags);

	return val;
}

static uint8_t load_mem(uint16_t addr)
{
	uint8_t       val;

	val = mem_read8(cpu->mem, addr);
	return load_val(val);
}

void lda_immediate(void)
{
	uint8_t      val;

	val = get_immediate();
	cpu->ac = load_val(val);
}

void lda_zero_page(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(0);
	cpu->ac = load_mem(addr);
}

void lda_zero_page_x(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(cpu->x);
	cpu->ac = load_mem(addr);
}

void lda_absolute(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(0);
	cpu->ac = load_mem(addr);
}

void lda_absolute_x(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(cpu->x);
	cpu->ac = load_mem(addr);
}

void lda_absolute_y(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(cpu->y);
	cpu->ac = load_mem(addr);
}

void lda_indirect_x(void)
{
	uint16_t  addr;

	addr = get_indirect_x_addr();
	cpu->ac = load_mem(addr);
}

void lda_indirect_y(void)
{
	uint16_t  addr;

	addr = get_indirect_y_addr();
	cpu->ac = load_mem(addr);
//	printf ("LDA(*),Y: AC <- [0x%04X]: 0x%02X\n", addr, cpu->ac);
}

void ldx_immediate(void)
{
	uint8_t      val;

	val = get_immediate();
	cpu->x = load_val(val);
}

void ldx_zero_page(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(0);
	cpu->x = load_mem(addr);
}

void ldx_zero_page_y(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(cpu->y);
	cpu->x = load_mem(addr);
}

void ldx_absolute(void)
{
	uint16_t      addr;

	addr = get_absolute_addr(0);
	cpu->x = load_mem(addr);
}

void ldx_absolute_y(void)
{
	uint16_t      addr;

	addr = get_absolute_addr(cpu->y);
	cpu->x = load_mem(addr);
}

void ldy_immediate(void)
{
	uint8_t      val;

	val = get_immediate();
	cpu->y = load_val(val);
}

void ldy_zero_page(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(0);
	cpu->y = load_mem(addr);
}

void ldy_zero_page_x(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(cpu->y);
	cpu->y = load_mem(addr);
}

void ldy_absolute(void)
{
	uint16_t      addr;

	addr = get_absolute_addr(0);
	cpu->y = load_mem(addr);
}

void ldy_absolute_x(void)
{
	uint16_t      addr;

	addr = get_absolute_addr(cpu->y);
	cpu->y = load_mem(addr);
}

