/*
 * adc.c
 *
 *  Created on: Aug 26, 2012
 *      Author: kevin
 */

#include <stdlib.h>
#include <stdio.h>
#include "cpu6502.h"
#include "math.h"

static void adc_val(uint8_t val)
{
	status_reg_t  flags;

	val += cpu->ac;
	if (status_is_set(&cpu->status, ST_CARRY)) {
		val++;
	}

	flags = (val) ? 0: ST_ZERO;
	flags |= (val & 0x80) ? ST_NEG: 0;
	flags |= (val < cpu->ac) ? ST_CARRY: 0;
	flags |= (((cpu->ac & 0x80) == 0) && (val & 0x80)) ? ST_OVRFL: 0;
	status_reg_mask_and_set(&cpu->status, ST_ZERO | ST_NEG | ST_CARRY | ST_OVRFL, flags);

	cpu->ac = val;
}

static void sbc_val(uint8_t val)
{
	status_reg_t  flags;

	val = cpu->ac - val;
	if (status_is_set(&cpu->status, ST_CARRY)) {
		val--;
	}

	flags = (val) ? 0: ST_ZERO;
	flags |= (val & 0x80) ? ST_NEG: 0;
	flags |= (val < cpu->ac) ? ST_CARRY: 0;
	flags |= (((cpu->ac & 0x80) == 0) && (val & 0x80)) ? ST_OVRFL: 0;
	status_reg_mask_and_set(&cpu->status, ST_ZERO | ST_NEG | ST_CARRY | ST_OVRFL, flags);

	cpu->ac = val;
}

static void adc_mem(uint16_t addr)
{
	uint8_t  val;

	val = mem_read8(cpu->mem, addr);
	adc_val(val);
}

static void sbc_mem(uint16_t addr)
{
	uint8_t  val;

	val = mem_read8(cpu->mem, addr);
	sbc_val(val);
}

void adc_immediate(void)
{
	uint8_t      val;

	val = get_immediate();
	adc_val(val);
}

void adc_zero_page(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(0);
	adc_mem(addr);
}

void adc_zero_page_x(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(cpu->x);
	adc_mem(addr);
}

void adc_absolute(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(0);
	adc_mem(addr);
}

void adc_absolute_x(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(cpu->x);
	adc_mem(addr);
}

void adc_absolute_y(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(cpu->y);
	adc_mem(addr);
}

void adc_indirect_x(void)
{
	uint16_t  addr;

	addr = get_indirect_x_addr();
	adc_mem(addr);
}

void adc_indirect_y(void)
{
	uint16_t  addr;

	addr = get_indirect_y_addr();
	adc_mem(addr);
}

void sbc_immediate(void)
{
	uint8_t      val;

	val = get_immediate();
	sbc_val(val);
}

void sbc_zero_page(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(0);
	sbc_mem(addr);
}

void sbc_zero_page_x(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(cpu->x);
	sbc_mem(addr);
}

void sbc_absolute(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(0);
	sbc_mem(addr);
}

void sbc_absolute_x(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(cpu->x);
	sbc_mem(addr);
}

void sbc_absolute_y(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(cpu->y);
	sbc_mem(addr);
}

void sbc_indirect_x(void)
{
	uint16_t  addr;

	addr = get_indirect_x_addr();
	sbc_mem(addr);
}

void sbc_indirect_y(void)
{
	uint16_t  addr;

	addr = get_indirect_y_addr();
	sbc_mem(addr);
}

