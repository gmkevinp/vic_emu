/*
 * pc_reg.h
 *
 *  Created on: Aug 26, 2012
 *      Author: kevin
 */

#ifndef PC_REG_H_
#define PC_REG_H_
#include <stdint.h>
#include "mem.h"

typedef uint16_t  pc_reg_t;

void pc_reg_init(pc_reg_t *pc, mem_st *mem);
void pc_reg_dump(pc_reg_t *pc);
void pc_reg_inc(pc_reg_t *pc, uint8_t bytes);
void pc_reg_set(pc_reg_t *pc, uint16_t addr);

#endif /* PC_REG_H_ */
