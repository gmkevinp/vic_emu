/*
 * rom.c
 *
 *  Created on: Aug 23, 2015
 *      Author: kevin
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "rom.h"
#include "mem.h"

static uint8_t rom_read8(mem_st *mem, uint16_t addr)
{
	uint8_t  val;

	val = mem->ram[addr];
	mem->last_rd_addr = addr;
	mem->last_rd_val = val;
	return val;
}

static void rom_write(mem_st *mem, uint16_t addr, uint8_t val)
{
}

static void rom_region(mem_st *mem, uint16_t dst, uint16_t len, char *desc)
{
	mem_region(mem, dst, len, rom_read8, rom_write);
	printf ("ROM: 0x%04X - 0x%04X %s\n", dst, dst + len - 1, desc);
}

static void rom_init_unexpanded(mem_st *mem)
{
	/* 3K Expansion RAM */
	rom_region(mem, 0x0400, 0x0C00, "3K RAM");

	/* 8K Expansion RAM/ROM */
	rom_region(mem, 0x2000, 0x2000, "8K RAM");

	/* 8K Expansion RAM/ROM */
	rom_region(mem, 0x4000, 0x2000, "8K RAM");

	/* 8K Expansion RAM/ROM */
	rom_region(mem, 0x6000, 0x2000, "8K RAM");

	/* 8K Expansion ROM */
	rom_region(mem, 0xA000, 0x2000, "8K RAM");
}

void rom_load(mem_st *mem, uint16_t dst, uint16_t len, char *fname)
{
	mem_load_file(mem, dst, len, fname);
	rom_region(mem, dst, len, fname);
	printf("ROM: 0x%04X - 0x%04X %s loaded\n", dst, dst + len - 1, fname);

	return;
}

void rom_init(mem_st *mem)
{
	rom_load(mem, 0x8000, 0x1000, "rom/vic20/chargen");
	rom_load(mem, 0xC000, 0x2000, "rom/vic20/basic");
	rom_load(mem, 0xE000, 0x2000, "rom/vic20/kernal");

	rom_init_unexpanded(mem);
}

