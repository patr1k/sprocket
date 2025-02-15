/**
 * CPU Block 2 Instructions
 */

#include "cpu.h"
#include "cpu_instr_set.h"

static void _8bit_add(struct gbc* dev, enum cpu_reg_r8 r8, bool withCarry)
{
    uint8_t reg = cpu_r8_val(dev, r8);
    uint16_t result16 = dev->cpu.AF.byte.A + reg + (withCarry ? dev->cpu.AF.flag.C : 0);
    uint8_t result8 = result16 & 0xFF;
    uint8_t half = ((dev->cpu.AF.byte.A ^ reg ^ result8) & 0x10) > 0;
    uint8_t carry = (result16 & 0x100) > 0;

    dev->cpu.AF.byte.A = result8;
    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.Z = result8 == 0 ? 1 : 0;
    dev->cpu.AF.flag.H = half ? 1 : 0;
    dev->cpu.AF.flag.C = carry ? 1 : 0;
}

static void _8bit_subtract(struct gbc* dev, enum cpu_reg_r8 r8, bool withCarry)
{
    uint8_t reg = cpu_r8_val(dev, r8);
    uint16_t result16 = dev->cpu.AF.byte.A - reg - (withCarry ? dev->cpu.AF.flag.C : 0);
    uint8_t result8 = result16 & 0xFF;
    uint8_t half = ((dev->cpu.AF.byte.A ^ reg ^ result8) & 0x10) > 0;
    uint8_t carry = (result16 & 0x100) > 0;

    dev->cpu.AF.byte.A = result8;
    dev->cpu.AF.flag.N = 1;
    dev->cpu.AF.flag.Z = result8 == 0 ? 1 : 0;
    dev->cpu.AF.flag.H = half ? 1 : 0;
    dev->cpu.AF.flag.C = carry ? 1 : 0;
}

void cpu_add_a_r8(struct gbc* dev, enum cpu_reg_r8 r8)
{
    DECOMP("ADD A, %s", R8_NAME(r8))

    _8bit_add(dev, r8, false);
}

void cpu_adc_a_r8(struct gbc* dev, enum cpu_reg_r8 r8)
{
    DECOMP("ADC A, %s", R8_NAME(r8))

    _8bit_add(dev, r8, true);
}

void cpu_sub_a_r8(struct gbc* dev, enum cpu_reg_r8 r8)
{
    DECOMP("SUB A, %s", R8_NAME(r8))

    _8bit_subtract(dev, r8, false);
}

void cpu_sbc_a_r8(struct gbc* dev, enum cpu_reg_r8 r8)
{
    DECOMP("SBC A, %s", R8_NAME(r8))

    _8bit_subtract(dev, r8, true);
}

void cpu_and_a_r8(struct gbc* dev, enum cpu_reg_r8 r8)
{
    DECOMP("AND A, %s", R8_NAME(r8))
    dev->cpu.AF.byte.A &= cpu_r8_val(dev, r8);

    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.C = 0;
    dev->cpu.AF.flag.H = 1;
    dev->cpu.AF.flag.Z = dev->cpu.AF.byte.A == 0 ? 1 : 0;
}

void cpu_xor_a_r8(struct gbc* dev, enum cpu_reg_r8 r8)
{
    DECOMP("XOR A, %s", R8_NAME(r8))
    dev->cpu.AF.byte.A ^= cpu_r8_val(dev, r8);

    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.C = 0;
    dev->cpu.AF.flag.H = 0;
    dev->cpu.AF.flag.Z = dev->cpu.AF.byte.A == 0 ? 1 : 0;
}

void cpu_or_a_r8(struct gbc* dev, enum cpu_reg_r8 r8)
{
    DECOMP("OR A, %s", R8_NAME(r8))
    dev->cpu.AF.byte.A |= cpu_r8_val(dev, r8);

    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.C = 0;
    dev->cpu.AF.flag.H = 0;
    dev->cpu.AF.flag.Z = dev->cpu.AF.byte.A == 0 ? 1 : 0;
}

void cpu_cp_a_r8(struct gbc* dev, enum cpu_reg_r8 r8)
{
    DECOMP("CP A, %s", R8_NAME(r8))

    uint8_t reg = cpu_r8_val(dev, r8);
    uint16_t result16 = dev->cpu.AF.byte.A - reg;
    uint8_t result8 = result16 & 0xFF;
    uint8_t half = ((dev->cpu.AF.byte.A ^ reg ^ result8) & 0x10) > 0;
    uint8_t carry = (result16 & 0x100) > 0;

    dev->cpu.AF.flag.N = 1;
    dev->cpu.AF.flag.Z = result8 == 0 ? 1 : 0;
    dev->cpu.AF.flag.H = half ? 1 : 0;
    dev->cpu.AF.flag.C = carry ? 1 : 0;
}