/**
 * CPU Block 2 Instructions
 */

#include "cpu_isa.h"

#define ADD_A_R8(r8src, r16src) CPU_INSTR(add_A_##r8src) \
    { \
        DECOMP("ADD A, " #r8src) \
        uint8_t reg = dev->cpu.r16src.byte.r8src ; \
        uint16_t result16 = dev->cpu.AF.byte.A + reg; \
        uint8_t result8 = result16 & 0xFF; \
        uint8_t half = ((dev->cpu.AF.byte.A ^ reg ^ result8) & 0x10) > 0; \
        uint8_t carry = (result16 & 0x100) > 0; \
        dev->cpu.AF.byte.A = result8; \
        dev->cpu.AF.flag.N = 0; \
        dev->cpu.AF.flag.Z = result8 == 0 ? 1 : 0; \
        dev->cpu.AF.flag.H = half ? 1 : 0; \
        dev->cpu.AF.flag.C = carry ? 1 : 0; \
    }

#define ADC_A_R8(r8src, r16src) CPU_INSTR(adc_A_##r8src) \
    { \
        DECOMP("ADD A, " #r8src) \
        uint8_t reg = dev->cpu.r16src.byte.r8src ; \
        uint16_t result16 = dev->cpu.AF.byte.A + reg + dev->cpu.AF.flag.C; \
        uint8_t result8 = result16 & 0xFF; \
        uint8_t half = ((dev->cpu.AF.byte.A ^ reg ^ result8) & 0x10) > 0; \
        uint8_t carry = (result16 & 0x100) > 0; \
        dev->cpu.AF.byte.A = result8; \
        dev->cpu.AF.flag.N = 0; \
        dev->cpu.AF.flag.Z = result8 == 0 ? 1 : 0; \
        dev->cpu.AF.flag.H = half ? 1 : 0; \
        dev->cpu.AF.flag.C = carry ? 1 : 0; \
    }

#define SUB_A_R8(r8src, r16src) CPU_INSTR(sub_A_##r8src) \
    { \
        DECOMP("SUB A, " #r8src) \
        uint8_t reg = dev->cpu.r16src.byte.r8src; \
        uint16_t result16 = dev->cpu.AF.byte.A - reg; \
        uint8_t result8 = result16 & 0xFF; \
        uint8_t half = ((dev->cpu.AF.byte.A ^ reg ^ result8) & 0x10) > 0; \
        uint8_t carry = (result16 & 0x100) > 0; \
        dev->cpu.AF.byte.A = result8; \
        dev->cpu.AF.flag.N = 1; \
        dev->cpu.AF.flag.Z = result8 == 0 ? 1 : 0; \
        dev->cpu.AF.flag.H = half ? 1 : 0; \
        dev->cpu.AF.flag.C = carry ? 1 : 0; \
    }

#define SBC_A_R8(r8src, r16src) CPU_INSTR(sbc_A_##r8src) \
    { \
        DECOMP("SBC A, " #r8src) \
        uint8_t reg = dev->cpu.r16src.byte.r8src; \
        uint16_t result16 = dev->cpu.AF.byte.A - reg - dev->cpu.AF.flag.C; \
        uint8_t result8 = result16 & 0xFF; \
        uint8_t half = ((dev->cpu.AF.byte.A ^ reg ^ result8) & 0x10) > 0; \
        uint8_t carry = (result16 & 0x100) > 0; \
        dev->cpu.AF.byte.A = result8; \
        dev->cpu.AF.flag.N = 1; \
        dev->cpu.AF.flag.Z = result8 == 0 ? 1 : 0; \
        dev->cpu.AF.flag.H = half ? 1 : 0; \
        dev->cpu.AF.flag.C = carry ? 1 : 0; \
    }

#define AND_A_R8(r8src, r16src) CPU_INSTR(and_A_##r8src) \
    { \
        DECOMP("AND A, " #r8src) \
        dev->cpu.AF.byte.A &= dev->cpu.r16src.byte.r8src; \
        dev->cpu.AF.flag.N = 0; \
        dev->cpu.AF.flag.C = 0; \
        dev->cpu.AF.flag.H = 1; \
        dev->cpu.AF.flag.Z = dev->cpu.AF.byte.A == 0 ? 1 : 0; \
    }

#define XOR_A_R8(r8src, r16src) CPU_INSTR(xor_A_##r8src) \
    { \
        DECOMP("XOR A, " #r8src) \
        dev->cpu.AF.byte.A ^= dev->cpu.r16src.byte.r8src; \
        dev->cpu.AF.flag.N = 0; \
        dev->cpu.AF.flag.C = 0; \
        dev->cpu.AF.flag.H = 0; \
        dev->cpu.AF.flag.Z = dev->cpu.AF.byte.A == 0 ? 1 : 0; \
    }

#define OR_A_R8(r8src, r16src) CPU_INSTR(or_A_##r8src) \
    { \
        DECOMP("OR A, " #r8src) \
        dev->cpu.AF.byte.A |= dev->cpu.r16src.byte.r8src; \
        dev->cpu.AF.flag.N = 0; \
        dev->cpu.AF.flag.C = 0; \
        dev->cpu.AF.flag.H = 0; \
        dev->cpu.AF.flag.Z = dev->cpu.AF.byte.A == 0 ? 1 : 0; \
    }

#define CP_A_R8(r8src, r16src) CPU_INSTR(cp_A_##r8src) \
    { \
        DECOMP("CP A, " #r8src) \
        uint8_t reg = dev->cpu.r16src.byte.r8src; \
        uint16_t result16 = dev->cpu.AF.byte.A - reg; \
        uint8_t result8 = result16; \
        uint8_t half = ((dev->cpu.AF.byte.A ^ reg ^ result8) & 0x10) > 0; \
        uint8_t carry = (result16 & 0x100) > 0; \
        dev->cpu.AF.flag.N = 1; \
        dev->cpu.AF.flag.Z = result8 == 0 ? 1 : 0; \
        dev->cpu.AF.flag.H = half ? 1 : 0; \
        dev->cpu.AF.flag.C = carry ? 1 : 0; \
    }

ADD_A_R8(B, BC)
ADD_A_R8(C, BC)
ADD_A_R8(D, DE)
ADD_A_R8(E, DE)
ADD_A_R8(H, HL)
ADD_A_R8(L, HL)
ADD_A_R8(A, AF)
CPU_INSTR(add_A_HLmem)
{ 
    DECOMP("ADD A, [HL]") 
    uint8_t reg = dev->mem[dev->cpu.HL.val]; 
    uint16_t result16 = dev->cpu.AF.byte.A + reg; 
    uint8_t result8 = result16 & 0xFF; 
    uint8_t half = ((dev->cpu.AF.byte.A ^ reg ^ result8) & 0x10) > 0; 
    uint8_t carry = (result16 & 0x100) > 0; 
    dev->cpu.AF.byte.A = result8; 
    dev->cpu.AF.flag.N = 0; 
    dev->cpu.AF.flag.Z = result8 == 0 ? 1 : 0; 
    dev->cpu.AF.flag.H = half ? 1 : 0; 
    dev->cpu.AF.flag.C = carry ? 1 : 0; 
}

ADC_A_R8(B, BC)
ADC_A_R8(C, BC)
ADC_A_R8(D, DE)
ADC_A_R8(E, DE)
ADC_A_R8(H, HL)
ADC_A_R8(L, HL)
ADC_A_R8(A, AF)
CPU_INSTR(adc_A_HLmem)
{ 
    DECOMP("ADD A, [HL]") 
    uint8_t reg = dev->mem[dev->cpu.HL.val]; 
    uint16_t result16 = dev->cpu.AF.byte.A + reg + dev->cpu.AF.flag.C; 
    uint8_t result8 = result16 & 0xFF; 
    uint8_t half = ((dev->cpu.AF.byte.A ^ reg ^ result8) & 0x10) > 0; 
    uint8_t carry = (result16 & 0x100) > 0; 
    dev->cpu.AF.byte.A = result8; 
    dev->cpu.AF.flag.N = 0; 
    dev->cpu.AF.flag.Z = result8 == 0 ? 1 : 0; 
    dev->cpu.AF.flag.H = half ? 1 : 0; 
    dev->cpu.AF.flag.C = carry ? 1 : 0; 
}

SUB_A_R8(B, BC)
SUB_A_R8(C, BC)
SUB_A_R8(D, DE)
SUB_A_R8(E, DE)
SUB_A_R8(H, HL)
SUB_A_R8(L, HL)
SUB_A_R8(A, AF)
CPU_INSTR(sub_A_HLmem)
{ 
    DECOMP("SUB A, [HL]") 
    uint8_t reg = dev->mem[dev->cpu.HL.val]; 
    uint16_t result16 = dev->cpu.AF.byte.A - reg; 
    uint8_t result8 = result16 & 0xFF; 
    uint8_t half = ((dev->cpu.AF.byte.A ^ reg ^ result8) & 0x10) > 0; 
    uint8_t carry = (result16 & 0x100) > 0; 
    dev->cpu.AF.byte.A = result8; 
    dev->cpu.AF.flag.N = 0; 
    dev->cpu.AF.flag.Z = result8 == 0 ? 1 : 0; 
    dev->cpu.AF.flag.H = half ? 1 : 0; 
    dev->cpu.AF.flag.C = carry ? 1 : 0; 
}

SBC_A_R8(B, BC)
SBC_A_R8(C, BC)
SBC_A_R8(D, DE)
SBC_A_R8(E, DE)
SBC_A_R8(H, HL)
SBC_A_R8(L, HL)
SBC_A_R8(A, AF)
CPU_INSTR(sbc_A_HLmem)
{ 
    DECOMP("SBC A, [HL]") 
    uint8_t reg = dev->mem[dev->cpu.HL.val]; 
    uint16_t result16 = dev->cpu.AF.byte.A - reg - dev->cpu.AF.flag.C; 
    uint8_t result8 = result16 & 0xFF; 
    uint8_t half = ((dev->cpu.AF.byte.A ^ reg ^ result8) & 0x10) > 0; 
    uint8_t carry = (result16 & 0x100) > 0; 
    dev->cpu.AF.byte.A = result8; 
    dev->cpu.AF.flag.N = 1; 
    dev->cpu.AF.flag.Z = result8 == 0 ? 1 : 0; 
    dev->cpu.AF.flag.H = half ? 1 : 0; 
    dev->cpu.AF.flag.C = carry ? 1 : 0; 
}


AND_A_R8(B, BC)
AND_A_R8(C, BC)
AND_A_R8(D, DE)
AND_A_R8(E, DE)
AND_A_R8(H, HL)
AND_A_R8(L, HL)
AND_A_R8(A, AF)
CPU_INSTR(and_A_HLmem)
{
    DECOMP("AND A, [HL]")
    dev->cpu.AF.byte.A &= dev->mem[dev->cpu.HL.val];

    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.C = 0;
    dev->cpu.AF.flag.H = 1;
    dev->cpu.AF.flag.Z = dev->cpu.AF.byte.A == 0 ? 1 : 0;
}


XOR_A_R8(B, BC)
XOR_A_R8(C, BC)
XOR_A_R8(D, DE)
XOR_A_R8(E, DE)
XOR_A_R8(H, HL)
XOR_A_R8(L, HL)
XOR_A_R8(A, AF)
CPU_INSTR(xor_A_HLmem)
{
    DECOMP("XOR A, [HL]")
    dev->cpu.AF.byte.A ^= dev->mem[dev->cpu.HL.val];

    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.C = 0;
    dev->cpu.AF.flag.H = 0;
    dev->cpu.AF.flag.Z = dev->cpu.AF.byte.A == 0 ? 1 : 0;
}


OR_A_R8(B, BC)
OR_A_R8(C, BC)
OR_A_R8(D, DE)
OR_A_R8(E, DE)
OR_A_R8(H, HL)
OR_A_R8(L, HL)
OR_A_R8(A, AF)
CPU_INSTR(or_A_HLmem)
{
    DECOMP("OR A, [HL]")
    dev->cpu.AF.byte.A |= dev->mem[dev->cpu.HL.val];

    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.C = 0;
    dev->cpu.AF.flag.H = 0;
    dev->cpu.AF.flag.Z = dev->cpu.AF.byte.A == 0 ? 1 : 0;
}


CP_A_R8(B, BC)
CP_A_R8(C, BC)
CP_A_R8(D, DE)
CP_A_R8(E, DE)
CP_A_R8(H, HL)
CP_A_R8(L, HL)
CP_A_R8(A, AF)
CPU_INSTR(cp_A_HLmem)
{
    DECOMP("CP A, [HL]")

    uint8_t reg = dev->mem[dev->cpu.HL.val];
    uint16_t result16 = dev->cpu.AF.byte.A - reg;
    uint8_t result8 = result16;
    uint8_t half = ((dev->cpu.AF.byte.A ^ reg ^ result8) & 0x10) > 0;
    uint8_t carry = (result16 & 0x100) > 0;

    dev->cpu.AF.flag.N = 1;
    dev->cpu.AF.flag.Z = result8 == 0 ? 1 : 0;
    dev->cpu.AF.flag.H = half ? 1 : 0;
    dev->cpu.AF.flag.C = carry ? 1 : 0;
}