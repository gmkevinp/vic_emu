/*
 * status_reg.h
 *
 *  Created on: Aug 26, 2012
 *      Author: kevin
 */

#ifndef STATUS_REG_H_
#define STATUS_REG_H_
#include <stdint.h>

typedef uint8_t status_reg_t;

#define ST_CARRY  0x01
#define ST_ZERO   0x02
#define ST_IRQ    0x04
#define ST_DEC    0x08
#define ST_BRK    0x10
#define ST_UNDEF  0x20
#define ST_OVRFL  0x40
#define ST_NEG    0x80

void status_reg_init(status_reg_t *status);
void status_reg_dump(status_reg_t *status);
void status_reg_mask_and_set(status_reg_t *status, uint8_t mask, uint8_t fields);
void status_reg_set(status_reg_t *status, uint8_t fields);
void status_reg_clr(status_reg_t *status, uint8_t fields);
uint8_t status_is_set(status_reg_t *status, uint8_t fields);

#endif /* STATUS_REG_H_ */
