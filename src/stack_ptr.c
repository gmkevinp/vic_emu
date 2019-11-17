/*
 * stack.c
 *
 *  Created on: Aug 27, 2012
 *      Author: kevin
 */
#include "cpu6502.h"
#include "stack_ptr.h"

#define STACK_START         0x100
#define STACK_END           0x1FF
#define STACK_POS(cpu)     (STACK_START + (cpu)->sp)
#define STACK_TOS_VAL(cpu) (mem_read8((cpu)->mem, STACK_POS(cpu)))

#define STACK_DEBUG  0

static void stack_dump()
{
	uint16_t  addr;

	if (cpu->sp == 0xFF) {
		return;
	}
	printf("Stack:\n");
	for (addr = STACK_END; addr >= STACK_POS(cpu); addr--) {
		printf("  0x%04X: 0x%02X\n", addr, mem_read8(cpu->mem, addr));
	}
}

void stack_init(void)
{
	cpu->sp = 0xFF;
}

void stack_push(uint8_t val)
{

	if (STACK_DEBUG) {
		printf ("Pre- Push(0x%02X): SP: 0x%02X; PC: 0x%04X; 0x%04X: 0x%02X\n",
				val, cpu->sp, cpu->pc, STACK_POS(cpu), STACK_TOS_VAL(cpu));
	}

	mem_write(cpu->mem, STACK_POS(cpu), val);
	cpu->sp--;

	if (STACK_DEBUG) {
		printf ("Post-Push      : SP: 0x%02X; PC: 0x%04X; 0x%04X: 0x%02X\n",
				cpu->sp, cpu->pc, STACK_POS(cpu), STACK_TOS_VAL(cpu));
		stack_dump();
	}
}

uint8_t stack_pop(void)
{
	uint8_t  val;

	if (STACK_DEBUG) {
		printf ("Pre -Pop       : SP: 0x%02X; PC: 0x%04X; 0x%04X: 0x%02X\n",
				cpu->sp, cpu->pc, STACK_POS(cpu), STACK_TOS_VAL(cpu));
	}

	cpu->sp++;
	val = mem_read8(cpu->mem, STACK_POS(cpu));

	if (STACK_DEBUG) {
		printf ("Post-Pop(0x%02X) : SP: 0x%02X; PC: 0x%04X; 0x%04X: 0x%02X\n",
				val, cpu->sp, cpu->pc, STACK_POS(cpu), STACK_TOS_VAL(cpu));
		stack_dump();
	}

	return val;
}
