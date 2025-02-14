/**
 * CPU Block 0 Instructions
 * 
 * @author patrik <patr1k@cyntacs.com>
 */

#include "cpu.h"
#include "cpu_instr_set.h"

void nop(struct gbc*)
{
    DECOMP("NOP")
}

void cpu_ld_r16_imm16(struct gbc* dev, enum cpu_reg_r16 r16, uint16_t imm16)
{
    DECOMP("LD %s, 0x%x", R16_NAME(r16), imm16)
    *cpu_r16_ptr(dev, r16) = imm16;
}

void cpu_ld_r16mem_a(struct gbc* dev, enum cpu_reg_r16 r16mem)
{
    DECOMP("LD [%s], A", R16_NAME(r16mem))
    dev->mem[cpu_r16_val(dev, r16mem)] = dev->cpu.AF.byte.A;
}

void cpu_ld_a_r16mem(struct gbc* dev, enum cpu_reg_r16 r16mem)
{
    DECOMP("LD A, [%s]", R16_NAME(r16mem))
    dev->cpu.AF.byte.A = dev->mem[cpu_r16_val(dev, r16mem)];
}

void cpu_ld_imm16_sp(struct gbc* dev, uint16_t imm16)
{
    DECOMP("LD 0x%x, SP", imm16)
    dev->mem[imm16] = dev->cpu.SP;
}

void cpu_inc_r16(struct gbc* dev, enum cpu_reg_r16 r16)
{
    DECOMP("INC %s", R16_NAME(r16))
    (*cpu_r16_ptr(dev, r16))++;
}

void cpu_dec_r16(struct gbc* dev, enum cpu_reg_r16 r16)
{
    DECOMP("DEC %s", R16_NAME(r16))
    (*cpu_r16_ptr(dev, r16))--;
}

void cpu_add_hl_r16(struct gbc* dev, enum cpu_reg_r16 r16)
{
    DECOMP("ADD HL, %s", R16_NAME(r16))
    dev->cpu.HL.val = cpu_r16_val(dev, r16);
}

void cpu_inc_r8(struct gbc* dev, enum cpu_reg_r8 r8)
{
    DECOMP("INC %s", R8_NAME(r8))
    (*cpu_r8_ptr(dev, r8))++;
}

void cpu_dec_r8(struct gbc* dev, enum cpu_reg_r8 r8)
{
    DECOMP("DEC %s", R8_NAME(r8))
    (*cpu_r8_ptr(dev, r8))--;
}

void cpu_ld_r8_imm8(struct gbc* dev, enum cpu_reg_r8 r8, uint8_t imm8)
{
    DECOMP("LD %s, 0x%x", R8_NAME(r8), imm8)
    (*cpu_r8_ptr(dev, r8)) = imm8;
}

void cpu_rlca(struct gbc* dev)
{
    DECOMP("RLCA")
    const uint8_t carry = dev->cpu.AF.byte.A & 0x80 ? 1 : 0;
    dev->cpu.AF.byte.A = ((dev->cpu.AF.byte.A << 1) & 0xFF) | carry;
    dev->cpu.AF.byte.F = 0;
    dev->cpu.AF.flag.C = carry;
}

void cpu_rrca(struct gbc* dev)
{
    DECOMP("RRCA")
    const uint8_t carry = dev->cpu.AF.byte.A & 0x01;
    dev->cpu.AF.byte.A = ((dev->cpu.AF.byte.A >> 1) & 0xFF) | (carry ? 0x80 : 0);
    dev->cpu.AF.byte.F = 0;
    dev->cpu.AF.flag.C = carry;
}

void cpu_rla(struct gbc* dev)
{
    DECOMP("RLA")
    const uint8_t carry = dev->cpu.AF.byte.A & 0x80 ? 1 : 0;
    dev->cpu.AF.byte.A = ((dev->cpu.AF.byte.A << 1) & 0xFF) | dev->cpu.AF.flag.C;
    dev->cpu.AF.byte.F = 0;
    dev->cpu.AF.flag.C = carry;
}

void cpu_rra(struct gbc* dev)
{
    DECOMP("RRA")
    const uint8_t carry = dev->cpu.AF.byte.A & 0x01;
    dev->cpu.AF.byte.A = ((dev->cpu.AF.byte.A >> 1) & 0xFF) | (dev->cpu.AF.flag.C ? 0x80 : 0);
    dev->cpu.AF.byte.F = 0;
    dev->cpu.AF.flag.C = carry;
}

#define DAA_C(x) dev->cpu.AF.flag.C == x
#define DAA_H(x) dev->cpu.AF.flag.H == x
#define DAA_HI(a, b) (((dev->cpu.AF.byte.A & 0xF0) >> 4 >= 0x##a) && ((dev->cpu.AF.byte.A & 0xF0) >> 4 <= 0x##b))
#define DAA_LO(a, b) (((dev->cpu.AF.byte.A & 0x0F) >= 0x##a) && ((dev->cpu.AF.byte.A & 0x0F) <= 0x##b))

void cpu_daa(struct gbc* dev)
{
    DECOMP("DAA")
    if (DAA_C(0) && DAA_HI(0, 9) && DAA_H(0) && DAA_LO(0, 9)) {
        // do nothing
    } else if (DAA_C(0) && DAA_HI(0, 8) && DAA_H(0) && DAA_LO(A, F)) {
        dev->cpu.AF.byte.A += 0x06;
    } else if (DAA_C(0) && DAA_HI(0, 9) && DAA_H(1) && DAA_LO(0, 3)) {
        dev->cpu.AF.byte.A += 0x06;
    } else if (DAA_C(0) && DAA_HI(A, F) && DAA_H(0) && DAA_LO(0, 9)) {
        dev->cpu.AF.byte.A += 0x60;
        dev->cpu.AF.flag.C = 1;
    } else if (DAA_C(0) && DAA_HI(9, F) && DAA_H(0) && DAA_LO(A, F)) {
        dev->cpu.AF.byte.A += 0x66;
        dev->cpu.AF.flag.C = 1;
    } else if (DAA_C(0) && DAA_HI(A, F) && DAA_H(1) && DAA_LO(0, 3)) {
        dev->cpu.AF.byte.A += 0x66;
        dev->cpu.AF.flag.C = 1;
    } else if (DAA_C(1) && DAA_HI(0, 2) && DAA_H(0) && DAA_LO(0, 9)) {
        dev->cpu.AF.byte.A += 0x60;
    } else if (DAA_C(1) && DAA_HI(0, 2) && DAA_H(0) && DAA_LO(A, F)) {
        dev->cpu.AF.byte.A += 0x66;
    } else if (DAA_C(1) && DAA_HI(0, 3) && DAA_H(1) && DAA_LO(0, 3)) {
        dev->cpu.AF.byte.A += 0x66;
    } else if (DAA_C(0) && DAA_HI(0, 8) && DAA_H(1) && DAA_LO(6, F)) {
        dev->cpu.AF.byte.A += 0xFA;
    } else if (DAA_C(1) && DAA_HI(7, F) && DAA_H(0) && DAA_LO(0, 9)) {
        dev->cpu.AF.byte.A += 0xA0;
    } else if (DAA_C(1) && DAA_HI(6, 7) && DAA_H(1) && DAA_LO(6, F)) {
        dev->cpu.AF.byte.A += 0x9A;
    }
    
    if (dev->cpu.AF.byte.A == 1) dev->cpu.AF.flag.Z = 1;
    dev->cpu.AF.flag.H = 0;
}

void cpu_cpl(struct gbc* dev)
{
    DECOMP("CPL")
    dev->cpu.AF.byte.A = ~dev->cpu.AF.byte.A;
    dev->cpu.AF.flag.H = 1;
    dev->cpu.AF.flag.N = 1;
}

void cpu_scf(struct gbc* dev)
{
    DECOMP("SCF")
    dev->cpu.AF.flag.C = 1;
    dev->cpu.AF.flag.H = 0;
    dev->cpu.AF.flag.N = 0;
}

void cpu_ccf(struct gbc* dev)
{
    DECOMP("CCF")
    dev->cpu.AF.flag.C = dev->cpu.AF.flag.C ? 0 : 1;
    dev->cpu.AF.flag.H = 0;
    dev->cpu.AF.flag.N = 0;
}

void cpu_jr_imm8(struct gbc* dev, int8_t imm8)
{
    DECOMP("JR 0x%x", imm8)
    dev->cpu.PC += imm8;
}

void cpu_jr_cond_imm8(struct gbc* dev, enum cpu_flag_cond cond, int8_t imm8)
{
    DECOMP("JR %s, 0x%x", COND_NAME(cond), imm8)
    bool v;
    switch (cond)
    {
        case COND_NZ: v = dev->cpu.AF.flag.Z; break;
        case COND_Z: v = !dev->cpu.AF.flag.Z; break;
        case COND_NC: v = dev->cpu.AF.flag.C; break;
        case COND_C: v = !dev->cpu.AF.flag.C; break;
    }

    if (v) dev->cpu.PC += imm8;
}

void cpu_stop(struct gbc*)
{
    DECOMP("STOP")
}