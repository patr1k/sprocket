/**
 * CPU Block 0 Instructions
 * 
 * @author patrik <patr1k@cyntacs.com>
 */

#include "cpu.h"
#include "cpu_instr_set.h"

void nop(struct gbc*)
{

}

void cpu_ld_r16_imm16(struct gbc* dev, enum cpu_reg_r16 r16, uint16_t imm16)
{
    *cpu_r16_ptr(dev, r16) = imm16;
}

void cpu_ld_r16mem_a(struct gbc* dev, enum cpu_reg_r16 r16mem)
{
    dev->mem[cpu_r16_val(dev, r16mem)] = dev->cpu.AF.byte.A;
}

void cpu_ld_a_r16mem(struct gbc* dev, enum cpu_reg_r16 r16mem)
{
    dev->cpu.AF.byte.A = dev->mem[cpu_r16_val(dev, r16mem)];
}

void cpu_ld_imm16_sp(struct gbc* dev, uint16_t imm16)
{
    dev->mem[imm16] = dev->cpu.SP;
}

void cpu_inc_r16(struct gbc* dev, enum cpu_reg_r16 r16)
{
    (*cpu_r16_ptr(dev, r16))++;
}

void cpu_dec_r16(struct gbc* dev, enum cpu_reg_r16 r16)
{
    (*cpu_r16_ptr(dev, r16))--;
}

void cpu_add_hl_r16(struct gbc* dev, enum cpu_reg_r16 r16)
{
    dev->cpu.HL.val = cpu_r16_val(dev, r16);
}

void cpu_inc_r8(struct gbc* dev, enum cpu_reg_r8 r8)
{
    (*cpu_r8_ptr(dev, r8))++;
}

void cpu_dec_r8(struct gbc* dev, enum cpu_reg_r8 r8)
{
    (*cpu_r8_ptr(dev, r8))--;
}

void cpu_ld_r8_imm8(struct gbc* dev, enum cpu_reg_r8 r8, uint8_t imm8)
{
    (*cpu_r8_ptr(dev, r8)) = imm8;
}

void cpu_rlca(struct gbc* dev)
{
    const uint8_t carry = dev->cpu.AF.byte.A & 0x80 ? 1 : 0;
    dev->cpu.AF.byte.A = ((dev->cpu.AF.byte.A << 1) & 0xFF) | carry;
    dev->cpu.AF.byte.F = 0;
    dev->cpu.AF.flag.C = carry;
}

void cpu_rrca(struct gbc* dev)
{
    const uint8_t carry = dev->cpu.AF.byte.A & 0x01;
    dev->cpu.AF.byte.A = ((dev->cpu.AF.byte.A >> 1) & 0xFF) | (carry ? 0x80 : 0);
    dev->cpu.AF.byte.F = 0;
    dev->cpu.AF.flag.C = carry;
}

void cpu_rla(struct gbc* dev)
{
    const uint8_t carry = dev->cpu.AF.byte.A & 0x80 ? 1 : 0;
    dev->cpu.AF.byte.A = ((dev->cpu.AF.byte.A << 1) & 0xFF) | dev->cpu.AF.flag.C;
    dev->cpu.AF.byte.F = 0;
    dev->cpu.AF.flag.C = carry;
}

void cpu_rra(struct gbc* dev)
{
    const uint8_t carry = dev->cpu.AF.byte.A & 0x01;
    dev->cpu.AF.byte.A = ((dev->cpu.AF.byte.A >> 1) & 0xFF) | (dev->cpu.AF.flag.C ? 0x80 : 0);
    dev->cpu.AF.byte.F = 0;
    dev->cpu.AF.flag.C = carry;
}

void cpu_daa(struct gbc* dev)
{
    
}

void cpu_cpl(struct gbc* dev)
{

}

void cpu_scf(struct gbc* dev)
{

}

void cpu_ccf(struct gbc* dev)
{

}

void cpu_jr_imm8(struct gbc* dev, uint8_t imm8)
{

}

void cpu_jr_cond_imm8(struct gbc* dev, enum cpu_flag_cond cond, uint8_t imm8)
{

}

void cpu_stop(struct gbc*)
{

}