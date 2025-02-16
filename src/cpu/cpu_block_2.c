/**
 * CPU Block 2 Instructions
 */

#include "cpu_isa.h"

#define ADD_A_R8(r8src, r16src) CPU_INSTR(add_A_##r8src) \
    { \
        DECOMP("ADD A, " #r8src) \
        uint8_t reg = dev->cpu.##r16src.byte.##r8src; \
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
        uint8_t reg = dev->cpu.##r16src.byte.##r8src; \
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

