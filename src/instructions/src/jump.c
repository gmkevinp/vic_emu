/*
 * jump.c
 *
 *  Created on: Aug 27, 2012
 *      Author: kevin
 */
#include "cpu6502.h"
#include "jump.h"
#include "stack.h"

void jmp_absolute(void)
{
    uint16_t  addr;

    addr = get_absolute_addr(0);
    pc_reg_set(&cpu->pc, addr);
}

void jmp_indirect(void)
{
    uint16_t  addr;

    addr = get_indirect_addr();
    pc_reg_set(&cpu->pc, addr);
}

void jsr(void)
{
    uint16_t  jmp_addr;
    uint16_t  ret_addr;
    uint8_t   addr_hi;
    uint8_t   addr_lo;

    jmp_addr = get_absolute_addr(0);

    /* Save return address to stack */
    ret_addr = (cpu->pc+2);
    addr_hi = (ret_addr & 0xFF00) >> 8;
    addr_lo = (ret_addr & 0x00FF);
    stack_push(addr_hi);
    stack_push(addr_lo);

    pc_reg_set(&cpu->pc, jmp_addr);
}

void rti(void)
{
    uint16_t  addr;
    uint8_t   addr_hi;
    uint8_t   addr_lo;
    uint8_t   status;

    status = stack_pop();
    addr_lo = stack_pop();
    addr_hi = stack_pop();
    addr = (addr_hi << 8) | addr_lo;

    pc_reg_set(&cpu->pc, addr);
    cpu->status = status;
}

void rts(void)
{
    uint16_t  addr;
    uint8_t   addr_hi;
    uint8_t   addr_lo;

    addr_lo = stack_pop();
    addr_hi = stack_pop();
    addr = (addr_hi << 8) | addr_lo;

    pc_reg_set(&cpu->pc, addr + 1);
}
