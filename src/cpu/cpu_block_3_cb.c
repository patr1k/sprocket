/**
 * CPU Block 3 (0xCB Extension) Instructions
 */

#include "cpu_isa.h"

#define BIT_U3_R8(bit, r8, r16) CPU_INSTR(bit_##bit_##r8) \
    { \
        DECOMP("BIT " #bit ", " #r8) \
        dev->cpu.AF.flag.Z = (dev->cpu.BC.byte.B & (1 << 0)) == 0; \
        dev->cpu.AF.flag.N = 0; \
        dev->cpu.AF.flag.H = 1; \
    }

#define BIT_U3_HLMEM(bit) CPU_INSTR(bit_##bit_HLmem) \
    { \
        DECOMP("BIT " #bit ", [HL]") \
        dev->cpu.AF.flag.Z = (dev->mem[dev->cpu.HL.val] & (1 << 0)) == 0; \
        dev->cpu.AF.flag.N = 0; \
        dev->cpu.AF.flag.H = 1; \
    }

BIT_U3_R8(0, B, BC)
BIT_U3_R8(1, B, BC)
BIT_U3_R8(2, B, BC)
BIT_U3_R8(3, B, BC)
BIT_U3_R8(4, B, BC)
BIT_U3_R8(5, B, BC)
BIT_U3_R8(6, B, BC)
BIT_U3_R8(7, B, BC)

BIT_U3_R8(0, C, BC)
BIT_U3_R8(1, C, BC)
BIT_U3_R8(2, C, BC)
BIT_U3_R8(3, C, BC)
BIT_U3_R8(4, C, BC)
BIT_U3_R8(5, C, BC)
BIT_U3_R8(6, C, BC)
BIT_U3_R8(7, C, BC)

BIT_U3_R8(0, D, DE)
BIT_U3_R8(1, D, DE)
BIT_U3_R8(2, D, DE)
BIT_U3_R8(3, D, DE)
BIT_U3_R8(4, D, DE)
BIT_U3_R8(5, D, DE)
BIT_U3_R8(6, D, DE)
BIT_U3_R8(7, D, DE)

BIT_U3_R8(0, E, DE)
BIT_U3_R8(1, E, DE)
BIT_U3_R8(2, E, DE)
BIT_U3_R8(3, E, DE)
BIT_U3_R8(4, E, DE)
BIT_U3_R8(5, E, DE)
BIT_U3_R8(6, E, DE)
BIT_U3_R8(7, E, DE)

BIT_U3_R8(0, H, HL)
BIT_U3_R8(1, H, HL)
BIT_U3_R8(2, H, HL)
BIT_U3_R8(3, H, HL)
BIT_U3_R8(4, H, HL)
BIT_U3_R8(5, H, HL)
BIT_U3_R8(6, H, HL)
BIT_U3_R8(7, H, HL)

BIT_U3_R8(0, L, HL)
BIT_U3_R8(1, L, HL)
BIT_U3_R8(2, L, HL)
BIT_U3_R8(3, L, HL)
BIT_U3_R8(4, L, HL)
BIT_U3_R8(5, L, HL)
BIT_U3_R8(6, L, HL)
BIT_U3_R8(7, L, HL)

BIT_U3_HLMEM(0)
BIT_U3_HLMEM(1)
BIT_U3_HLMEM(2)
BIT_U3_HLMEM(3)
BIT_U3_HLMEM(4)
BIT_U3_HLMEM(5)
BIT_U3_HLMEM(6)
BIT_U3_HLMEM(7)

BIT_U3_R8(0, A, AF)
BIT_U3_R8(1, A, AF)
BIT_U3_R8(2, A, AF)
BIT_U3_R8(3, A, AF)
BIT_U3_R8(4, A, AF)
BIT_U3_R8(5, A, AF)
BIT_U3_R8(6, A, AF)
BIT_U3_R8(7, A, AF)

#define RLC_R8(r8, r16) CPU_INSTR(rlc_##r8) \
    { \
        DECOMP("RLC " #r8) \
        uint8_t carry = (dev->cpu.r16.byte.r8 & 0x80) ? 1 : 0; \
        dev->cpu.r16.byte.r8 = (dev->cpu.r16.byte.r8 << 1) | carry; \
        dev->cpu.AF.flag.Z = dev->cpu.r16.byte.r8 == 0; \
        dev->cpu.AF.flag.N = 0; \
        dev->cpu.AF.flag.H = 0; \
        dev->cpu.AF.flag.C = carry; \
    }

RLC_R8(B, BC)
RLC_R8(C, BC)
RLC_R8(D, DE)
RLC_R8(E, DE)
RLC_R8(H, HL)
RLC_R8(L, HL)
RLC_R8(A, AF)
CPU_INSTR(rlc_HLmem)
{
    DECOMP("RLC [HL]")

    uint8_t carry = (dev->mem[dev->cpu.HL.val] & 0x80) ? 1 : 0;
    dev->mem[dev->cpu.HL.val] = (dev->mem[dev->cpu.HL.val] << 1) | carry;

    dev->cpu.AF.flag.Z = dev->mem[dev->cpu.HL.val] == 0;
    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.H = 0;
    dev->cpu.AF.flag.C = carry;
}

#define RRC_R8(r8, r16) CPU_INSTR(rrc_##r8) \
    { \
        DECOMP("RLC " #r8) \
        uint8_t carry = (dev->cpu.r16.byte.r8 & 0x01) ? 1 : 0; \
        dev->cpu.r16.byte.r8 = (dev->cpu.r16.byte.r8 >> 1) | (carry ? 0x80 : 0); \
        dev->cpu.AF.flag.Z = dev->cpu.r16.byte.r8 == 0; \
        dev->cpu.AF.flag.N = 0; \
        dev->cpu.AF.flag.H = 0; \
        dev->cpu.AF.flag.C = carry; \
    }

RRC_R8(B, BC)
RRC_R8(C, BC)
RRC_R8(D, DE)
RRC_R8(E, DE)
RRC_R8(H, HL)
RRC_R8(L, HL)
RRC_R8(A, AF)
CPU_INSTR(rrc_HLmem)
{
    DECOMP("RRC [HL]")

    uint8_t carry = (dev->mem[dev->cpu.HL.val] & 0x01) ? 1 : 0;
    dev->mem[dev->cpu.HL.val] = (dev->mem[dev->cpu.HL.val] >> 1) | (carry ? 0x80 : 0);
    
    dev->cpu.AF.flag.Z = dev->mem[dev->cpu.HL.val] == 0;
    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.H = 0;
    dev->cpu.AF.flag.C = carry;
}

#define RL_R8(r8, r16) CPU_INSTR(rl_##r8) \
    { \
        DECOMP("RL " #r8) \
        uint8_t carry = (dev->cpu.r16.byte.r8 & 0x80) ? 1 : 0; \
        dev->cpu.r16.byte.r8 = (dev->cpu.r16.byte.r8 << 1) | dev->cpu.AF.flag.C; \
        dev->cpu.AF.flag.Z = dev->cpu.r16.byte.r8 == 0; \
        dev->cpu.AF.flag.N = 0; \
        dev->cpu.AF.flag.H = 0; \
        dev->cpu.AF.flag.C = carry; \
    }

RL_R8(B, BC)
RL_R8(C, BC)
RL_R8(D, DE)
RL_R8(E, DE)
RL_R8(H, HL)
RL_R8(L, HL)
RL_R8(A, AF)
CPU_INSTR(rl_HLmem)
{
    DECOMP("RL [HL]")

    uint8_t carry = (dev->mem[dev->cpu.HL.val] & 0x80) ? 1 : 0;
    dev->mem[dev->cpu.HL.val] = (dev->mem[dev->cpu.HL.val] << 1) | dev->cpu.AF.flag.C;

    dev->cpu.AF.flag.Z = dev->mem[dev->cpu.HL.val] == 0;
    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.H = 0;
    dev->cpu.AF.flag.C = carry;
}

#define RR_R8(r8, r16) CPU_INSTR(rr_##r8) \
    { \
        DECOMP("RR " #r8) \
        uint8_t carry = (dev->cpu.r16.byte.r8 & 0x01) ? 1 : 0; \
        dev->cpu.r16.byte.r8 = (dev->cpu.r16.byte.r8 >> 1) | (dev->cpu.AF.flag.C ? 0x80 : 0); \
        dev->cpu.AF.flag.Z = dev->cpu.r16.byte.r8 == 0; \
        dev->cpu.AF.flag.N = 0; \
        dev->cpu.AF.flag.H = 0; \
        dev->cpu.AF.flag.C = carry; \
    }

RR_R8(B, BC)
RR_R8(C, BC)
RR_R8(D, DE)
RR_R8(E, DE)
RR_R8(H, HL)
RR_R8(L, HL)
RR_R8(A, AF)
CPU_INSTR(rr_HLmem)
{
    DECOMP("RR [HL]")

    uint8_t carry = (dev->mem[dev->cpu.HL.val] & 0x01) ? 1 : 0;
    dev->mem[dev->cpu.HL.val] = (dev->mem[dev->cpu.HL.val] >> 1) | (dev->cpu.AF.flag.C ? 0x80 : 0);

    dev->cpu.AF.flag.Z = dev->mem[dev->cpu.HL.val] == 0;
    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.H = 0;
    dev->cpu.AF.flag.C = carry;
}