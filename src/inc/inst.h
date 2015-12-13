/*
 * instr.h
 *
 *  Created on: Aug 26, 2012
 *      Author: kevin
 */

#ifndef INSTR_H_
#define INSTR_H_
#include <stdint.h>
#include "inst_db.h"

#define N_OPCODES  256

typedef struct inst_st_ {
	inst_db_entry_st  inst_data[N_OPCODES];
} inst_st;

void inst_init(inst_st *inst);
uint8_t get_immediate(void);
uint16_t get_zero_page_addr(uint8_t offset);
uint16_t get_absolute_addr(uint8_t offset);
uint16_t get_indirect_x_addr(void);
uint16_t get_indirect_y_addr(void);
uint16_t get_indirect_addr(void);


#endif /* INSTR_H_ */
