/*
 * incdec.c
 *
 *  Created on: Aug 27, 2012
 *      Author: kevin
 */
#include "cpu6502.h"
#include "incdec.h"

static void set_status(uint8_t val)
{
	status_reg_t  flags;

	flags = (val) ? 0: ST_ZERO;
	flags |= (val & 0x80) ? ST_NEG: 0;
	status_reg_mask_and_set(&cpu->status, ST_ZERO | ST_NEG, flags);
}

static void dec_mem(uint16_t addr)
{
	uint8_t  val;

	val = mem_read8(cpu->mem, addr);
	val--;
	mem_write(cpu->mem, addr, val);
	set_status(val);
}

static void inc_mem(uint16_t addr)
{
	uint8_t  val;

	val = mem_read8(cpu->mem, addr);
	val++;
	mem_write(cpu->mem, addr, val);
	set_status(val);
}

void dec_zero_page(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(0);
	dec_mem(addr);
}

void dec_zero_page_x(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(cpu->x);
	dec_mem(addr);
}

void dec_absolute(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(0);
	dec_mem(addr);
}

void dec_absolute_x(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(cpu->x);
	dec_mem(addr);
}

void dex(void)
{
	cpu->x--;
	set_status(cpu->x);
}

void dey(void)
{
	cpu->y--;
	set_status(cpu->y);
}

void inc_zero_page(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(0);
	inc_mem(addr);
}

void inc_zero_page_x(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(cpu->x);
	inc_mem(addr);
}

void inc_absolute(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(0);
	inc_mem(addr);
}

void inc_absolute_x(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(cpu->x);
	inc_mem(addr);
}

void inx(void)
{
	cpu->x++;
	set_status(cpu->x);
}

void iny(void)
{
	cpu->y++;
	set_status(cpu->y);
}


