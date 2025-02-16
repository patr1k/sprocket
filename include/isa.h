#pragma once

#include <stdlib.h>
#include <memory.h>

#include "cpu.h"

#define FETCH_BYTE() (dev->mem[dev->cpu.PC.val++])
#define FETCH_WORD() (dev->mem[dev->cpu.PC.val++] | (dev->mem[dev->cpu.PC.val++] << 8))

#define STACK_PUSH(byte) dev->mem[dev->cpu.SP.val++] = byte
#define STACK_POP() --dev->cpu.SP.val

#define CPU_INSTR(name) void cpu_##name(struct gbc *dev)

#define DECOMP_ON 1
// Decompilation logging
#ifdef DECOMP_ON
#include <stdio.h>
#define DECOMP(str, ...) printf(str "\n" __VA_OPT__(,) __VA_ARGS__);
#else
#define DECOMP(...)
#endif

/**
 * Block 0 Instructions
 */
CPU_INSTR(nop);

CPU_INSTR(ld_BC_d16);
CPU_INSTR(ld_DE_d16);
CPU_INSTR(ld_HL_d16);
CPU_INSTR(ld_SP_d16);

CPU_INSTR(ld_BCmem_A);
CPU_INSTR(ld_DEmem_A);
CPU_INSTR(ld_HLi_A);
CPU_INSTR(ld_HLd_A);

CPU_INSTR(ld_A_BCmem);
CPU_INSTR(ld_A_DEmem);
CPU_INSTR(ld_A_HLi);
CPU_INSTR(ld_A_HLd);

CPU_INSTR(ld_a16_SP);

CPU_INSTR(inc_BC);
CPU_INSTR(inc_DE);
CPU_INSTR(inc_HL);
CPU_INSTR(inc_SP);

CPU_INSTR(dec_BC);
CPU_INSTR(dec_DE);
CPU_INSTR(dec_HL);
CPU_INSTR(dec_SP);

CPU_INSTR(add_HL_BC);
CPU_INSTR(add_HL_DE);
CPU_INSTR(add_HL_HL);
CPU_INSTR(add_HL_SP);

CPU_INSTR(inc_B);
CPU_INSTR(inc_C);
CPU_INSTR(inc_D);
CPU_INSTR(inc_E);
CPU_INSTR(inc_H);
CPU_INSTR(inc_L);
CPU_INSTR(inc_HLmem);
CPU_INSTR(inc_A);

CPU_INSTR(dec_B);
CPU_INSTR(dec_C);
CPU_INSTR(dec_D);
CPU_INSTR(dec_E);
CPU_INSTR(dec_H);
CPU_INSTR(dec_L);
CPU_INSTR(dec_HLmem);
CPU_INSTR(dec_A);

CPU_INSTR(ld_B_d8);
CPU_INSTR(ld_C_d8);
CPU_INSTR(ld_D_d8);
CPU_INSTR(ld_E_d8);
CPU_INSTR(ld_H_d8);
CPU_INSTR(ld_L_d8);
CPU_INSTR(ld_HLmem_d8);
CPU_INSTR(ld_A_d8);

CPU_INSTR(rlca);
CPU_INSTR(rrca);
CPU_INSTR(rla);
CPU_INSTR(rra);

CPU_INSTR(daa);
CPU_INSTR(cpl);

CPU_INSTR(scf);
CPU_INSTR(ccf);

CPU_INSTR(jr_r8);
CPU_INSTR(jr_nz_r8);
CPU_INSTR(jr_z_r8);
CPU_INSTR(jr_nc_r8);
CPU_INSTR(jr_c_r8);

CPU_INSTR(stop);

/**
 * Block 1 Instructions
 */
CPU_INSTR(halt);

CPU_INSTR(ld_B_B);
CPU_INSTR(ld_B_C);
CPU_INSTR(ld_B_D);
CPU_INSTR(ld_B_E);
CPU_INSTR(ld_B_H);
CPU_INSTR(ld_B_L);
CPU_INSTR(ld_B_HLmem);
CPU_INSTR(ld_B_A);

CPU_INSTR(ld_C_B);
CPU_INSTR(ld_C_C);
CPU_INSTR(ld_C_D);
CPU_INSTR(ld_C_E);
CPU_INSTR(ld_C_H);
CPU_INSTR(ld_C_L);
CPU_INSTR(ld_C_HLmem);
CPU_INSTR(ld_C_A);

CPU_INSTR(ld_D_B);
CPU_INSTR(ld_D_C);
CPU_INSTR(ld_D_D);
CPU_INSTR(ld_D_E);
CPU_INSTR(ld_D_H);
CPU_INSTR(ld_D_L);
CPU_INSTR(ld_D_HLmem);
CPU_INSTR(ld_D_A);

CPU_INSTR(ld_E_B);
CPU_INSTR(ld_E_C);
CPU_INSTR(ld_E_D);
CPU_INSTR(ld_E_E);
CPU_INSTR(ld_E_H);
CPU_INSTR(ld_E_L);
CPU_INSTR(ld_E_HLmem);
CPU_INSTR(ld_E_A);

CPU_INSTR(ld_H_B);
CPU_INSTR(ld_H_C);
CPU_INSTR(ld_H_D);
CPU_INSTR(ld_H_E);
CPU_INSTR(ld_H_H);
CPU_INSTR(ld_H_L);
CPU_INSTR(ld_H_HLmem);
CPU_INSTR(ld_H_A);

CPU_INSTR(ld_L_B);
CPU_INSTR(ld_L_C);
CPU_INSTR(ld_L_D);
CPU_INSTR(ld_L_E);
CPU_INSTR(ld_L_H);
CPU_INSTR(ld_L_L);
CPU_INSTR(ld_L_HLmem);
CPU_INSTR(ld_L_A);

CPU_INSTR(ld_HLmem_B);
CPU_INSTR(ld_HLmem_C);
CPU_INSTR(ld_HLmem_D);
CPU_INSTR(ld_HLmem_E);
CPU_INSTR(ld_HLmem_H);
CPU_INSTR(ld_HLmem_L);
CPU_INSTR(ld_HLmem_A);

CPU_INSTR(ld_A_B);
CPU_INSTR(ld_A_C);
CPU_INSTR(ld_A_D);
CPU_INSTR(ld_A_E);
CPU_INSTR(ld_A_H);
CPU_INSTR(ld_A_L);
CPU_INSTR(ld_A_HLmem);
CPU_INSTR(ld_A_A);

/**
 * Block 2 Instructions
 */
CPU_INSTR(add_A_B);
CPU_INSTR(add_A_C);
CPU_INSTR(add_A_D);
CPU_INSTR(add_A_E);
CPU_INSTR(add_A_H);
CPU_INSTR(add_A_L);
CPU_INSTR(add_A_HLmem);
CPU_INSTR(add_A_A);

CPU_INSTR(adc_A_B);
CPU_INSTR(adc_A_C);
CPU_INSTR(adc_A_D);
CPU_INSTR(adc_A_E);
CPU_INSTR(adc_A_H);
CPU_INSTR(adc_A_L);
CPU_INSTR(adc_A_HLmem);
CPU_INSTR(adc_A_A);