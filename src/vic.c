/*
 * vic.c
 *
 *  Created on: Dec 25, 2015
 *      Author: kevin
 */
#include <stdlib.h>
#include <stdio.h>
#include "vic.h"
#include "mem.h"

static mem_st  *mem;

static uint8_t
vic_read8(mem_st *mem, uint16_t dst)
{
	return mem->ram[dst];
}

static void
vic_write8(mem_st *mem, uint16_t dst, uint8_t val)
{
	mem->ram[dst] = val;
}

void vic_region(mem_st *mem, uint16_t dst, uint16_t len)
{
	mem_region(mem, dst, len, vic_read8, vic_write8);
	printf ("VIC: 0x%04X - 0x%04X\n", dst, dst + len - 1);
}

void vic_clk(void)
{
}

static void vic_col2rgbf(uint8_t col, uint8_t *pixel)
{
	/* Colours from http://www.pepto.de/projects/colorvic */
	static rgbu8_st rgbu8[] = {
			{ 0x00, 0x00, 0x00 },
			{ 0xFF, 0xFF, 0xFF },
			{ 0x68, 0x37, 0x2B },
			{ 0x70, 0xA4, 0xB2 },
			{ 0x6F, 0x3D, 0x86 },
			{ 0x58, 0x8D, 0x43 },
			{ 0x35, 0x28, 0x79 },
			{ 0xB8, 0xC7, 0x6F },
			{ 0x6F, 0x4F, 0x25 },
			{ 0x43, 0x39, 0x00 },
			{ 0x9A, 0x67, 0x59 },
			{ 0x44, 0x44, 0x44 },
			{ 0x6C, 0x6C, 0x6C },
			{ 0x9A, 0xD2, 0x84 },
			{ 0x6C, 0x5E, 0xB5 },
			{ 0x95, 0x95, 0x95 }
	};

	*pixel++ = rgbu8[col].red;
	*pixel++ = rgbu8[col].green;
	*pixel++ = rgbu8[col].blue;
}

static void vic_get_rgbu8_pixel(uint16_t x, uint16_t y, uint8_t *pixels)
{
	uint16_t        screen_addr = 0x1E00;
	uint16_t        colour_addr = 0x9600;
	uint16_t        char_rom_addr = 0x8000;
	uint16_t        bit_data_addr;
	uint16_t        offset;
	uint8_t         row;
	uint8_t         col;
	uint8_t         ch;
	uint8_t         bit;
	uint8_t         data;

//	printf ("Pixel X: %d; Y: %d\n", x, y);
	row = y >> 3;
	offset = row * 22;
	col = x >> 3;
	offset += col;
//	printf ("Screen row: %d; col: %d; Offset: 0x%04X\n", row, col, offset);
	ch = mem_bd_read8(mem, screen_addr + offset);
	col = mem_bd_read8(mem, colour_addr + offset);
//	printf ("Char addr: 0x%04X; c: 0x%02X\n", screen_addr + offset, ch);

	bit_data_addr = char_rom_addr + (((uint16_t) ch) << 3) + (y & 0x7);
	data = mem_bd_read8(mem, bit_data_addr);
//	printf ("bit_data_addr: 0x%04X; val: 0x%02X\n", bit_data_addr, data);
	bit = (data & (0x80 >> (x & 0x7)));
	if (bit) {
//		printf ("bit 0x%02X is on\n", 0x80 >> (x & 0x7));
	} else {
//		printf ("bit 0x%02X is off\n", 0x80 >> (x & 0x7));
		col = 1;
	}
	vic_col2rgbf(col, pixels);
}

void vic_get_rgbu8_screen(uint16_t width, uint16_t height, uint8_t *pixels)
{
	uint16_t  w;
	uint16_t  h;
	uint32_t  i;

	/* Need to flip image, pixels has (0,0) at lower left of screen */
	/* VIC has (0,0) at upper left of screen */
	i = 0;
	for (h = 0; h < height; h++) {
		for (w = 0; w < width; w++) {
			vic_get_rgbu8_pixel(w, height-h-1, &pixels[i]);
			i += 3;
		}
	}
//	exit(-1);
}

void vic_get_screen_sz(uint16_t *width, uint16_t *height)
{
	*width = 22 * 8;
	*height = 23 * 8;
}

void vic_init(mem_st  *mem_in)
{
	mem = mem_in;
	vic_region(mem, 0x9000, 0x10);
}
