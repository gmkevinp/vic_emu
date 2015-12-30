/*
 * mem.h
 *
 *  Created on: Aug 26, 2012
 *      Author: kevin
 */

#ifndef MEM_H_
#define MEM_H_
#include <stdint.h>

#define MEM_SZ  65536

struct mem_st_;

typedef uint8_t (*mem_read_f )(struct mem_st_ *mem, uint16_t addr);
typedef void    (*mem_write_f)(struct mem_st_ *mem, uint16_t addr, uint8_t val);

typedef struct mem_st_ {
	uint8_t     ram[MEM_SZ];
	mem_read_f  mem_read[MEM_SZ];
	mem_write_f mem_write[MEM_SZ];
	uint16_t    last_rd_addr;
	uint8_t     last_rd_val;
	uint16_t    last_wr_addr;
	uint8_t     last_wr_val;
} mem_st;

void mem_init(mem_st *mem);
void mem_dump(mem_st *mem);
uint8_t  mem_read8(mem_st *mem, uint16_t addr);
uint16_t mem_read16(mem_st *mem, uint16_t addr);
uint8_t  mem_bd_read8(mem_st *mem, uint16_t addr);
uint16_t mem_bd_read16(mem_st *mem, uint16_t addr);
void mem_write(mem_st *mem, uint16_t addr, uint8_t val);
void mem_load(mem_st *mem, uint16_t dst, uint16_t len, uint8_t *src);
void mem_load_file(mem_st *mem, uint16_t dst, uint16_t len, char *fname);
void mem_region(mem_st *mem, uint16_t dst, uint16_t len,
				mem_read_f read8, mem_write_f write8);

#endif /* MEM_H_ */
