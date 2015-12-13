/*
 * compare.h
 *
 *  Created on: Aug 29, 2012
 *      Author: kevin
 */

#ifndef COMPARE_H_
#define COMPARE_H_

void cmp_immediate(void);
void cmp_zero_page(void);
void cmp_zero_page_x(void);
void cmp_absolute(void);
void cmp_absolute_x(void);
void cmp_absolute_y(void);
void cmp_indirect_x(void);
void cmp_indirect_y(void);

void cpx_immediate(void);
void cpx_zero_page(void);
void cpx_absolute(void);

void cpy_immediate(void);
void cpy_zero_page(void);
void cpy_absolute(void);

#endif /* COMPARE_H_ */
