/*
 * rom.h
 *
 *  Created on: Aug 23, 2015
 *      Author: kevin
 */
#ifndef ROM_H_
#define ROM_H_
#include <stdint.h>
#include "mem.h"

void rom_init(mem_st *mem);
void rom_load(mem_st *mem, uint16_t dst, uint16_t len, char *fname);

#endif
