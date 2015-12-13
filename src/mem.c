/*
 * mem.c
 *
 *  Created on: Aug 26, 2012
 *      Author: kevin
 */
#include <stdio.h>
#include <string.h>

#include "mem.h"
#include "ram.h"
#include "rom.h"

void mem_init(mem_st *mem)
{
	uint32_t addr;

	printf ("RAM: 0x0000 - 0xFFFF\n");
	memset(mem->ram, 0, MEM_SZ);
	for (addr = 0; addr < MEM_SZ; addr++) {
		mem->mem_read[addr] = ram_read8;
		mem->mem_write[addr] = ram_write;
	}
}

void mem_dump(mem_st *mem)
{
	uint32_t  addr;

	for (addr=0; addr<MEM_SZ; addr++) {
		if (mem->ram[addr]) {
			printf (".%04X  %02X\n", addr, mem->ram[addr]);
		}
	}
}

uint8_t mem_read8(mem_st *mem, uint16_t addr)
{
//	printf ("Read: 0x%04X: 0x%02X\n",
//			addr, mem->ram[addr]);
	return mem->mem_read[addr](mem, addr);
}

uint16_t mem_read16(mem_st *mem, uint16_t addr)
{
	uint16_t  addr_hi;
	uint16_t  addr_lo;

	addr_hi = mem_read8(mem, addr+1);
	addr_lo = mem_read8(mem, addr);
	return ((addr_hi << 8) | addr_lo);
}

void mem_write(mem_st *mem, uint16_t addr, uint8_t val)
{
//	printf ("Write: 0x%04X: 0x%02X  <- 0x%02X\n",
//			addr, mem->ram[addr], val);
	mem->mem_write[addr](mem, addr, val);
}

void mem_load(mem_st *mem, uint16_t dst, uint8_t *src, uint16_t len)
{
	int i;

	for (i=0; i<len; i++) {
		mem_write(mem, dst+i, src[i]);
	}
}

