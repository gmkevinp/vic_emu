/*
 * shift.h
 *
 *  Created on: Aug 29, 2012
 *      Author: kevin
 */

#ifndef SHIFT_H_
#define SHIFT_H_

void asl_accumulator(void);
void asl_zero_page(void);
void asl_zero_page_x(void);
void asl_absolute(void);
void asl_absolute_x(void);

void lsr_accumulator(void);
void lsr_zero_page(void);
void lsr_zero_page_x(void);
void lsr_absolute(void);
void lsr_absolute_x(void);

void rol_accumulator(void);
void rol_zero_page(void);
void rol_zero_page_x(void);
void rol_absolute(void);
void rol_absolute_x(void);

void ror_accumulator(void);
void ror_zero_page(void);
void ror_zero_page_x(void);
void ror_absolute(void);
void ror_absolute_x(void);

#endif /* SHIFT_H_ */
