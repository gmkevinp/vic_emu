/*
 * inst_db.c
 *
 *  Created on: Aug 26, 2012
 *      Author: kevin
 */
#include <stdint.h>
#include <stdbool.h>
#include "inst_db.h"
#include "math.h"
#include "bitops.h"
#include "branch.h"
#include "brk.h"
#include "compare.h"
#include "incdec.h"
#include "load.h"
#include "jump.h"
#include "nop.h"
#include "shift.h"
#include "stack.h"
#include "status.h"
#include "store.h"
#include "transfer.h"

inst_db_entry_st inst_db[] = {
		/* ADC - Done */
		{ .opcode = 0x69, .n_cycles = 2, .sz = 2, .pc_adv = true,  .format = "ADC #$%02X",      .func = adc_immediate, },
		{ .opcode = 0x65, .n_cycles = 3, .sz = 2, .pc_adv = true,  .format = "ADC $%02X",       .func = adc_zero_page, },
		{ .opcode = 0x75, .n_cycles = 4, .sz = 2, .pc_adv = true,  .format = "ADC $%02X, X",    .func = adc_zero_page_x, },
		{ .opcode = 0x6D, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "ADC $%04X",       .func = adc_absolute, },
		{ .opcode = 0x7D, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "ADC $%04X, X",    .func = adc_absolute_x, },
		{ .opcode = 0x79, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "ADC $%04X, Y",    .func = adc_absolute_y, },
		{ .opcode = 0x61, .n_cycles = 6, .sz = 2, .pc_adv = true,  .format = "ADC ($%02X, X)",  .func = adc_indirect_x, },
		{ .opcode = 0x71, .n_cycles = 5, .sz = 2, .pc_adv = true,  .format = "ADC ($%02X), Y",  .func = adc_indirect_y, },

		/* AND - Done */
		{ .opcode = 0x29, .n_cycles = 2, .sz = 2, .pc_adv = true,  .format = "AND #$%02X",      .func = and_immediate, },
		{ .opcode = 0x25, .n_cycles = 3, .sz = 2, .pc_adv = true,  .format = "AND $%02X",       .func = and_zero_page, },
		{ .opcode = 0x35, .n_cycles = 4, .sz = 2, .pc_adv = true,  .format = "AND $%02X, X",    .func = and_zero_page_x, },
		{ .opcode = 0x2D, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "AND $%04X",       .func = and_absolute, },
		{ .opcode = 0x3D, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "AND $%04X, X",    .func = and_absolute_x, },
		{ .opcode = 0x39, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "AND $%04X, Y",    .func = and_absolute_y, },
		{ .opcode = 0x21, .n_cycles = 6, .sz = 2, .pc_adv = true,  .format = "AND ($%02X, X)",  .func = and_indirect_x, },
		{ .opcode = 0x31, .n_cycles = 5, .sz = 2, .pc_adv = true,  .format = "AND ($%02X), Y",  .func = and_indirect_y, },

		/* ASL - Done */
		{ .opcode = 0x0A, .n_cycles = 2, .sz = 1, .pc_adv = true,  .format = "ASL",             .func = asl_accumulator, },
		{ .opcode = 0x06, .n_cycles = 5, .sz = 2, .pc_adv = true,  .format = "ASL $%02X",       .func = asl_zero_page, },
		{ .opcode = 0x16, .n_cycles = 6, .sz = 2, .pc_adv = true,  .format = "ASL $%02X, X",    .func = asl_zero_page_x, },
		{ .opcode = 0x0E, .n_cycles = 6, .sz = 3, .pc_adv = true,  .format = "ASL $%04X",       .func = asl_absolute, },
		{ .opcode = 0x1E, .n_cycles = 7, .sz = 3, .pc_adv = true,  .format = "ASL $%04X, X",    .func = asl_absolute_x, },

		/* Branches - Done */
		{ .opcode = 0x90, .n_cycles = 3, .sz = 2, .pc_adv = false, .format = "BCC $%04X",       .func = bcc, },
		{ .opcode = 0xB0, .n_cycles = 3, .sz = 2, .pc_adv = false, .format = "BCS $%04X",       .func = bcs, },
		{ .opcode = 0xF0, .n_cycles = 3, .sz = 2, .pc_adv = false, .format = "BEQ $%04X",       .func = beq, },
		{ .opcode = 0x30, .n_cycles = 3, .sz = 2, .pc_adv = false, .format = "BMI $%04X",       .func = bmi, },
		{ .opcode = 0xD0, .n_cycles = 3, .sz = 2, .pc_adv = false, .format = "BNE $%04X",       .func = bne, },
		{ .opcode = 0x10, .n_cycles = 3, .sz = 2, .pc_adv = false, .format = "BPL $%04X",       .func = bpl, },
		{ .opcode = 0x50, .n_cycles = 3, .sz = 2, .pc_adv = false, .format = "BVC $%04X",       .func = bvc, },
		{ .opcode = 0x70, .n_cycles = 3, .sz = 2, .pc_adv = false, .format = "BVS $%04X",       .func = bvs, },

		/* BIT */
		{ .opcode = 0x24, .n_cycles = 3, .sz = 2, .pc_adv = true,  .format = "BIT $%02X",       .func = bit_zero_page, },
		{ .opcode = 0x2C, .n_cycles = 4, .sz = 3, .pc_adv = false, .format = "BIT $%04X",       .func = bit_absolute, },

		/* BRK - Done */
		{ .opcode = 0x00, .n_cycles = 7, .sz = 1, .pc_adv = false, .format = "BRK",             .func = brk, },

		/* Clear Status - Done */
		{ .opcode = 0x18, .n_cycles = 2, .sz = 1, .pc_adv = true,  .format = "CLC",             .func = clc, },
		{ .opcode = 0xD8, .n_cycles = 2, .sz = 1, .pc_adv = true,  .format = "CLD",             .func = cld, },
		{ .opcode = 0x58, .n_cycles = 2, .sz = 1, .pc_adv = true,  .format = "CLI",             .func = cli, },
		{ .opcode = 0xB8, .n_cycles = 2, .sz = 1, .pc_adv = true,  .format = "CLV",             .func = clv, },

		/* Compare - Done */
		{ .opcode = 0xC9, .n_cycles = 2, .sz = 2, .pc_adv = true,  .format = "CMP #$%02X",      .func = cmp_immediate, },
		{ .opcode = 0xC5, .n_cycles = 3, .sz = 2, .pc_adv = true,  .format = "CMP $%02X",       .func = cmp_zero_page, },
		{ .opcode = 0xD5, .n_cycles = 4, .sz = 2, .pc_adv = true,  .format = "CMP $%02X, X",    .func = cmp_zero_page_x, },
		{ .opcode = 0xCD, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "CMP $%04X",       .func = cmp_absolute, },
		{ .opcode = 0xDD, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "CMP $%04X, X",    .func = cmp_absolute_x, },
		{ .opcode = 0xD9, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "CMP $%04X, Y",    .func = cmp_absolute_y, },
		{ .opcode = 0xC1, .n_cycles = 6, .sz = 2, .pc_adv = true,  .format = "CMP ($%02X, X)",  .func = cmp_indirect_x, },
		{ .opcode = 0xD1, .n_cycles = 5, .sz = 2, .pc_adv = true,  .format = "CMP ($%02X), Y",  .func = cmp_indirect_y, },

		/* CPX - Done */
		{ .opcode = 0xE0, .n_cycles = 2, .sz = 2, .pc_adv = true,  .format = "CPX #$%02X",      .func = cpx_immediate, },
		{ .opcode = 0xE4, .n_cycles = 3, .sz = 2, .pc_adv = true,  .format = "CPX $%02X",       .func = cpx_zero_page, },
		{ .opcode = 0xEC, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "CPX $%04X",       .func = cpx_absolute, },

		/* CPY - Done */
		{ .opcode = 0xC0, .n_cycles = 2, .sz = 2, .pc_adv = true,  .format = "CPY #$%02X",      .func = cpy_immediate, },
		{ .opcode = 0xC4, .n_cycles = 3, .sz = 2, .pc_adv = true,  .format = "CPY $%02X",       .func = cpy_zero_page, },
		{ .opcode = 0xCC, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "CPY $%04X",       .func = cpy_absolute, },

		/* Decrement - Done */
		{ .opcode = 0xC6, .n_cycles = 5, .sz = 2, .pc_adv = true,  .format = "DEC $%02X",       .func = dec_zero_page, },
		{ .opcode = 0xD6, .n_cycles = 6, .sz = 2, .pc_adv = true,  .format = "DEC $%02X, X",    .func = dec_zero_page_x, },
		{ .opcode = 0xCE, .n_cycles = 6, .sz = 3, .pc_adv = true,  .format = "DEC $%04X",       .func = dec_absolute, },
		{ .opcode = 0xDE, .n_cycles = 7, .sz = 3, .pc_adv = true,  .format = "DEC $%04X, X",    .func = dec_absolute_x, },
		{ .opcode = 0xCA, .n_cycles = 2, .sz = 1, .pc_adv = true,  .format = "DEX",             .func = dex, },
		{ .opcode = 0x88, .n_cycles = 2, .sz = 1, .pc_adv = true,  .format = "DEY",             .func = dey, },

		/* EOR - Done */
		{ .opcode = 0x49, .n_cycles = 2, .sz = 2, .pc_adv = true,  .format = "EOR #$%02X",      .func = eor_immediate, },
		{ .opcode = 0x45, .n_cycles = 3, .sz = 2, .pc_adv = true,  .format = "EOR $%02X",       .func = eor_zero_page, },
		{ .opcode = 0x55, .n_cycles = 4, .sz = 2, .pc_adv = true,  .format = "EOR $%02X, X",    .func = eor_zero_page_x, },
		{ .opcode = 0x4D, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "EOR $%04X",       .func = eor_absolute, },
		{ .opcode = 0x5D, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "EOR $%04X, X",    .func = eor_absolute_x, },
		{ .opcode = 0x59, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "EOR $%04X, Y",    .func = eor_absolute_y, },
		{ .opcode = 0x41, .n_cycles = 6, .sz = 2, .pc_adv = true,  .format = "EOR ($%02X, X)",  .func = eor_indirect_x, },
		{ .opcode = 0x51, .n_cycles = 5, .sz = 2, .pc_adv = true,  .format = "EOR ($%02X), Y",  .func = eor_indirect_y, },

		/* Increment - Done */
		{ .opcode = 0xE6, .n_cycles = 5, .sz = 2, .pc_adv = true,  .format = "INC $%02X",       .func = inc_zero_page, },
		{ .opcode = 0xF6, .n_cycles = 6, .sz = 2, .pc_adv = true,  .format = "INC $%02X",       .func = inc_zero_page_x, },
		{ .opcode = 0xEE, .n_cycles = 6, .sz = 3, .pc_adv = true,  .format = "INC $%04X",       .func = inc_absolute, },
		{ .opcode = 0xFE, .n_cycles = 7, .sz = 3, .pc_adv = true,  .format = "INC $%04X, X",    .func = inc_absolute_x, },
		{ .opcode = 0xE8, .n_cycles = 2, .sz = 1, .pc_adv = true,  .format = "INX",             .func = inx, },
		{ .opcode = 0xC8, .n_cycles = 2, .sz = 1, .pc_adv = true,  .format = "INY",             .func = iny, },

		/* Jump - Done */
		{ .opcode = 0x4C, .n_cycles = 3, .sz = 3, .pc_adv = false, .format = "JMP $%04X",       .func = jmp_absolute, },
		{ .opcode = 0x6C, .n_cycles = 5, .sz = 3, .pc_adv = false, .format = "JMP ($%04X)",     .func = jmp_indirect, },
		{ .opcode = 0x20, .n_cycles = 6, .sz = 3, .pc_adv = false, .format = "JSR $%04X",       .func = jsr, },

		/* LDA - Done */
		{ .opcode = 0xA9, .n_cycles = 2, .sz = 2, .pc_adv = true,  .format = "LDA #$%02X",      .func = lda_immediate, },
		{ .opcode = 0xA5, .n_cycles = 3, .sz = 2, .pc_adv = true,  .format = "LDA $%02X",       .func = lda_zero_page, },
		{ .opcode = 0xB5, .n_cycles = 4, .sz = 2, .pc_adv = true,  .format = "LDA $%02X, X",    .func = lda_zero_page_x, },
		{ .opcode = 0xAD, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "LDA $%04X",       .func = lda_absolute, },
		{ .opcode = 0xBD, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "LDA $%04X, X",    .func = lda_absolute_x, },
		{ .opcode = 0xB9, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "LDA $%04X, Y",    .func = lda_absolute_y, },
		{ .opcode = 0xA1, .n_cycles = 6, .sz = 2, .pc_adv = true,  .format = "LDA ($%02X, X)",  .func = lda_indirect_x, },
		{ .opcode = 0xB1, .n_cycles = 5, .sz = 2, .pc_adv = true,  .format = "LDA ($%02X), Y",  .func = lda_indirect_y, },

		/* LDX - Done */
		{ .opcode = 0xA2, .n_cycles = 2, .sz = 2, .pc_adv = true,  .format = "LDX #$%02X",      .func = ldx_immediate, },
		{ .opcode = 0xA6, .n_cycles = 3, .sz = 2, .pc_adv = true,  .format = "LDX $%02X",       .func = ldx_zero_page, },
		{ .opcode = 0xB6, .n_cycles = 4, .sz = 2, .pc_adv = true,  .format = "LDX $%02X, Y",    .func = ldx_zero_page_y, },
		{ .opcode = 0xAE, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "LDX $%04X",       .func = ldx_absolute, },
		{ .opcode = 0xBE, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "LDX $%04X, Y",    .func = ldx_absolute_y, },

		/* LDY - Done */
		{ .opcode = 0xA0, .n_cycles = 2, .sz = 2, .pc_adv = true,  .format = "LDY #$%02X",      .func = ldy_immediate, },
		{ .opcode = 0xA4, .n_cycles = 3, .sz = 2, .pc_adv = true,  .format = "LDY $%02X",       .func = ldy_zero_page, },
		{ .opcode = 0xB4, .n_cycles = 4, .sz = 2, .pc_adv = true,  .format = "LDY $%02X, X",    .func = ldy_zero_page_x, },
		{ .opcode = 0xAC, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "LDY $%04X",       .func = ldy_absolute, },
		{ .opcode = 0xBC, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "LDY $%04X, X",    .func = ldy_absolute_x, },

		/* LSR Needs to be implemented! */
		{ .opcode = 0x4A, .n_cycles = 2, .sz = 1, .pc_adv = true,  .format = "LSR A",           .func = lsr_accumulator, },
		{ .opcode = 0x46, .n_cycles = 5, .sz = 2, .pc_adv = true,  .format = "LSR $%02X",       .func = lsr_zero_page, },
		{ .opcode = 0x56, .n_cycles = 6, .sz = 2, .pc_adv = true,  .format = "LSR $%02X, X",    .func = lsr_zero_page_x, },
		{ .opcode = 0x4E, .n_cycles = 6, .sz = 3, .pc_adv = true,  .format = "LSR $%04X",       .func = lsr_absolute, },
		{ .opcode = 0x5E, .n_cycles = 7, .sz = 3, .pc_adv = true,  .format = "LSR $%04X, X",    .func = lsr_absolute_x, },

		/* NOP - Done */
		{ .opcode = 0xEA, .n_cycles = 2, .sz = 1, .pc_adv = true,  .format = "NOP",             .func = nop, },

		/* ORA - Done */
		{ .opcode = 0x09, .n_cycles = 2, .sz = 2, .pc_adv = true,  .format = "ORA #$%02X",      .func = ora_immediate, },
		{ .opcode = 0x05, .n_cycles = 3, .sz = 2, .pc_adv = true,  .format = "ORA $%02X",       .func = ora_zero_page, },
		{ .opcode = 0x15, .n_cycles = 4, .sz = 2, .pc_adv = true,  .format = "ORA $%02X, X",    .func = ora_zero_page_x, },
		{ .opcode = 0x0D, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "ORA $%04X",       .func = ora_absolute, },
		{ .opcode = 0x1D, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "ORA $%04X, X",    .func = ora_absolute_x, },
		{ .opcode = 0x19, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "ORA $%04X, Y",    .func = ora_absolute_y, },
		{ .opcode = 0x01, .n_cycles = 6, .sz = 2, .pc_adv = true,  .format = "ORA ($%02X, X)",  .func = ora_indirect_x, },
		{ .opcode = 0x11, .n_cycles = 5, .sz = 2, .pc_adv = true,  .format = "ORA ($%02X), Y",  .func = ora_indirect_y, },

		/* Stack push/pull */
		{ .opcode = 0x48, .n_cycles = 3, .sz = 1, .pc_adv = true,  .format = "PHA",             .func = pha, },
		{ .opcode = 0x08, .n_cycles = 3, .sz = 1, .pc_adv = true,  .format = "PHP",             .func = php, },
		{ .opcode = 0x68, .n_cycles = 4, .sz = 1, .pc_adv = true,  .format = "PLA",             .func = pla, },
		{ .opcode = 0x28, .n_cycles = 4, .sz = 1, .pc_adv = true,  .format = "PLP",             .func = plp, },

		/* ROL - Done */
		{ .opcode = 0x2A, .n_cycles = 2, .sz = 1, .pc_adv = true,  .format = "ROL",             .func = rol_accumulator, },
		{ .opcode = 0x26, .n_cycles = 5, .sz = 2, .pc_adv = true,  .format = "ROL $%02X",       .func = rol_zero_page, },
		{ .opcode = 0x36, .n_cycles = 6, .sz = 2, .pc_adv = true,  .format = "ROL $%02X, X",    .func = rol_zero_page_x, },
		{ .opcode = 0x2E, .n_cycles = 6, .sz = 3, .pc_adv = true,  .format = "ROL $%04X",       .func = rol_absolute, },
		{ .opcode = 0x3E, .n_cycles = 7, .sz = 3, .pc_adv = true,  .format = "ROL $%04X, X",    .func = rol_absolute_x, },

		/* ROR - Done */
		{ .opcode = 0x6A, .n_cycles = 2, .sz = 1, .pc_adv = true,  .format = "ROR",             .func = ror_accumulator, },
		{ .opcode = 0x66, .n_cycles = 5, .sz = 2, .pc_adv = true,  .format = "ROR $%02X",       .func = ror_zero_page, },
		{ .opcode = 0x76, .n_cycles = 6, .sz = 2, .pc_adv = true,  .format = "ROR $%02X, X",    .func = ror_zero_page_x, },
		{ .opcode = 0x6E, .n_cycles = 6, .sz = 3, .pc_adv = true,  .format = "ROR $%04X",       .func = ror_absolute, },
		{ .opcode = 0x7E, .n_cycles = 7, .sz = 3, .pc_adv = true,  .format = "ROR $%04X, X",    .func = ror_absolute_x, },

		/* RTI/RTS - Done */
		{ .opcode = 0x4D, .n_cycles = 6, .sz = 1, .pc_adv = false, .format = "RTI",             .func = rti, },
		{ .opcode = 0x60, .n_cycles = 6, .sz = 1, .pc_adv = false, .format = "RTS",             .func = rts, },

		/* SBC - Done */
		{ .opcode = 0xE9, .n_cycles = 2, .sz = 2, .pc_adv = true,  .format = "SBC #$%02X",      .func = sbc_immediate, },
		{ .opcode = 0xE5, .n_cycles = 3, .sz = 2, .pc_adv = true,  .format = "SBC $%02X",       .func = sbc_zero_page, },
		{ .opcode = 0xF5, .n_cycles = 4, .sz = 2, .pc_adv = true,  .format = "SBC $%02X, X",    .func = sbc_zero_page_x, },
		{ .opcode = 0xED, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "SBC $%04X",       .func = sbc_absolute, },
		{ .opcode = 0xFD, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "SBC $%04X, X",    .func = sbc_absolute_x, },
		{ .opcode = 0xF9, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "SBC $%04X, Y",    .func = sbc_absolute_y, },
		{ .opcode = 0xE1, .n_cycles = 6, .sz = 2, .pc_adv = true,  .format = "SBC ($%02X, X)",  .func = sbc_indirect_x, },
		{ .opcode = 0xF1, .n_cycles = 5, .sz = 2, .pc_adv = true,  .format = "SBC ($%02X), Y",  .func = sbc_indirect_y, },

		/* Set Status - Done */
		{ .opcode = 0x38, .n_cycles = 2, .sz = 1, .pc_adv = true,  .format = "SEC",             .func = sec, },
		{ .opcode = 0xF8, .n_cycles = 2, .sz = 1, .pc_adv = true,  .format = "SED",             .func = sed, },
		{ .opcode = 0x78, .n_cycles = 2, .sz = 1, .pc_adv = true,  .format = "SEI",             .func = sei, },

		/* STA - Done */
		{ .opcode = 0x85, .n_cycles = 3, .sz = 2, .pc_adv = true,  .format = "STA $%02X",       .func = sta_zero_page, },
		{ .opcode = 0x95, .n_cycles = 4, .sz = 2, .pc_adv = true,  .format = "STA $%02X, X",    .func = sta_zero_page_x, },
		{ .opcode = 0x8D, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "STA $%04X",       .func = sta_absolute, },
		{ .opcode = 0x9D, .n_cycles = 5, .sz = 3, .pc_adv = true,  .format = "STA $%04X, X",    .func = sta_absolute_x, },
		{ .opcode = 0x99, .n_cycles = 5, .sz = 3, .pc_adv = true,  .format = "STA $%04X, Y",    .func = sta_absolute_y, },
		{ .opcode = 0x81, .n_cycles = 6, .sz = 2, .pc_adv = true,  .format = "STA ($%02X, X)",  .func = sta_indirect_x, },
		{ .opcode = 0x91, .n_cycles = 6, .sz = 2, .pc_adv = true,  .format = "STA ($%02X), Y",  .func = sta_indirect_y, },

		/* STX - Done */
		{ .opcode = 0x86, .n_cycles = 3, .sz = 2, .pc_adv = true,  .format = "STX $%02X",       .func = stx_zero_page, },
		{ .opcode = 0x96, .n_cycles = 4, .sz = 2, .pc_adv = true,  .format = "STX $%02X, Y",    .func = stx_zero_page_y, },
		{ .opcode = 0x8E, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "STX $%04X",       .func = stx_absolute, },

		/* STY - Done */
		{ .opcode = 0x84, .n_cycles = 3, .sz = 2, .pc_adv = true,  .format = "STY $%02X",       .func = sty_zero_page, },
		{ .opcode = 0x94, .n_cycles = 4, .sz = 2, .pc_adv = true,  .format = "STY $%02X, X",    .func = sty_zero_page_x, },
		{ .opcode = 0x8C, .n_cycles = 4, .sz = 3, .pc_adv = true,  .format = "STY $%04X",       .func = sty_absolute, },

		/* Set Status - Done */
		{ .opcode = 0xAA, .n_cycles = 2, .sz = 1, .pc_adv = true,  .format = "TAX",             .func = tax, },
		{ .opcode = 0xA8, .n_cycles = 2, .sz = 1, .pc_adv = true,  .format = "TAY",             .func = tay, },
		{ .opcode = 0xBA, .n_cycles = 2, .sz = 1, .pc_adv = true,  .format = "TSX",             .func = tsx, },
		{ .opcode = 0x8A, .n_cycles = 2, .sz = 1, .pc_adv = true,  .format = "TXA",             .func = txa, },
		{ .opcode = 0x9A, .n_cycles = 2, .sz = 1, .pc_adv = true,  .format = "TXS",             .func = txs, },
		{ .opcode = 0x98, .n_cycles = 2, .sz = 1, .pc_adv = true,  .format = "TYA",             .func = tya, },

};

uint8_t inst_db_num_entries = (sizeof(inst_db) / sizeof(inst_db[0]));
