/*
 * inst_db.h
 *
 *  Created on: Aug 26, 2012
 *      Author: kevin
 */

#ifndef INST_DB_H_
#define INST_DB_H_

#include <stdint.h>

typedef void (*inst_run_f)(void);

typedef struct inst_db_entry_st_ {
	uint8_t      opcode;
	uint8_t      sz;
	uint8_t      n_cycles;
	uint8_t      pc_adv;
	char        *format;
	inst_run_f   func;
	uint32_t     exec_count;
} inst_db_entry_st;

extern inst_db_entry_st inst_db[];
extern uint8_t inst_db_num_entries;

#endif /* INST_DB_H_ */
