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

uint8_t  ram_read8(mem_st *mem, uint16_t addr)
{
	uint8_t  val;

	val = mem->ram[addr];
	mem->last_rd_addr = addr;
	mem->last_rd_val = val;
	return val;
}

void ram_write(mem_st *mem, uint16_t addr, uint8_t val)
{
	mem->ram[addr] = val;
	mem->last_wr_addr = addr;
	mem->last_wr_val = val;
}

void ram_region(mem_st *mem, uint16_t dst, uint16_t len) {
	uint32_t   addr;
	uint32_t   end;

	end = (uint32_t) dst + (uint32_t) len;
	if (end > 0xFFFF) {
		printf ("%s: Out of range: dst: 0x%04X; len: 0x%04X\n", __FUNCTION__, dst, len);
		exit(-1);
	}
	printf ("RAM: 0x%04X - 0x%04X\n", dst, dst + len);
	for (addr = dst; addr <= end; addr++) {
		mem->mem_read[addr] = ram_read8;
		mem->mem_write[addr] = ram_write;
	}
}

void ram_load(mem_st *mem, uint16_t dst, uint16_t len, char *fname)
{
	mem_load_file(mem, dst, len, fname);
	ram_region(mem, dst, len);
	printf("RAM: 0x%04X - 0x%04X %s loaded\n", dst, dst + len - 1, fname);

	return;
}
