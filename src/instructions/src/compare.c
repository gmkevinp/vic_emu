/*
 * compare.c
 *
 *  Created on: Aug 29, 2012
 *      Author: kevin
 */
#include "cpu6502.h"
#include "compare.h"

static void cmp_val(uint8_t val1, uint8_t val2)
{
	status_reg_t  flags;
	uint8_t       result;

	result = val1 - val2;
	flags = (!result) ? ST_ZERO: 0;
	flags |= (result & 0x80) ? ST_NEG: 0;
	flags |= (val1 >= val2) ? ST_CARRY: 0;
	status_reg_mask_and_set(&cpu->status, ST_ZERO | ST_NEG | ST_CARRY, flags);
}

static void cmp_mem(uint8_t val1, uint16_t addr)
{
	uint8_t       val2;

	val2 = mem_read8(cpu->mem, addr);
	cmp_val(val1, val2);
}

void cmp_immediate(void)
{
	uint8_t      val;

	val = get_immediate();
	cmp_val(cpu->ac, val);
}

void cmp_zero_page(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(0);
	cmp_mem(cpu->ac, addr);
}

void cmp_zero_page_x(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(cpu->x);
	cmp_mem(cpu->ac, addr);
}

void cmp_absolute(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(0);
	cmp_mem(cpu->ac, addr);
}

void cmp_absolute_x(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(cpu->x);
	cmp_mem(cpu->ac, addr);
}

void cmp_absolute_y(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(cpu->y);
	cmp_mem(cpu->ac, addr);
}

void cmp_indirect_x(void)
{
	uint16_t  addr;

	addr = get_indirect_x_addr();
	cmp_mem(cpu->ac, addr);
}

void cmp_indirect_y(void)
{
	uint16_t  addr;

	addr = get_indirect_y_addr();
	cmp_mem(cpu->ac, addr);
//	printf ("CMP(*),Y: AC == [0x%04X]?: 0x%02X\n", addr, cpu->mem->ram[addr]);
}

void cpx_immediate(void)
{
	uint8_t      val;

	val = get_immediate();
	cmp_val(cpu->x, val);
}

void cpx_zero_page(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(0);
	cmp_mem(cpu->x, addr);
}

void cpx_absolute(void)
{
	uint16_t      addr;

	addr = get_absolute_addr(0);
	cmp_mem(cpu->x, addr);
}

void cpy_immediate(void)
{
	uint8_t      val;

	val = get_immediate();
	cmp_val(cpu->y, val);
}

void cpy_zero_page(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(0);
	cmp_mem(cpu->y, addr);
}

void cpy_absolute(void)
{
	uint16_t      addr;

	addr = get_absolute_addr(0);
	cmp_mem(cpu->y, addr);
}
