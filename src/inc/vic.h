/*
 * vic.h
 *
 *  Created on: Aug 23, 2015
 *      Author: kevin
 */

#ifndef VIC_H_
#define VIC_H_

#include <stdint.h>
#include "mem.h"

typedef vic_st_ {
	uint8_t   origin_h;
	uint8_t   origin_v;
	uint8_t   n_cols;
	uint8_t   n_rows;
	uint8_t   raster;
	uint8_t   screen_char_mem;
	uint8_t   pen_h;
	uint8_t   pen_v;
	uint8_t   paddle1;
	uint8_t   paddle2;
	uint8_t   bass;
	uint8_t   alto;
	uint8_t   soprano;
	uint8_t   noise;
	uint8_t   aux_colour_volume;
	uint8_t   screen_border_col;
} vic_st;

#define VIC_INTERLACE_MASK  0x80
#define VIC_ORIGIN_H_MASK   0x7F
#define
void     vic_init(mem_st *mem);
void     vic_region(mem_st *mem, uint16_t dst, uint16_t len);
uint8_t  vic_read8(mem_st *mem, uint16_t addr);
void     vic_write(mem_st *mem, uint16_t addr, uint8_t val);


#endif /* INC_VIC_H_ */
