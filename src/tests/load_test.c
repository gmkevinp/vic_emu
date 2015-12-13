/*
 * load_test.c
 *
 *  Created on: Aug 29, 2012
 *      Author: kevin
 */
#include "unity.h"
#include "cpu6502.h"
#include "rom.h"
#include "ram.h"
#include "load.h"

static cpu6502_st  cpu6502;
static mem_st      mem;

void setUp(void)
{
	mem_init(&mem);
	rom_init(&mem);
	cpu6502_init(&cpu6502, &mem);
}

void tearDown(void)
{
}

void test_6502_run(void)
{

	//	mem_load(&cpu6502.mem, 0, prg, sizeof(prg));

	cpu6502_run(&cpu6502);
}

static void load_program(uint8_t *prg, uint16_t prg_sz)
{
	uint16_t  addr;

	cpu6502_init(cpu, &mem);
	for (addr = 0; addr<prg_sz; addr++) {
		mem_write(cpu->mem, addr, prg[addr]);
	}
}

static void assert_cpu_state(uint16_t pc, uint8_t ac, uint8_t x, uint8_t y, uint8_t status)
{
	TEST_ASSERT_EQUAL_UINT16_MESSAGE(pc, cpu->pc, "PC");
	TEST_ASSERT_EQUAL_UINT8_MESSAGE(ac, cpu->ac, "AC");
	TEST_ASSERT_EQUAL_UINT8_MESSAGE(x, cpu->x, "XR");
	TEST_ASSERT_EQUAL_UINT8_MESSAGE(y, cpu->y, "YR");
	TEST_ASSERT_EQUAL_UINT8_MESSAGE(status, cpu->status, "Status");
}

void testCPU_init(void)
{
	static uint8_t expected[MEM_SZ] = { 0 };

	assert_cpu_state(0, 0, 0, 0, 0);
	TEST_ASSERT_EQUAL_MEMORY(expected, cpu->mem, MEM_SZ);
}

void testLDA_status_zero(void)
{
	uint8_t prg1[] = { 0xA9, 0x05, 0x00 };
	uint8_t prg2[] = { 0xA9, 0x00, 0x00 };
	uint8_t prg3[] = { 0xA9, 0x05, 0x00 };

	load_program(prg1, sizeof(prg1));
	assert_cpu_state(0, 0, 0, 0, 0x00);
	cpu6502_run(cpu);
	assert_cpu_state(3, 5, 0, 0, 0x00);

	cpu6502_init(cpu, &mem);
	assert_cpu_state(0, 0, 0, 0, 0x00);
	load_program(prg2, sizeof(prg2));
	cpu6502_run(cpu);
	assert_cpu_state(3, 0, 0, 0, 0x02);

	load_program(prg3, sizeof(prg3));
	cpu->status = 0xff;
	assert_cpu_state(0, 0, 0, 0, 0xff);
	cpu6502_run(cpu);
	assert_cpu_state(3, 5, 0, 0, 0x7d);

}

