/*
 * adc.h
 *
 *  Created on: Aug 26, 2012
 *      Author: kevin
 */

#ifndef ADC_H_
#define ADC_H_

void adc_immediate(void);
void adc_zero_page(void);
void adc_zero_page_x(void);
void adc_absolute(void);
void adc_absolute_x(void);
void adc_absolute_y(void);
void adc_indirect_x(void);
void adc_indirect_y(void);

void sbc_immediate(void);
void sbc_zero_page(void);
void sbc_zero_page_x(void);
void sbc_absolute(void);
void sbc_absolute_x(void);
void sbc_absolute_y(void);
void sbc_indirect_x(void);
void sbc_indirect_y(void);

#endif /* ADC_H_ */
