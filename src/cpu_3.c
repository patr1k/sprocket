/**
 * CPU Block 3 Instructions
 */

#include "cpu.h"
#include "cpu_instr_set.h"

static void _8bit_add(struct gbc* dev, uint8_t imm8, bool withCarry)
{
    uint16_t result16 = dev->cpu.AF.byte.A + imm8 + (withCarry ? dev->cpu.AF.flag.C : 0);
    uint8_t result8 = result16 & 0xFF;
    uint8_t half = ((dev->cpu.AF.byte.A ^ imm8 ^ result8) & 0x10) > 0;
    uint8_t carry = (result16 & 0x100) > 0;

    dev->cpu.AF.byte.A = result8;

    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.Z = result8 == 0 ? 1 : 0;
    dev->cpu.AF.flag.H = half ? 1 : 0;
    dev->cpu.AF.flag.C = carry ? 1 : 0;
}

static void _8bit_subtract(struct gbc* dev, uint8_t imm8, bool withCarry)
{
    uint16_t result16 = dev->cpu.AF.byte.A - imm8 - (withCarry ? dev->cpu.AF.flag.C : 0);
    uint8_t result8 = result16 & 0xFF;
    uint8_t half = ((dev->cpu.AF.byte.A ^ imm8 ^ result8) & 0x10) > 0;
    uint8_t carry = (result16 & 0x100) > 0;

    dev->cpu.AF.byte.A = result8;
    
    dev->cpu.AF.flag.N = 1;
    dev->cpu.AF.flag.Z = result8 == 0 ? 1 : 0;
    dev->cpu.AF.flag.H = half ? 1 : 0;
    dev->cpu.AF.flag.C = carry ? 1 : 0;
}

void cpu_add_a_imm8(struct gbc* dev, uint8_t imm8)
{
    DECOMP("ADD A, 0x%x", imm8)

    _8bit_add(dev, imm8, false);
}

void cpu_adc_a_imm8(struct gbc* dev, uint8_t imm8)
{
    DECOMP("ADC A, 0x%x", imm8)

    _8bit_add(dev, imm8, true);
}

void cpu_sub_a_imm8(struct gbc* dev, uint8_t imm8)
{
    DECOMP("SUB A, 0x%x", imm8)

    _8bit_subtract(dev, imm8, false);
}

void cpu_sbc_a_imm8(struct gbc* dev, uint8_t imm8)
{
    DECOMP("SBC A, 0x%x", imm8)

    _8bit_subtract(dev, imm8, true);
}

void cpu_and_a_imm8(struct gbc* dev, uint8_t imm8)
{
    DECOMP("AND A, 0x%x", imm8)
    dev->cpu.AF.byte.A &= imm8;

    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.C = 0;
    dev->cpu.AF.flag.H = 1;
    dev->cpu.AF.flag.Z = dev->cpu.AF.byte.A == 0 ? 1 : 0;
}

void cpu_xor_a_imm8(struct gbc* dev, uint8_t imm8)
{
    DECOMP("XOR A, 0x%x", imm8)
    dev->cpu.AF.byte.A ^= imm8;

    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.C = 0;
    dev->cpu.AF.flag.H = 0;
    dev->cpu.AF.flag.Z = dev->cpu.AF.byte.A == 0 ? 1 : 0;
}

void cpu_or_a_imm8(struct gbc* dev, uint8_t imm8)
{
    DECOMP("OR A, 0x%x", imm8)
    dev->cpu.AF.byte.A |= imm8;

    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.C = 0;
    dev->cpu.AF.flag.H = 0;
    dev->cpu.AF.flag.Z = dev->cpu.AF.byte.A == 0 ? 1 : 0;
}

void cpu_cp_a_imm8(struct gbc* dev, uint8_t imm8)
{
    DECOMP("CP A, 0x%x", imm8)

    uint8_t reg = imm8;
    uint16_t result16 = dev->cpu.AF.byte.A - reg;
    uint8_t result8 = result16 & 0xFF;
    uint8_t half = ((dev->cpu.AF.byte.A ^ reg ^ result8) & 0x10) > 0;
    uint8_t carry = (result16 & 0x100) > 0;

    dev->cpu.AF.flag.N = 1;
    dev->cpu.AF.flag.Z = result8 == 0 ? 1 : 0;
    dev->cpu.AF.flag.H = half ? 1 : 0;
    dev->cpu.AF.flag.C = carry ? 1 : 0;
}

void cpu_ret_cond(struct gbc* dev, enum cpu_flag_cond cond)
{
    DECOMP("RET %s", COND_NAME(cond))

    if (cond == COND_Z && dev->cpu.AF.flag.Z == 0) return;
    if (cond == COND_NZ && dev->cpu.AF.flag.Z != 0) return;
    if (cond == COND_C && dev->cpu.AF.flag.C == 0) return;
    if (cond == COND_NC && dev->cpu.AF.flag.C != 0) return;

    dev->cpu.PC.byte.L = dev->mem[dev->cpu.SP.val];
    dev->cpu.PC.byte.H = dev->mem[dev->cpu.SP.val + 1];
    dev->cpu.SP.val = dev->cpu.SP.val + 2;
}