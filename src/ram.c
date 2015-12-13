/*
 * ram.c
 *
 *  Created on: Aug 23, 2015
 *      Author: kevin
 */
#include <stdio.h>
#include "cpu6502.h"
#include "ram.h"

uint8_t  ram_read8(mem_st *mem, uint16_t addr)
{
	return mem->ram[addr];
}

void ram_write(mem_st *mem, uint16_t addr, uint8_t val)
{
	mem->ram[addr] = val;
//	printf ("Writing RAM: [0x%04X] <- %02X\n", addr, val);
}

