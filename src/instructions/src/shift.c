/*
 * shift.c
 *
 *  Created on: Aug 29, 2012
 *      Author: kevin
 */

#include "cpu6502.h"
#include "shift.h"

static uint8_t asl_val(uint8_t val)
{
	status_reg_t  flags = 0;

	flags |= (val & 0x80) ? ST_CARRY: 0;
	val <<= 1;
	flags = (!val) ? ST_ZERO: 0;
	flags |= (val & 0x80) ? ST_NEG: 0;

	status_reg_mask_and_set(&cpu->status, ST_ZERO | ST_NEG | ST_CARRY, flags);
	return val;
}

static uint8_t lsr_val(uint8_t val)
{
	status_reg_t  flags;

	flags = (val & 0x01) ? ST_CARRY: 0;
	val >>= 1;
	flags |= (!val) ? ST_ZERO: 0;

	status_reg_mask_and_set(&cpu->status, ST_ZERO | ST_NEG | ST_CARRY, flags);
	return val;
}

static uint8_t rol_val(uint8_t val)
{
	status_reg_t  flags;
	uint8_t       new_carry;
	uint8_t       old_carry;

	old_carry = status_is_set(&cpu->status, ST_CARRY)? 1: 0;
	new_carry = val & 0x80;
	val <<= 1;
	val |= old_carry;
	flags = (new_carry) ? ST_CARRY: 0;
	flags |= (!val) ? ST_ZERO: 0;
	flags |= (val & 0x80) ? ST_NEG: 0;

	status_reg_mask_and_set(&cpu->status, ST_ZERO | ST_NEG | ST_CARRY, flags);
	return val;
}

static uint8_t ror_val(uint8_t val)
{
	status_reg_t  flags;
	uint8_t       old_carry;
	uint8_t       new_carry;

	old_carry = status_is_set(&cpu->status, ST_CARRY)? 1: 0;
	new_carry = val & 0x01;
	val >>= 1;
	val |= old_carry << 7;
	flags = (new_carry) ? ST_CARRY: 0;
	flags |= (!val) ? ST_ZERO: 0;
	flags |= (val & 0x80) ? ST_NEG: 0;

	status_reg_mask_and_set(&cpu->status, ST_ZERO | ST_NEG | ST_CARRY, flags);
	return val;
}

static void asl_mem(uint16_t addr)
{
	uint8_t  val;

	val = mem_read8(cpu->mem, addr);
	val = asl_val(val);
	mem_write(cpu->mem, addr, val);
}

static void lsr_mem(uint16_t addr)
{
	uint8_t  val;

	val = mem_read8(cpu->mem, addr);
	val = lsr_val(val);
	mem_write(cpu->mem, addr, val);
}

static void rol_mem(uint16_t addr)
{
	uint8_t  val;

	val = mem_read8(cpu->mem, addr);
	val = rol_val(val);
	mem_write(cpu->mem, addr, val);
}

static void ror_mem(uint16_t addr)
{
	uint8_t  val;

	val = mem_read8(cpu->mem, addr);
	val = ror_val(val);
	mem_write(cpu->mem, addr, val);
}

void asl_accumulator(void)
{
	cpu->ac = asl_val(cpu->ac);
}

void asl_zero_page(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(0);
	asl_mem(addr);
}

void asl_zero_page_x(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(cpu->x);
	asl_mem(addr);
}

void asl_absolute(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(0);
	asl_mem(addr);
}

void asl_absolute_x(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(cpu->x);
	asl_mem(addr);
}

void lsr_accumulator(void)
{
	cpu->ac = lsr_val(cpu->ac);
}

void lsr_zero_page(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(0);
	lsr_mem(addr);
}

void lsr_zero_page_x(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(cpu->x);
	lsr_mem(addr);
}

void lsr_absolute(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(0);
	lsr_mem(addr);
}

void lsr_absolute_x(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(cpu->x);
	lsr_mem(addr);
}

void rol_accumulator(void)
{
	cpu->ac = rol_val(cpu->ac);
}

void rol_zero_page(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(0);
	rol_mem(addr);
}

void rol_zero_page_x(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(cpu->x);
	rol_mem(addr);
}

void rol_absolute(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(0);
	rol_mem(addr);
}

void rol_absolute_x(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(cpu->x);
	rol_mem(addr);
}

void ror_accumulator(void)
{
	cpu->ac = ror_val(cpu->ac);
}

void ror_zero_page(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(0);
	ror_mem(addr);
}

void ror_zero_page_x(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(cpu->x);
	ror_mem(addr);
}

void ror_absolute(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(0);
	ror_mem(addr);
}

void ror_absolute_x(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(cpu->x);
	ror_mem(addr);
}

