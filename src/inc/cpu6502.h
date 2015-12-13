/*
 * 6502cpu.h
 *
 *  Created on: Aug 26, 2012
 *      Author: kevin
 */

#ifndef CPU6502_H_
#define CPU6502_H_
#include <stdio.h>

#include "status_reg.h"
#include "pc_reg.h"
#include "mem.h"
#include "inst.h"
#include "stack_ptr.h"

typedef uint8_t bool;
#define TRUE  ((bool)(0==0))
#define FALSE ((bool)(0==1))

typedef struct cpu6502_st_ {
	status_reg_t    status;
	pc_reg_t        pc;
	mem_st         *mem;
	inst_st         inst;
	uint8_t         wait_cycles;

	uint8_t         ac;
	uint8_t         x;
	uint8_t         y;
	uint8_t         sp;

	uint8_t         halt;
	uint8_t         trace;
	uint32_t        n_inst;
	FILE           *ofp;
} cpu6502_st;

void cpu6502_init(cpu6502_st *cpu, mem_st *mem);
void cpu6502_run(cpu6502_st *cpu);
void cpu6502_halt(const char *str);
void cpu6502_dump(cpu6502_st *cpu);
uint8_t cpu6502_fetch_pc_and_inc(void);
void cpu6502_step(void);
void cpu6502_clk(void);
void cpu6502_dump_inst_exec_count(cpu6502_st *cpu);

extern cpu6502_st *cpu;

#endif /* CPU6502_H_ */
