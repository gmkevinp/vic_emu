/*
 * mem.h
 *
 *  Created on: Aug 26, 2012
 *      Author: kevin
 */

#ifndef RAM_H_
#define RAM_H_
#include <stdint.h>
#include "mem.h"

uint8_t  ram_read8(mem_st *mem, uint16_t addr);
void ram_write(mem_st *mem, uint16_t addr, uint8_t val);

#endif
