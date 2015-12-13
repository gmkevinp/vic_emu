/*
 * incdec.h
 *
 *  Created on: Aug 27, 2012
 *      Author: kevin
 */

#ifndef INCDEC_H_
#define INCDEC_H_

void dec_zero_page(void);
void dec_zero_page_x(void);
void dec_absolute(void);
void dec_absolute_x(void);
void dex(void);
void dey(void);

void inc_zero_page(void);
void inc_zero_page_x(void);
void inc_absolute(void);
void inc_absolute_x(void);
void inx(void);
void iny(void);

#endif /* INCDEC_H_ */
