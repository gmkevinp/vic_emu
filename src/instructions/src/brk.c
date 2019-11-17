/*
 * brk.c
 *
 *  Created on: Aug 26, 2012
 *      Author: kevin
 */
#include <stdio.h>
#include "cpu6502.h"
#include "brk.h"

void brk(void)
{
	pc_reg_inc(&cpu->pc, 2);
	cpu6502_irq(CPU6502_BRK);
}
