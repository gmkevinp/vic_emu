/*
 * branch.c
 *
 *  Created on: Aug 27, 2012
 *      Author: kevin
 */

#include <stdlib.h>
#include "cpu6502.h"
#include "branch.h"

bool is_branch_op(uint8_t op)
{
    /* NOTE: branch opcode follow the pattern <odd><0> */
    return ((op & 0x1F) == 0x10);
}

uint16_t calc_branch_addr(uint16_t pc, uint8_t addr)
{
    if (addr & 0x80) {
        return cpu->pc + 2 + (0xFF00 | addr);
    } else {
        return cpu->pc + 2 + addr;
    }
}

void do_branch(addr)
{
    cpu->pc = calc_branch_addr(cpu->pc, addr);

    if (addr == 0xFE) {
        printf("Warning: Infinite loop at 0x%04X... exiting\n", cpu->pc);
        exit(0);
    }
}

void branch_if(uint8_t field, bool is_set)
{
    uint8_t  addr;

    addr = get_immediate();
    if (is_set == status_is_set(&cpu->status, field)) {
        do_branch(addr);
    } else {
        cpu->pc += 2;
    }
}

void bcs(void)
{
    branch_if(ST_CARRY, TRUE);
}

void bcc(void)
{
    branch_if(ST_CARRY, FALSE);
}

void beq(void)
{
    branch_if(ST_ZERO, TRUE);
}

void bne(void)
{
    branch_if(ST_ZERO, FALSE);
}

void bmi(void)
{
    branch_if(ST_NEG, TRUE);
}

void bpl(void)
{
    branch_if(ST_NEG, FALSE);
}

void bvs(void)
{
    branch_if(ST_OVRFL, TRUE);
}
void bvc(void)
{
    branch_if(ST_OVRFL, FALSE);
}


