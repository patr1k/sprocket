/**
 * CPU Block 1 Instructions
 */

#include "cpu_isa.h"

CPU_INSTR(halt)
{
    DECOMP("HALT")
}

#define LD_R8_R8(r8src, r8dst, r16src, r16dst) CPU_INSTR(ld_##r8dst##_##r8src) \
    { \
        DECOMP("LD " #r8dst ", " #r8src) \
        dev->cpu.r16dst.byte.r8dst = dev->cpu.r16src.byte.r8src; \
    }

#define LD_R8_HL(r8dst, r16dst) CPU_INSTR(ld_##r8dst##_HLmem) \
    { \
        DECOMP("LD " #r8dst ", [HL]") \
        dev->cpu.r16dst.byte.r8dst = dev->mem[dev->cpu.HL.val]; \
    }

#define LD_HL_R8(r8src, r16src) CPU_INSTR(ld_HLmem_##r8src) \
    { \
        DECOMP("LD [HL], " #r8src) \
        dev->mem[dev->cpu.HL.val] = dev->cpu.r16src.byte.r8src; \
    }

LD_R8_R8(B, B, BC, BC)
LD_R8_R8(B, C, BC, BC)
LD_R8_R8(B, D, BC, DE)
LD_R8_R8(B, E, BC, DE)
LD_R8_R8(B, H, BC, HL)
LD_R8_R8(B, L, BC, HL)
LD_R8_HL(B, BC)
LD_R8_R8(B, A, BC, AF)

LD_R8_R8(C, B, BC, BC)
LD_R8_R8(C, C, BC, BC)
LD_R8_R8(C, D, BC, DE)
LD_R8_R8(C, E, BC, DE)
LD_R8_R8(C, H, BC, HL)
LD_R8_R8(C, L, BC, HL)
LD_R8_HL(C, BC)
LD_R8_R8(C, A, BC, AF)

LD_R8_R8(D, B, DE, BC)
LD_R8_R8(D, C, DE, BC)
LD_R8_R8(D, D, DE, DE)
LD_R8_R8(D, E, DE, DE)
LD_R8_R8(D, H, DE, HL)
LD_R8_R8(D, L, DE, HL)
LD_R8_HL(D, DE)
LD_R8_R8(D, A, DE, AF)

LD_R8_R8(E, B, DE, BC)
LD_R8_R8(E, C, DE, BC)
LD_R8_R8(E, D, DE, DE)
LD_R8_R8(E, E, DE, DE)
LD_R8_R8(E, H, DE, HL)
LD_R8_R8(E, L, DE, HL)
LD_R8_HL(E, DE)
LD_R8_R8(E, A, DE, AF)

LD_R8_R8(H, B, HL, BC)
LD_R8_R8(H, C, HL, BC)
LD_R8_R8(H, D, HL, DE)
LD_R8_R8(H, E, HL, DE)
LD_R8_R8(H, H, HL, HL)
LD_R8_R8(H, L, HL, HL)
LD_R8_HL(H, HL)
LD_R8_R8(H, A, HL, AF)

LD_R8_R8(L, B, HL, BC)
LD_R8_R8(L, C, HL, BC)
LD_R8_R8(L, D, HL, DE)
LD_R8_R8(L, E, HL, DE)
LD_R8_R8(L, H, HL, HL)
LD_R8_R8(L, L, HL, HL)
LD_R8_HL(L, HL)
LD_R8_R8(L, A, HL, AF)

LD_HL_R8(B, BC)
LD_HL_R8(C, BC)
LD_HL_R8(D, DE)
LD_HL_R8(E, DE)
LD_HL_R8(H, HL)
LD_HL_R8(L, HL)
LD_HL_R8(A, AF)

LD_R8_R8(A, B, AF, BC)
LD_R8_R8(A, C, AF, BC)
LD_R8_R8(A, D, AF, DE)
LD_R8_R8(A, E, AF, DE)
LD_R8_R8(A, H, AF, HL)
LD_R8_R8(A, L, AF, HL)
LD_R8_HL(A, AF)
LD_R8_R8(A, A, AF, AF)