/*
 * mem.c
 *
 *  Created on: Aug 26, 2012
 *      Author: kevin
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mem.h"
#include "ram.h"
#include "rom.h"

void mem_init_functional_test(mem_st *mem)
{
    memset(mem, 0, sizeof(*mem));
    ram_region(mem, 0x0000, 0x10000);
    ram_load(mem, 0x0000, 0x10000, "rom/vic20/6502_functional_test.bin");
}

void mem_init(mem_st *mem)
{
    memset(mem, 0, sizeof(*mem));
    ram_region(mem, 0x0000, 0x8000);
    ram_region(mem, 0x8000, 0x8000);
}

void mem_dump(mem_st *mem)
{
    uint32_t  addr;

    for (addr=0; addr<=MEM_SZ; addr++) {
        if (mem->ram[addr] != 0) {
            printf (".%04X  %02X\n", addr, mem->ram[addr]);
        }
    }
}

/* Backdoor read... used by non-opcode functions */
/*  to simulate 6502 opcode processing           */
/* NOTE: This function doesn't call the read     */
/*  function pointer, which would record this    */
/*  read for debugging                           */
uint8_t mem_bd_read8(mem_st *mem, uint16_t addr)
{
    return mem->ram[addr];
}

uint16_t mem_bd_read16(mem_st *mem, uint16_t addr)
{
    uint16_t  addr_hi;
    uint16_t  addr_lo;

    addr_hi = mem_bd_read8(mem, addr+1);
    addr_lo = mem_bd_read8(mem, addr);
    return ((addr_hi << 8) | addr_lo);
}

uint8_t mem_read8(mem_st *mem, uint16_t addr)
{
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
    mem->mem_write[addr](mem, addr, val);
}

void mem_load(mem_st *mem, uint16_t dst, uint32_t len, uint8_t *src)
{
    uint32_t i;

    for (i=0; i<len; i++) {
        mem_write(mem, dst+i, src[i]);
    }
}

void mem_region(mem_st *mem, uint16_t dst, uint32_t len,
                mem_read_f read8, mem_write_f write8)
{
    uint32_t   addr;
    uint32_t   end;

    end = (uint32_t) dst + (uint32_t) len;
    if ((end-1) > 0xFFFF) {
        printf ("%s: Out of range: dst: 0x%04X; len: 0x%04X\n", __FUNCTION__, dst, len);
        exit(-1);
    }
    for (addr = dst; addr < end; addr++) {
        mem->mem_read[addr] = read8;
        mem->mem_write[addr] = write8;
    }
}

void mem_load_file(mem_st *mem, uint16_t dst, uint32_t len, char *fname)
{
    uint8_t     *data;
    size_t       obj_read;
    FILE        *fp;

    fp = fopen(fname, "r");
    if (!fp) {
        perror("Failed to open file");
        exit(-1);
    }

    data = malloc(len+1);
    if (!data) {
        perror("Failed to allocate memory for data");
        exit(-1);
    }

    obj_read = fread(data, len, 1, fp);
    if (obj_read != 1) {
        perror("Failed to read data");
        exit(-1);
    }

    mem_load(mem, dst, len, data);

    fclose(fp);
    free(data);
    return;
}

