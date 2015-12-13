/*
 * store.c
 *
 *  Created on: Aug 29, 2012
 *      Author: kevin
 */

#include <stdlib.h>
#include <stdio.h>
#include "cpu6502.h"
#include "load.h"

void sta_zero_page(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(0);
	mem_write(cpu->mem, addr, cpu->ac);
}

void sta_zero_page_x(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(cpu->x);
	mem_write(cpu->mem, addr, cpu->ac);
}

void sta_absolute(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(0);
	mem_write(cpu->mem, addr, cpu->ac);
}

void sta_absolute_x(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(cpu->x);
	mem_write(cpu->mem, addr, cpu->ac);
}

void sta_absolute_y(void)
{
	uint16_t  addr;

	addr = get_absolute_addr(cpu->y);
	mem_write(cpu->mem, addr, cpu->ac);
}

void sta_indirect_x(void)
{
	uint16_t  addr;

	addr = get_indirect_x_addr();
	mem_write(cpu->mem, addr, cpu->ac);
}

void sta_indirect_y(void)
{
	uint16_t  addr;

	addr = get_indirect_y_addr();
//	printf ("STA(*),Y: [0x%04X] <- AC: 0x%02X\n", addr, cpu->ac);
	mem_write(cpu->mem, addr, cpu->ac);
}

void stx_zero_page(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(0);
	mem_write(cpu->mem, addr, cpu->x);
}

void stx_zero_page_y(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(cpu->y);
	mem_write(cpu->mem, addr, cpu->x);
}

void stx_absolute(void)
{
	uint16_t      addr;

	addr = get_absolute_addr(0);
	mem_write(cpu->mem, addr, cpu->x);
}

void sty_zero_page(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(0);
	mem_write(cpu->mem, addr, cpu->y);
}

void sty_zero_page_x(void)
{
	uint16_t      addr;

	addr = get_zero_page_addr(cpu->x);
	mem_write(cpu->mem, addr, cpu->y);
}

void sty_absolute(void)
{
	uint16_t      addr;

	addr = get_absolute_addr(0);
	mem_write(cpu->mem, addr, cpu->y);
}

