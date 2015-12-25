/*
 * status_reg.c
 *
 *  Created on: Aug 26, 2012
 *      Author: kevin
 */
#include <stdio.h>
#include "status_reg.h"


void status_reg_init(status_reg_t *status_reg)
{
	status_reg_set(status_reg, 0);
}

void status_reg_dump(status_reg_t *status)
{
	printf("status: 0x%02X\n", *status);
}

void status_reg_mask_and_set(status_reg_t *status, uint8_t mask, uint8_t fields)
{
	status_reg_clr(status, mask);
	status_reg_set(status, fields);
}

void status_reg_set(status_reg_t *status, uint8_t fields)
{
	*status |= (fields | ST_UNDEF | ST_BRK);
}

void status_reg_clr(status_reg_t *status, uint8_t fields)
{
	*status &= ~fields;
	*status |= ST_UNDEF | ST_BRK;
}

uint8_t status_is_set(status_reg_t *status, uint8_t fields)
{
	return ((*status & fields) == fields);
}
