#pragma once

#include <stdint.h>

// Decompilation logging
#ifdef DECOMP_ON
#define DECOMP(str, ...) printf(str "\n" __VA_OPT__(,) __VA_ARGS__);
#else
#define DECOMP(...)
#endif

// Used to declare definitions for CPU instructions
#define DEF_INSTR(instr, ...) void cpu_##instr(struct gbc* __VA_OPT__(,) __VA_ARGS__);

// Arguments for CPU instructions
#define ARG_R8 enum cpu_reg_r8      // 8-bit Register
#define ARG_R16 enum cpu_reg_r16    // 16-bit Register
#define ARG_IMM8 uint8_t            // Immediate Unsigned 8-bit Value
#define ARG_IMM16 uint16_t          // Immediate Unsigned 16-bit Value
#define ARG_IMM8S int8_t            // Immediate Signed 8-bit Value
#define ARG_IMM16S int16_t          // Immediate Signed 16-bit Value
#define ARG_COND enum cpu_flag_cond // Flag Condition

// Block 0 Instructions
DEF_INSTR(nop)
DEF_INSTR(ld_r16_imm16, ARG_R16, ARG_IMM16)
DEF_INSTR(ld_r16mem_a, ARG_R16)
DEF_INSTR(ld_a_r16mem, ARG_R16)
DEF_INSTR(ld_imm16_sp, ARG_IMM16)
DEF_INSTR(inc_r16, ARG_R16)
DEF_INSTR(dec_r16, ARG_R16)
DEF_INSTR(add_hl_r16, ARG_R16)
DEF_INSTR(inc_r8, ARG_R8)
DEF_INSTR(dec_r8, ARG_R8)
DEF_INSTR(ld_r8_imm8, ARG_R8, ARG_IMM8)
DEF_INSTR(rlca)
DEF_INSTR(rrca)
DEF_INSTR(rla)
DEF_INSTR(rra)
DEF_INSTR(daa)
DEF_INSTR(cpl)
DEF_INSTR(scf)
DEF_INSTR(ccf)
DEF_INSTR(jr_imm8, ARG_IMM8S)
DEF_INSTR(jr_cond_imm8, ARG_COND, ARG_IMM8S)
DEF_INSTR(stop)

// Block 1 Instructions
DEF_INSTR(ld_r8_r8, ARG_R8, ARG_R8)
DEF_INSTR(halt)
DEF_INSTR(add_a_r8, ARG_R8)