/*
 * and.h
 *
 *  Created on: Aug 27, 2012
 *      Author: kevin
 */

#ifndef AND_H_
#define AND_H_

void and_immediate(void);
void and_zero_page(void);
void and_zero_page_x(void);
void and_absolute(void);
void and_absolute_x(void);
void and_absolute_y(void);
void and_indirect_x(void);
void and_indirect_y(void);

void bit_zero_page(void);
void bit_absolute(void);

void eor_immediate(void);
void eor_zero_page(void);
void eor_zero_page_x(void);
void eor_absolute(void);
void eor_absolute_x(void);
void eor_absolute_y(void);
void eor_indirect_x(void);
void eor_indirect_y(void);

void ora_immediate(void);
void ora_zero_page(void);
void ora_zero_page_x(void);
void ora_absolute(void);
void ora_absolute_x(void);
void ora_absolute_y(void);
void ora_indirect_x(void);
void ora_indirect_y(void);

#endif /* AND_H_ */
