/*
 * and.c
 *
 *  Created on: Aug 27, 2012
 *      Author: kevin
 */

#include <stdlib.h>
#include <stdio.h>
#include "cpu6502.h"
#include "bitops.h"

static void set_flags(void)
{
    status_reg_t  flags;

    flags = (cpu->ac) ? 0: ST_ZERO;
    flags |= (cpu->ac & 0x80) ? ST_NEG: 0;
    status_reg_mask_and_set(&cpu->status, ST_ZERO | ST_NEG, flags);
}

static void and_val(uint8_t val)
{
    cpu->ac &= val;
    set_flags();
}

static void and_mem(uint16_t addr)
{
    uint8_t  val;

    val = mem_read8(cpu->mem, addr);
    and_val(val);
}

static void bit_mem(uint16_t addr)
{
    uint8_t  val;
    uint8_t  flags;

    val = mem_read8(cpu->mem, addr);
    flags = (cpu->ac & val)? 0: ST_ZERO;
    flags |= (val & 0x80)? ST_NEG: 0;
    flags |= (val & 0x40)? ST_OVRFL: 0;
    status_reg_mask_and_set(&cpu->status, ST_ZERO | ST_NEG | ST_OVRFL, flags);
}

static void eor_val(uint8_t val)
{
    cpu->ac ^= val;
    set_flags();
}

static void eor_mem(uint16_t addr)
{
    uint8_t  val;

    val = mem_read8(cpu->mem, addr);
    eor_val(val);
}

static void ora_val(uint8_t val)
{
    cpu->ac |= val;
    set_flags();
}

static void ora_mem(uint16_t addr)
{
    uint8_t  val;

    val = mem_read8(cpu->mem, addr);
    ora_val(val);
}

void and_immediate(void)
{
    uint8_t      val;

    val = get_immediate();
    and_val(val);
}

void and_zero_page(void)
{
    uint16_t      addr;

    addr = get_zero_page_addr(0);
    and_mem(addr);
}

void and_zero_page_x(void)
{
    uint16_t      addr;

    addr = get_zero_page_addr(cpu->x);
    and_mem(addr);
}

void and_absolute(void)
{
    uint16_t  addr;

    addr = get_absolute_addr(0);
    and_mem(addr);
}

void and_absolute_x(void)
{
    uint16_t  addr;

    addr = get_absolute_addr(cpu->x);
    and_mem(addr);
}

void and_absolute_y(void)
{
    uint16_t  addr;

    addr = get_absolute_addr(cpu->y);
    and_mem(addr);
}

void and_indirect_x(void)
{
    uint16_t  addr;

    addr = get_indirect_x_addr();
    and_mem(addr);
}

void and_indirect_y(void)
{
    uint16_t  addr;

    addr = get_indirect_y_addr();
    and_mem(addr);
}

void bit_zero_page(void)
{
    uint16_t      addr;

    addr = get_zero_page_addr(0);
    bit_mem(addr);
}

void bit_absolute(void)
{
    uint16_t  addr;

    addr = get_absolute_addr(0);
    bit_mem(addr);
}

void eor_immediate(void)
{
    uint8_t      val;

    val = get_immediate();
    eor_val(val);
}

void eor_zero_page(void)
{
    uint16_t      addr;

    addr = get_zero_page_addr(0);
    eor_mem(addr);
}

void eor_zero_page_x(void)
{
    uint16_t      addr;

    addr = get_zero_page_addr(cpu->x);
    eor_mem(addr);
}

void eor_absolute(void)
{
    uint16_t  addr;

    addr = get_absolute_addr(0);
    eor_mem(addr);
}

void eor_absolute_x(void)
{
    uint16_t  addr;

    addr = get_absolute_addr(cpu->x);
    eor_mem(addr);
}

void eor_absolute_y(void)
{
    uint16_t  addr;

    addr = get_absolute_addr(cpu->y);
    eor_mem(addr);
}

void eor_indirect_x(void)
{
    uint16_t  addr;

    addr = get_indirect_x_addr();
    eor_mem(addr);
}

void eor_indirect_y(void)
{
    uint16_t  addr;

    addr = get_indirect_y_addr();
    eor_mem(addr);
}

void ora_immediate(void)
{
    uint8_t      val;

    val = get_immediate();
    ora_val(val);
}

void ora_zero_page(void)
{
    uint16_t      addr;

    addr = get_zero_page_addr(0);
    ora_mem(addr);
}

void ora_zero_page_x(void)
{
    uint16_t      addr;

    addr = get_zero_page_addr(cpu->x);
    ora_mem(addr);
}

void ora_absolute(void)
{
    uint16_t  addr;

    addr = get_absolute_addr(0);
    ora_mem(addr);
}

void ora_absolute_x(void)
{
    uint16_t  addr;

    addr = get_absolute_addr(cpu->x);
    ora_mem(addr);
}

void ora_absolute_y(void)
{
    uint16_t  addr;

    addr = get_absolute_addr(cpu->y);
    ora_mem(addr);
}

void ora_indirect_x(void)
{
    uint16_t  addr;

    addr = get_indirect_x_addr();
    ora_mem(addr);
}

void ora_indirect_y(void)
{
    uint16_t  addr;

    addr = get_indirect_y_addr();
    ora_mem(addr);
}
