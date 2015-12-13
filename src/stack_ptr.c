/*
 * stack.c
 *
 *  Created on: Aug 27, 2012
 *      Author: kevin
 */
#include "cpu6502.h"
#include "stack_ptr.h"

#define STACK_START 0x100
#define STACK_END   0x1FF

void stack_init(void)
{
	cpu->sp = 0x00;
}

void stack_push(uint8_t val)
{
	mem_write(cpu->mem, STACK_START + cpu->sp, val);
	cpu->sp--;
	if (!cpu->sp) {
		cpu6502_halt("Stack Overflow");
	}
}

uint8_t stack_pop(void)
{
	if (cpu->sp == 0xFF) {
		cpu6502_halt("Stack Underflow");
		return 0;
	}
	cpu->sp++;
	return mem_read8(cpu->mem, STACK_START + cpu->sp);
}
