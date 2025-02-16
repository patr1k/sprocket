/**
 * CPU Block 0 Instructions
 */

#include "cpu_isa.h"

CPU_INSTR(nop)
{
    DECOMP("NOP")
}

CPU_INSTR(ld_BC_d16)
{
    uint16_t d16 = FETCH_WORD();
    DECOMP("LD BC, 0x%x", d16)

    dev->cpu.BC.val = d16;
}

CPU_INSTR(ld_DE_d16)
{
    uint16_t d16 = FETCH_WORD();
    DECOMP("LD DE, 0x%x", d16)

    dev->cpu.DE.val = d16;
}

CPU_INSTR(ld_HL_d16)
{
    uint16_t d16 = FETCH_WORD();
    DECOMP("LD HL, 0x%x", d16)

    dev->cpu.HL.val = d16;
}

CPU_INSTR(ld_SP_d16)
{
    uint16_t d16 = FETCH_WORD();
    DECOMP("LD SP, 0x%x", d16)

    dev->cpu.SP.val = d16;
}

CPU_INSTR(ld_BCmem_A)
{
    DECOMP("LD [BC], A")
    dev->mem[dev->cpu.BC.val] = dev->cpu.AF.byte.A;
}

CPU_INSTR(ld_DEmem_A)
{
    DECOMP("LD [DE], A")
    dev->mem[dev->cpu.DE.val] = dev->cpu.AF.byte.A;
}

CPU_INSTR(ld_HLi_A)
{
    DECOMP("LD [HL+], A")
    dev->mem[dev->cpu.HL.val++] = dev->cpu.AF.byte.A;
}

CPU_INSTR(ld_HLd_A)
{
    DECOMP("LD [HL-], A")
    dev->mem[dev->cpu.HL.val--] = dev->cpu.AF.byte.A;
}

CPU_INSTR(ld_A_BCmem)
{
    DECOMP("LD A, [BC]")
    dev->cpu.AF.byte.A = dev->mem[dev->cpu.BC.val];
}

CPU_INSTR(ld_A_DEmem)
{
    DECOMP("LD A, [DE]")
    dev->cpu.AF.byte.A = dev->mem[dev->cpu.DE.val];
}

CPU_INSTR(ld_A_HLi)
{
    DECOMP("LD A, [HL+]")
    dev->cpu.AF.byte.A = dev->mem[dev->cpu.HL.val++];
}

CPU_INSTR(ld_A_HLd)
{
    DECOMP("LD A, [HL-]")
    dev->cpu.AF.byte.A = dev->mem[dev->cpu.HL.val--];
}

CPU_INSTR(ld_a16_SP)
{
    uint16_t a16 = FETCH_WORD();
    DECOMP("LD 0x%x, SP", a16)

    dev->mem[a16] = dev->cpu.SP.val;
}

CPU_INSTR(inc_BC)
{
    DECOMP("INC BC")
    ++dev->cpu.BC.val;
}

CPU_INSTR(inc_DE)
{
    DECOMP("INC DE")
    ++dev->cpu.DE.val;
}

CPU_INSTR(inc_HL)
{
    DECOMP("INC HL")
    ++dev->cpu.HL.val;
}

CPU_INSTR(inc_SP)
{
    DECOMP("INC SP")
    ++dev->cpu.SP.val;
}

CPU_INSTR(dec_BC)
{
    DECOMP("DEC BC")
    --dev->cpu.BC.val;
}

CPU_INSTR(dec_DE)
{
    DECOMP("DEC DE")
    --dev->cpu.DE.val;
}

CPU_INSTR(dec_HL)
{
    DECOMP("DEC HL")
    --dev->cpu.HL.val;
}

CPU_INSTR(dec_SP)
{
    DECOMP("DEC SP")
    --dev->cpu.SP.val;
}

CPU_INSTR(add_HL_BC)
{
    DECOMP("ADD HL, BC")

    uint16_t HL = dev->cpu.HL.val;
    uint16_t reg = dev->cpu.BC.val;
    uint32_t result32 = HL + reg;

    dev->cpu.HL.val = result32;

    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.C = (result32 & 0x10000) ? 1 : 0;
    dev->cpu.AF.flag.H = ((HL ^ reg ^ dev->cpu.HL.val) & 0x100) ? 1 : 0;
}

CPU_INSTR(add_HL_DE)
{
    DECOMP("ADD HL, DE")

    uint16_t HL = dev->cpu.HL.val;
    uint16_t reg = dev->cpu.DE.val;
    uint32_t result32 = HL + reg;

    dev->cpu.HL.val = result32;

    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.C = (result32 & 0x10000) ? 1 : 0;
    dev->cpu.AF.flag.H = ((HL ^ reg ^ dev->cpu.HL.val) & 0x100) ? 1 : 0;
}

CPU_INSTR(add_HL_HL)
{
    DECOMP("ADD HL, HL")

    uint16_t HL = dev->cpu.HL.val;
    uint16_t reg = dev->cpu.HL.val;
    uint32_t result32 = HL + reg;

    dev->cpu.HL.val = result32;

    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.C = (result32 & 0x10000) ? 1 : 0;
    dev->cpu.AF.flag.H = ((HL ^ reg ^ dev->cpu.HL.val) & 0x100) ? 1 : 0;
}

CPU_INSTR(add_HL_SP)
{
    DECOMP("ADD HL, SP")

    uint16_t HL = dev->cpu.HL.val;
    uint16_t reg = dev->cpu.SP.val;
    uint32_t result32 = HL + reg;

    dev->cpu.HL.val = result32;

    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.C = (result32 & 0x10000) ? 1 : 0;
    dev->cpu.AF.flag.H = ((HL ^ reg ^ dev->cpu.HL.val) & 0x100) ? 1 : 0;
}

CPU_INSTR(inc_B)
{
    DECOMP("INC B")

    ++dev->cpu.BC.byte.B;

    dev->cpu.AF.flag.Z = (dev->cpu.BC.byte.B == 0) ? 1 : 0;
    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.H = ((dev->cpu.BC.byte.B & 0x1F) == 0x1F) ? 1 : 0;
}

CPU_INSTR(inc_C)
{
    DECOMP("INC C")

    ++dev->cpu.BC.byte.C;

    dev->cpu.AF.flag.Z = (dev->cpu.BC.byte.C == 0) ? 1 : 0;
    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.H = ((dev->cpu.BC.byte.C & 0x1F) == 0x1F) ? 1 : 0;
}

CPU_INSTR(inc_D)
{
    DECOMP("INC D")

    ++dev->cpu.DE.byte.D;

    dev->cpu.AF.flag.Z = (dev->cpu.DE.byte.D == 0) ? 1 : 0;
    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.H = ((dev->cpu.DE.byte.D & 0x1F) == 0x1F) ? 1 : 0;
}

CPU_INSTR(inc_E)
{
    DECOMP("INC E")

    ++dev->cpu.DE.byte.E;

    dev->cpu.AF.flag.Z = (dev->cpu.DE.byte.E == 0) ? 1 : 0;
    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.H = ((dev->cpu.DE.byte.E & 0x1F) == 0x1F) ? 1 : 0;
}

CPU_INSTR(inc_H)
{
    DECOMP("INC H")

    ++dev->cpu.HL.byte.H;

    dev->cpu.AF.flag.Z = (dev->cpu.HL.byte.H == 0) ? 1 : 0;
    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.H = ((dev->cpu.HL.byte.H & 0x1F) == 0x1F) ? 1 : 0;
}

CPU_INSTR(inc_L)
{
    DECOMP("INC L")

    ++dev->cpu.HL.byte.L;

    dev->cpu.AF.flag.Z = (dev->cpu.HL.byte.L == 0) ? 1 : 0;
    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.H = ((dev->cpu.HL.byte.L & 0x1F) == 0x1F) ? 1 : 0;
}

CPU_INSTR(inc_HLmem)
{
    DECOMP("INC [HL]")

    ++dev->mem[dev->cpu.HL.val];

    dev->cpu.AF.flag.Z = (dev->mem[dev->cpu.HL.val] == 0) ? 1 : 0;
    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.H = ((dev->mem[dev->cpu.HL.val] & 0x1F) == 0x1F) ? 1 : 0;
}

CPU_INSTR(inc_A)
{
    DECOMP("INC A")

    ++dev->cpu.AF.byte.A;

    dev->cpu.AF.flag.Z = (dev->cpu.AF.byte.A == 0) ? 1 : 0;
    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.H = ((dev->cpu.AF.byte.A & 0x1F) == 0x1F) ? 1 : 0;
}

CPU_INSTR(dec_B)
{
    DECOMP("DEC B")

    --dev->cpu.BC.byte.B;

    dev->cpu.AF.flag.Z = (dev->cpu.BC.byte.B == 0) ? 1 : 0;
    dev->cpu.AF.flag.N = 1;
    dev->cpu.AF.flag.H = ((dev->cpu.BC.byte.B & 0x1F) == 0x0F) ? 1 : 0;
}

CPU_INSTR(dec_C)
{
    DECOMP("DEC C")

    --dev->cpu.BC.byte.C;

    dev->cpu.AF.flag.Z = (dev->cpu.BC.byte.C == 0) ? 1 : 0;
    dev->cpu.AF.flag.N = 1;
    dev->cpu.AF.flag.H = ((dev->cpu.BC.byte.C & 0x1F) == 0x0F) ? 1 : 0;
}

CPU_INSTR(dec_D)
{
    DECOMP("DEC D")

    --dev->cpu.DE.byte.D;

    dev->cpu.AF.flag.Z = (dev->cpu.DE.byte.D == 0) ? 1 : 0;
    dev->cpu.AF.flag.N = 1;
    dev->cpu.AF.flag.H = ((dev->cpu.DE.byte.D & 0x1F) == 0x0F) ? 1 : 0;
}

CPU_INSTR(dec_E)
{
    DECOMP("DEC E")

    --dev->cpu.DE.byte.E;

    dev->cpu.AF.flag.Z = (dev->cpu.DE.byte.E == 0) ? 1 : 0;
    dev->cpu.AF.flag.N = 1;
    dev->cpu.AF.flag.H = ((dev->cpu.DE.byte.E & 0x1F) == 0x0F) ? 1 : 0;
}

CPU_INSTR(dec_H)
{
    DECOMP("DEC H")

    --dev->cpu.HL.byte.H;

    dev->cpu.AF.flag.Z = (dev->cpu.HL.byte.H == 0) ? 1 : 0;
    dev->cpu.AF.flag.N = 1;
    dev->cpu.AF.flag.H = ((dev->cpu.HL.byte.H & 0x1F) == 0x0F) ? 1 : 0;
}

CPU_INSTR(dec_L)
{
    DECOMP("DEC L")

    --dev->cpu.HL.byte.L;

    dev->cpu.AF.flag.Z = (dev->cpu.HL.byte.L == 0) ? 1 : 0;
    dev->cpu.AF.flag.N = 1;
    dev->cpu.AF.flag.H = ((dev->cpu.HL.byte.L & 0x1F) == 0x0F) ? 1 : 0;
}

CPU_INSTR(dec_HLmem)
{
    DECOMP("DEC [HL]")

    --dev->mem[dev->cpu.HL.val];

    dev->cpu.AF.flag.Z = (dev->mem[dev->cpu.HL.val] == 0) ? 1 : 0;
    dev->cpu.AF.flag.N = 1;
    dev->cpu.AF.flag.H = ((dev->mem[dev->cpu.HL.val] & 0x1F) == 0x0F) ? 1 : 0;
}

CPU_INSTR(dec_A)
{
    DECOMP("DEC A")

    --dev->cpu.AF.byte.A;

    dev->cpu.AF.flag.Z = (dev->cpu.AF.byte.A == 0) ? 1 : 0;
    dev->cpu.AF.flag.N = 1;
    dev->cpu.AF.flag.H = ((dev->cpu.AF.byte.A & 0x1F) == 0x0F) ? 1 : 0;
}

CPU_INSTR(ld_B_d8)
{
    uint8_t d8 = FETCH_BYTE();
    DECOMP("LD B, 0x%x", d8)

    dev->cpu.BC.byte.B = d8;
}

CPU_INSTR(ld_C_d8)
{
    uint8_t d8 = FETCH_BYTE();
    DECOMP("LD C, 0x%x", d8)

    dev->cpu.BC.byte.C = d8;
}

CPU_INSTR(ld_D_d8)
{
    uint8_t d8 = FETCH_BYTE();
    DECOMP("LD D, 0x%x", d8)

    dev->cpu.DE.byte.D = d8;
}

CPU_INSTR(ld_E_d8)
{
    uint8_t d8 = FETCH_BYTE();
    DECOMP("LD E, 0x%x", d8)

    dev->cpu.DE.byte.E = d8;
}

CPU_INSTR(ld_H_d8)
{
    uint8_t d8 = FETCH_BYTE();
    DECOMP("LD H, 0x%x", d8)

    dev->cpu.HL.byte.H = d8;
}

CPU_INSTR(ld_L_d8)
{
    uint8_t d8 = FETCH_BYTE();
    DECOMP("LD L, 0x%x", d8)

    dev->cpu.HL.byte.L = d8;
}

CPU_INSTR(ld_HLmem_d8)
{
    uint8_t d8 = FETCH_BYTE();
    DECOMP("LD [HL], 0x%x", d8)

    dev->mem[dev->cpu.HL.val] = d8;
}

CPU_INSTR(ld_A_d8)
{
    uint8_t d8 = FETCH_BYTE();
    DECOMP("LD A, 0x%x", d8)

    dev->cpu.AF.byte.A = d8;
}

CPU_INSTR(rlca)
{
    DECOMP("RLCA")
    const uint8_t carry = (dev->cpu.AF.byte.A & 0x80) ? 1 : 0;
    dev->cpu.AF.byte.A = ((dev->cpu.AF.byte.A << 1) & 0xFF) | carry;

    dev->cpu.AF.byte.F = 0;
    dev->cpu.AF.flag.C = carry;
}

CPU_INSTR(rrca)
{
    DECOMP("RRCA")
    const uint8_t carry = (dev->cpu.AF.byte.A) & 0x01;
    dev->cpu.AF.byte.A = ((dev->cpu.AF.byte.A >> 1) & 0xFF) | (carry ? 0x80 : 0);

    dev->cpu.AF.byte.F = 0;
    dev->cpu.AF.flag.C = carry;
}

CPU_INSTR(rla)
{
    DECOMP("RLA")
    const uint8_t carry = (dev->cpu.AF.byte.A & 0x80) ? 1 : 0;
    dev->cpu.AF.byte.A = ((dev->cpu.AF.byte.A << 1) & 0xFF) | dev->cpu.AF.flag.C;

    dev->cpu.AF.byte.F = 0;
    dev->cpu.AF.flag.C = carry;
}

CPU_INSTR(rra)
{
    DECOMP("RRA")
    const uint8_t carry = (dev->cpu.AF.byte.A) & 0x01;
    dev->cpu.AF.byte.A = ((dev->cpu.AF.byte.A >> 1) & 0xFF) | (dev->cpu.AF.flag.C ? 0x80 : 0);

    dev->cpu.AF.byte.F = 0;
    dev->cpu.AF.flag.C = carry;
}

#define DAA_C(x) dev->cpu.AF.flag.C == x
#define DAA_H(x) dev->cpu.AF.flag.H == x
#define DAA_HI(a, b) (((dev->cpu.AF.byte.A & 0xF0) >> 4 >= 0x##a) && ((dev->cpu.AF.byte.A & 0xF0) >> 4 <= 0x##b))
#define DAA_LO(a, b) (((dev->cpu.AF.byte.A & 0x0F) >= 0x##a) && ((dev->cpu.AF.byte.A & 0x0F) <= 0x##b))

CPU_INSTR(daa)
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

CPU_INSTR(cpl)
{
    DECOMP("CPL")
    dev->cpu.AF.byte.A = ~dev->cpu.AF.byte.A;

    dev->cpu.AF.flag.H = 1;
    dev->cpu.AF.flag.N = 1;
}

CPU_INSTR(scf)
{
    DECOMP("SCF")

    dev->cpu.AF.flag.C = 1;
    dev->cpu.AF.flag.H = 0;
    dev->cpu.AF.flag.N = 0;
}

CPU_INSTR(ccf)
{
    DECOMP("CCF")
    
    dev->cpu.AF.flag.C = dev->cpu.AF.flag.C ? 0 : 1;
    dev->cpu.AF.flag.H = 0;
    dev->cpu.AF.flag.N = 0;
}

CPU_INSTR(jr_r8)
{
    int8_t r8 = FETCH_BYTE();
    DECOMP("JR %i", r8)

    dev->cpu.PC.val += r8;
}

CPU_INSTR(jr_nz_r8)
{
    int8_t r8 = FETCH_BYTE();
    DECOMP("JR NZ, %i", r8)

    if (dev->cpu.AF.flag.Z == 0) dev->cpu.PC.val += r8;
}

CPU_INSTR(jr_z_r8)
{
    int8_t r8 = FETCH_BYTE();
    DECOMP("JR Z, %i", r8)

    if (dev->cpu.AF.flag.Z == 1) dev->cpu.PC.val += r8;
}

CPU_INSTR(jr_nc_r8)
{
    int8_t r8 = FETCH_BYTE();
    DECOMP("JR NC, %i", r8)

    if (dev->cpu.AF.flag.C == 0) dev->cpu.PC.val += r8;
}

CPU_INSTR(jr_c_r8)
{
    int8_t r8 = FETCH_BYTE();
    DECOMP("JR C, %i", r8)

    if (dev->cpu.AF.flag.C == 1) dev->cpu.PC.val += r8;
}

CPU_INSTR(stop)
{
    DECOMP("STOP")
    ++dev->cpu.PC.val;
}