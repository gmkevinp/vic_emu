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

void ram_load(mem_st *mem, uint16_t dst, uint16_t len, char *fname);
void ram_region(mem_st *mem, uint16_t dst, uint16_t len);

#endif
