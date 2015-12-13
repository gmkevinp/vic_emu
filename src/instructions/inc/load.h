/*
 * load.h
 *
 *  Created on: Aug 29, 2012
 *      Author: kevin
 */

#ifndef LOAD_H_
#define LOAD_H_

void lda_immediate(void);
void lda_zero_page(void);
void lda_zero_page_x(void);
void lda_absolute(void);
void lda_absolute_x(void);
void lda_absolute_y(void);
void lda_indirect_x(void);
void lda_indirect_y(void);

void ldx_immediate(void);
void ldx_zero_page(void);
void ldx_zero_page_y(void);
void ldx_absolute(void);
void ldx_absolute_y(void);

void ldy_immediate(void);
void ldy_zero_page(void);
void ldy_zero_page_x(void);
void ldy_absolute(void);
void ldy_absolute_x(void);


#endif /* LOAD_H_ */
