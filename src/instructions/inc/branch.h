/*
 * branch.h
 *
 *  Created on: Aug 27, 2012
 *      Author: kevin
 */

#ifndef BRANCH_H_
#define BRANCH_H_

void bcc(void);
void bcs(void);
void beq(void);
void bmi(void);
void bne(void);
void bpl(void);
void bvc(void);
void bvs(void);

bool is_branch_op(uint8_t op);
uint16_t calc_branch_addr(uint16_t pc, uint8_t addr);

#endif /* BRANCH_H_ */
