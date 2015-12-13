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
	cpu6502_halt("BRK");
}
