/**
 * CPU Block 3 Instructions
 */

 #include "cpu_isa.h"

CPU_INSTR(add_A_d8)
{
    uint8_t d8 = FETCH_BYTE();
    DECOMP("ADD A, 0x%x", d8)

    uint16_t result16 = dev->cpu.AF.byte.A + d8;
    uint8_t result8 = result16 & 0xFF;
    uint8_t half = ((dev->cpu.AF.byte.A ^ d8 ^ result8) & 0x10) > 0;
    uint8_t carry = (result16 & 0x100) > 0;

    dev->cpu.AF.byte.A = result8;
    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.Z = result8 == 0 ? 1 : 0;
    dev->cpu.AF.flag.H = half ? 1 : 0;
    dev->cpu.AF.flag.C = carry ? 1 : 0;
}

CPU_INSTR(adc_A_d8)
{
    uint8_t d8 = FETCH_BYTE();
    DECOMP("ADC A, 0x%x", d8)

    uint16_t result16 = dev->cpu.AF.byte.A + d8 + dev->cpu.AF.flag.C;
    uint8_t result8 = result16 & 0xFF;
    uint8_t half = ((dev->cpu.AF.byte.A ^ d8 ^ result8) & 0x10) > 0;
    uint8_t carry = (result16 & 0x100) > 0;

    dev->cpu.AF.byte.A = result8;
    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.Z = result8 == 0 ? 1 : 0;
    dev->cpu.AF.flag.H = half ? 1 : 0;
    dev->cpu.AF.flag.C = carry ? 1 : 0;
}

CPU_INSTR(sub_A_d8)
{
    uint8_t d8 = FETCH_BYTE();
    DECOMP("SUB A, 0x%x", d8)

    uint16_t result16 = dev->cpu.AF.byte.A - d8;
    uint8_t result8 = result16 & 0xFF;
    uint8_t half = ((dev->cpu.AF.byte.A ^ d8 ^ result8) & 0x10) > 0;
    uint8_t carry = (result16 & 0x100) > 0;

    dev->cpu.AF.byte.A = result8;
    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.Z = result8 == 0 ? 1 : 0;
    dev->cpu.AF.flag.H = half ? 1 : 0;
    dev->cpu.AF.flag.C = carry ? 1 : 0;
}

CPU_INSTR(sbc_A_d8)
{
    uint8_t d8 = FETCH_BYTE();
    DECOMP("SBC A, 0x%x", d8)

    uint16_t result16 = dev->cpu.AF.byte.A - d8 - dev->cpu.AF.flag.C;
    uint8_t result8 = result16 & 0xFF;
    uint8_t half = ((dev->cpu.AF.byte.A ^ d8 ^ result8) & 0x10) > 0;
    uint8_t carry = (result16 & 0x100) > 0;

    dev->cpu.AF.byte.A = result8;
    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.Z = result8 == 0 ? 1 : 0;
    dev->cpu.AF.flag.H = half ? 1 : 0;
    dev->cpu.AF.flag.C = carry ? 1 : 0;
}

CPU_INSTR(and_A_d8)
{
    uint8_t d8 = FETCH_BYTE();
    DECOMP("AND A, 0x%x", d8)

    dev->cpu.AF.byte.A &= d8;
    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.C = 0;
    dev->cpu.AF.flag.H = 1;
    dev->cpu.AF.flag.Z = dev->cpu.AF.byte.A == 0 ? 1 : 0;
}

CPU_INSTR(xor_A_d8)
{
    uint8_t d8 = FETCH_BYTE();
    DECOMP("XOR A, 0x%x", d8)
    
    dev->cpu.AF.byte.A ^= d8;
    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.C = 0;
    dev->cpu.AF.flag.H = 0;
    dev->cpu.AF.flag.Z = dev->cpu.AF.byte.A == 0 ? 1 : 0;
}

CPU_INSTR(or_A_d8)
{
    uint8_t d8 = FETCH_BYTE();
    DECOMP("OR A, 0x%x", d8)
    
    dev->cpu.AF.byte.A |= d8;
    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.C = 0;
    dev->cpu.AF.flag.H = 0;
    dev->cpu.AF.flag.Z = dev->cpu.AF.byte.A == 0 ? 1 : 0;
}

CPU_INSTR(cp_A_d8)
{
    uint8_t d8 = FETCH_BYTE();
    DECOMP("CP A, 0x%x", d8)
    
    uint16_t result16 = dev->cpu.AF.byte.A - d8;
    uint8_t result8 = result16;
    uint8_t half = ((dev->cpu.AF.byte.A ^ d8 ^ result8) & 0x10) > 0;
    uint8_t carry = (result16 & 0x100) > 0;

    dev->cpu.AF.flag.N = 1;
    dev->cpu.AF.flag.Z = result8 == 0 ? 1 : 0;
    dev->cpu.AF.flag.H = half ? 1 : 0;
    dev->cpu.AF.flag.C = carry ? 1 : 0;
}

CPU_INSTR(ret)
{
    DECOMP("RET")
    dev->cpu.PC.val = POP_WORD();
}

#define RET_COND(cond_sym, cond_stmt) CPU_INSTR(ret_##cond_sym) \
    { \
        DECOMP("RET " #cond_sym) \
        if (dev->cpu.AF.flag.cond_stmt) \
            dev->cpu.PC.val = POP_WORD(); \
    }

RET_COND(Z, Z == 1)
RET_COND(NZ, Z == 0)
RET_COND(C, C == 1)
RET_COND(NC, C == 0)

CPU_INSTR(reti)
{
    DECOMP("RETI")

    dev->cpu.PC.byte.L = dev->mem[dev->cpu.SP.val];
    dev->cpu.PC.byte.H = dev->mem[dev->cpu.SP.val + 1];
    dev->cpu.SP.val = dev->cpu.SP.val + 2;

    dev->cpu.mode.flag.IME = 1;
}

#define JP_COND_A16(cond_sym, cond_stmt) CPU_INSTR(jp_##cond_sym##_a16) \
    { \
        uint16_t a16 = FETCH_WORD(); \
        DECOMP("JP " #cond_sym ", 0x%x", a16) \
        if (dev->cpu.AF.flag.cond_stmt) \
        dev->cpu.PC.val = a16; \
    }

JP_COND_A16(Z, Z == 1)
JP_COND_A16(NZ, Z == 0)
JP_COND_A16(C, C == 1)
JP_COND_A16(NC, C == 0)

CPU_INSTR(jp_a16)
{
    uint16_t a16 = FETCH_WORD();
    DECOMP("JP 0x%x", a16)

    dev->cpu.PC.val = a16;
}

CPU_INSTR(jp_HL)
{
    DECOMP("JP HL")

    dev->cpu.PC.val = dev->cpu.HL.val;
}

#define CALL_COND_A16(cond_sym, cond_stmt) CPU_INSTR(call_##cond_sym##_a16) \
    { \
        uint16_t a16 = FETCH_WORD(); \
        DECOMP("CALL " #cond_sym ", 0x%x", a16) \
        if (dev->cpu.AF.flag.cond_stmt) \
        { \
            PUSH_WORD(dev->cpu.PC.val); \
            dev->cpu.PC.val = a16; \
        } \
    }

CALL_COND_A16(Z, Z == 1)
CALL_COND_A16(NZ, Z == 0)
CALL_COND_A16(C, C == 1)
CALL_COND_A16(NC, C == 0)

CPU_INSTR(call_a16)
{
    uint16_t a16 = FETCH_WORD();
    DECOMP("CALL 0x%x", a16)

    PUSH_WORD(dev->cpu.PC.val);
    dev->cpu.PC.val = a16;
}

#define RST_VEC(vec, a16) CPU_INSTR(rst_##vec##h) \
    { \
        DECOMP("RST " #vec "H") \
        PUSH_WORD(dev->cpu.PC.val); \
        dev->cpu.PC.val = a16; \
    }

RST_VEC(00, 0x0000)
RST_VEC(08, 0x0040)
RST_VEC(10, 0x0080)
RST_VEC(18, 0x00C0)
RST_VEC(20, 0x0100)
RST_VEC(28, 0x0140)
RST_VEC(30, 0x0180)
RST_VEC(38, 0x01C0)

#define POP_R16(r16) CPU_INSTR(pop_##r16) \
    { \
        DECOMP("POP " #r16) \
        dev->cpu.r16.val = POP_WORD(); \
    }

POP_R16(BC)
POP_R16(DE)
POP_R16(HL)
POP_R16(AF)

#define PUSH_R16(r16) CPU_INSTR(push_##r16) \
    { \
        DECOMP("PUSH " #r16) \
        PUSH_WORD(dev->cpu.r16.val); \
    }

PUSH_R16(BC)
PUSH_R16(DE)
PUSH_R16(HL)
PUSH_R16(AF)

CPU_INSTR(ldh_a8_A)
{
    uint8_t a8 = FETCH_BYTE();
    DECOMP("LD [$FF00 + $%02x], A", a8)

    dev->mem[0xFF | a8] = dev->cpu.AF.byte.A;
}

CPU_INSTR(ldh_Cmem_A)
{
    uint8_t a8 = FETCH_BYTE();
    DECOMP("LD [$FF00 + C], A")

    dev->mem[0xFF | dev->cpu.BC.byte.C] = dev->cpu.AF.byte.A;
}

CPU_INSTR(ld_a16_A)
{
    uint8_t a16 = FETCH_WORD();
    DECOMP("LD [0x%x], A", a16)

    dev->mem[a16] = dev->cpu.AF.byte.A;
}

CPU_INSTR(ldh_A_a8)
{
    uint8_t a8 = FETCH_BYTE();
    DECOMP("LD A, [$FF00 + $%02x]", a8)

    dev->cpu.AF.byte.A = dev->mem[0xFF | a8];
}

CPU_INSTR(ldh_A_Cmem)
{
    uint8_t a8 = FETCH_BYTE();
    DECOMP("LD A, [$FF00 + C]")

    dev->cpu.AF.byte.A = dev->mem[0xFF | dev->cpu.BC.byte.C];
}

CPU_INSTR(ld_A_a16)
{
    uint8_t a16 = FETCH_WORD();
    DECOMP("LD A, [0x%x]", a16)

    dev->cpu.AF.byte.A = dev->mem[a16];
}

CPU_INSTR(di)
{
    DECOMP("DI")
    dev->cpu.mode.flag.IME = 0;
}

CPU_INSTR(ei)
{
    DECOMP("EI")
    dev->cpu.mode.flag.IME = 1;
}

CPU_INSTR(add_SP_r8)
{
    int8_t r8 = FETCH_BYTE();
    DECOMP("ADD SP, %i", r8)

    uint16_t result16 = dev->cpu.SP.val + r8;
    uint8_t result8 = result16;
    uint8_t half = ((dev->cpu.SP.val  ^ r8 ^ result8) & 0x10) > 0;
    uint8_t carry = (result16 & 0x100) > 0;

    dev->cpu.SP.val = result8;

    dev->cpu.AF.flag.Z = 0;
    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.H = half ? 1 : 0;
    dev->cpu.AF.flag.C = carry ? 1 : 0;
}

CPU_INSTR(ld_HL_SPr8)
{
    int8_t r8 = FETCH_BYTE();
    DECOMP("LD HL, SP + %i", r8)

    uint16_t result16 = dev->cpu.SP.val + r8;
    uint8_t result8 = result16;
    uint8_t half = ((dev->cpu.SP.val  ^ r8 ^ result8) & 0x10) > 0;
    uint8_t carry = (result16 & 0x100) > 0;

    dev->cpu.HL.val = result8;

    dev->cpu.AF.flag.Z = 0;
    dev->cpu.AF.flag.N = 0;
    dev->cpu.AF.flag.H = half ? 1 : 0;
    dev->cpu.AF.flag.C = carry ? 1 : 0;
}

CPU_INSTR(ld_SP_HL)
{
    DECOMP("LD SP, HL")

    dev->cpu.SP.val = dev->cpu.HL.val;
}
