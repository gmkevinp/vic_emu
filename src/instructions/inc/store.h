/*
 * store.h
 *
 *  Created on: Aug 29, 2012
 *      Author: kevin
 */

#ifndef STORE_H_
#define STORE_H_

void sta_zero_page(void);
void sta_zero_page_x(void);
void sta_absolute(void);
void sta_absolute_x(void);
void sta_absolute_y(void);
void sta_indirect_x(void);
void sta_indirect_y(void);

void stx_zero_page(void);
void stx_zero_page_y(void);
void stx_absolute(void);

void sty_zero_page(void);
void sty_zero_page_x(void);
void sty_absolute(void);

#endif /* STORE_H_ */
