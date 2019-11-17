/*
 * ram.c
 *
 *  Created on: Aug 23, 2015
 *      Author: kevin
 */
#include <stdio.h>
#include <stdlib.h>
#include "cpu6502.h"
#include "ram.h"
#include "mem.h"

static uint8_t  ram_read8(mem_st *mem, uint16_t addr)
{
	uint8_t  val;

	val = mem->ram[addr];
	mem->last_rd_addr = addr;
	mem->last_rd_val = val;
	return val;
}

static void ram_write(mem_st *mem, uint16_t addr, uint8_t val)
{
	mem->ram[addr] = val;
	mem->last_wr_addr = addr;
	mem->last_wr_val = val;
}

void ram_region(mem_st *mem, uint16_t dst, uint32_t len)
{
	mem_region(mem, dst, len, ram_read8, ram_write);
	printf ("RAM Region: 0x%04X - 0x%04X\n", dst, dst + len);
}

void ram_load(mem_st *mem, uint16_t dst, uint32_t len, char *fname)
{
	printf("RAM Load  : 0x%04X - 0x%04X %s\n", dst, dst + len, fname);
	mem_load_file(mem, dst, len, fname);

	return;
}
