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

static void rom_init_unexpanded(mem_st *mem)
{
	/* 3K Expansion RAM */
	rom_region(mem, 0x0400, 0x0C00);

	/* 8K Expansion RAM/ROM */
	rom_region(mem, 0x2000, 0x2000);

	/* 8K Expansion RAM/ROM */
	rom_region(mem, 0x4000, 0x2000);

	/* 8K Expansion RAM/ROM */
	rom_region(mem, 0x6000, 0x2000);

	/* 8K Expansion ROM */
	rom_region(mem, 0xA000, 0x2000);
}
void rom_init(mem_st *mem)
{
	rom_load(mem, 0x8000, 0x1000, "rom/vic20/chargen");
	rom_load(mem, 0xC000, 0x2000, "rom/vic20/basic");
	rom_load(mem, 0xE000, 0x2000, "rom/vic20/kernal");

	rom_init_unexpanded(mem);
}

void rom_region(mem_st *mem, uint16_t dst, uint16_t len) {
	uint32_t   addr;

	for (addr = dst; addr < (dst + len); addr++) {
		mem->mem_read[addr] = rom_read8;
		mem->mem_write[addr] = rom_write;
	}
}

uint8_t  rom_read8(mem_st *mem, uint16_t addr)
{
	return mem->ram[addr];
}

void rom_write(mem_st *mem, uint16_t addr, uint8_t val)
{
//	printf ("Writing ROM: [0x%04X] <- 0x%02X\n", addr, val);
}

void rom_load(mem_st *mem, uint16_t dst, uint16_t len, char *fname)
{
	uint8_t     *data;
	size_t       obj_read;
	FILE        *fp;

	fp = fopen(fname, "r");
	if (!fp) {
		perror("Failed to open rom file");
		exit(-1);
	}

	data = malloc(len);
	if (!data) {
		perror("Failed to allocate memory for rom data");
		exit(-1);
	}

	obj_read = fread(data, len, 1, fp);
	if (obj_read != 1) {
		perror("Failed to read rom data");
		exit(-1);
	}

	memcpy(&mem->ram[dst], data, len);
	rom_region(mem, dst, len);

	fclose(fp);
	free(data);

	printf("ROM: 0x%04X - 0x%04X %s loaded\n", dst, dst + len - 1, fname);
	return;
}

