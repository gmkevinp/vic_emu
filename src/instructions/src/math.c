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

static void adc_dec_val(uint8_t val)
{
	status_reg_t  flags = 0;
	uint8_t       res_lo;
	uint8_t       res_hi;

	printf("ADC: ac: 0x%02X; val: 0x%02X; SR: 0x%02X\n", cpu->ac, val, cpu->status);
	res_lo = (cpu->ac & 0x0F) + (val & 0x0F);
	printf("lo: 0x%02X = ac: 0x%02X; val: 0x%02X; SR: 0x%02X\n",
			res_lo, cpu->ac & 0xf, val & 0x0f, cpu->status);
	if (status_is_set(&cpu->status, ST_CARRY)) {
		res_lo++;
		printf("Add carry: res_lo: 0x%02X\n", res_lo);
	}

	res_hi = ((cpu->ac & 0xF0) >> 4) + ((val & 0xF0) >> 4);
	printf("hi: 0x%02X = ac: 0x%02X; val: 0x%02X; SR: 0x%02X\n",
			res_lo, cpu->ac & 0xf0, val & 0xf0, cpu->status);
	if (res_lo > 9) {
		printf("Carry from low(0x%02X) -> hi(0x%02X)\n", res_lo, res_hi);
		res_lo -= 10;
		res_hi++;
	}

	if (res_hi > 9) {
		printf("Carry from hi(0x%02X) -> carry\n", res_hi);
		res_hi -= 10;
		flags = ST_CARRY;
	}

	status_reg_mask_and_set(&cpu->status, ST_ZERO | ST_NEG | ST_CARRY | ST_OVRFL, flags);
	cpu->ac = (res_hi << 4) | res_lo;

	printf("ADC Done: ac: 0x%02X; SR: 0x%02X\n", cpu->ac, cpu->status);

}

static void adc_val(uint8_t val)
{
	status_reg_t  flags;
	uint16_t      result;

	if (status_is_set(&cpu->status, ST_DEC)) {
		adc_dec_val(val);
		return;
	}

	result = val + cpu->ac;
	if (status_is_set(&cpu->status, ST_CARRY)) {
		result++;
	}

	flags = (result & 0xFF) ? 0: ST_ZERO;
	flags |= (result & 0x80) ? ST_NEG: 0;
	flags |= (result > 0xFF) ? ST_CARRY: 0;
	flags |= (~(cpu->ac ^ val) & (cpu->ac ^ result) & 0x80) ? ST_OVRFL: 0;
	status_reg_mask_and_set(&cpu->status, ST_ZERO | ST_NEG | ST_CARRY | ST_OVRFL, flags);
	cpu->ac = result;
}

static void sbc_val(uint8_t val)
{
	adc_val(~val);
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

