#include "cpu.h"
#include "cpu_instr_set.h"

uint16_t* cpu_r16_ptr(struct gbc* dev, enum cpu_reg_r16 r16)
{
    switch (r16)
    {
        case R16_BC: return &dev->cpu.BC.val; break;
        case R16_DE: return &dev->cpu.DE.val; break;
        case R16_HL: return &dev->cpu.HL.val; break;
        case R16_SP: return &dev->cpu.SP; break;
    }
}

uint8_t* cpu_r8_ptr(struct gbc* dev, enum cpu_reg_r8 r8)
{
    switch (r8)
    {
        case R8_B: return &dev->cpu.BC.byte.B;
        case R8_C: return &dev->cpu.BC.byte.C;
        case R8_D: return &dev->cpu.DE.byte.D;
        case R8_E: return &dev->cpu.DE.byte.E;
        case R8_H: return &dev->cpu.HL.byte.H;
        case R8_L: return &dev->cpu.HL.byte.L;
        case R8_HL: return &dev->mem[dev->cpu.HL.val];
        case R8_A: return &dev->cpu.AF.byte.A;
    }
}

uint16_t cpu_r16_val(struct gbc* dev, enum cpu_reg_r16 r16)
{
    switch (r16)
    {
        case R16_BC: return dev->cpu.BC.val;
        case R16_DE: return dev->cpu.DE.val;
        case R16_HL: return dev->cpu.HL.val;
        case R16_SP: return dev->cpu.SP;
    }
}

uint8_t cpu_r8_val(struct gbc* dev, enum cpu_reg_r8 r8)
{
    switch (r8)
    {
        case R8_B: return dev->cpu.BC.byte.B;
        case R8_C: return dev->cpu.BC.byte.C;
        case R8_D: return dev->cpu.DE.byte.D;
        case R8_E: return dev->cpu.DE.byte.E;
        case R8_H: return dev->cpu.HL.byte.H;
        case R8_L: return dev->cpu.HL.byte.L;
        case R8_HL: return dev->mem[dev->cpu.HL.val];
        case R8_A: return dev->cpu.AF.byte.A;
    }
}

uint8_t cpu_fetch_byte(struct gbc* dev)
{
    return dev->mem[dev->cpu.PC++];
}

uint16_t cpu_fetch_word(struct gbc* dev)
{
    return dev->mem[dev->cpu.PC++] | (dev->mem[dev->cpu.PC++] << 4);
}

void cpu_exe(struct gbc* dev)
{
    const uint8_t instr = cpu_fetch_byte(dev);
    switch (instr)
    {
        case 0b00000000:    // 0x00: NOP
            cpu_nop(dev);
            break;

        case 0b00000001:    // 0x01: LD BC, imm16
        case 0b00010001:    // 0x11: LD DE, imm16
        case 0b00100001:    // 0x21: LD HL, imm16
        case 0b00110001:    // 0x31: LD SP, imm16
            cpu_ld_r16_imm16(dev, (instr & 0b00110000) >> 4, cpu_fetch_word(dev));
            break;

        case 0b00000010:    // 0x02: LD [BC], A
        case 0b00010010:    // 0x12: LD [DE], A
        case 0b00100010:    // 0x22: LD [HL], A
        case 0b00110010:    // 0x32: LD [SP], A
            cpu_ld_r16mem_a(dev, (instr & 0b00110000) >> 4);
            break;

        case 0b00001010:    // 0x0A: LD A, [BC]
        case 0b00011010:    // 0x1A: LD A, [DE]
        case 0b00101010:    // 0x2A: LD A, [HL]
        case 0b00111010:    // 0x3A: LD A, [SP]
            cpu_ld_a_r16mem(dev, (instr & 0b00110000) >> 4);
            break;
        
        case 0b00001000:    // 0x08: LD [imm16], SP
            cpu_ld_imm16_sp(dev, cpu_fetch_word(dev));
            break;

        case 0b00000011:    // 0x03: INC BC
        case 0b00010011:    // 0x13: INC DE
        case 0b00100011:    // 0x23: INC HL
        case 0b00110011:    // 0x33: INC SP
            cpu_inc_r16(dev, (instr & 0b00110000) >> 4);
            break;

        case 0b00001011:    // 0x0B: DEC BC
        case 0b00011011:    // 0x1B: DEC DE
        case 0b00101011:    // 0x2B: DEC HL
        case 0b00111011:    // 0x3B: DEC SP
            cpu_dec_r16(dev, (instr & 0b00110000) >> 4);
            break;

        case 0b00001001:    // 0x09: ADD HL, BC
        case 0b00011001:    // 0x19: ADD HL, DE
        case 0b00101001:    // 0x29: ADD HL, HL
        case 0b00111001:    // 0x39: ADD HL, SP
            cpu_add_hl_r16(dev, (instr & 0b00110000) >> 4);
            break;

        case 0b00000111:    // 0x07: RLCA
            cpu_rlca(dev);
            break;

        case 0b00001111:    // 0x0F: RRCA
            cpu_rrca(dev);
            break;

        case 0b00010111:    // 0x17: RLA
            cpu_rla(dev);
            break;

        case 0b00011111:    // 0x1F: RRA
            cpu_rra(dev);
            break;

        case 0b00100111:    // 0x27: DAA
            cpu_daa(dev);
            break;
        
        case 0b00101111:    // 0x2F: CPL
            cpu_cpl(dev);
            break;
        
        case 0b00110111:    // 0x37: SCF
            cpu_scf(dev);
            break;
        
        case 0b00111111:    // 0x3F: CCF
            cpu_ccf(dev);
            break;

        case 0b00011000:    // 0x18: JR imm8
            cpu_jr_imm8(dev, cpu_fetch_byte(dev));
            break;

        case 0b00100000:    // 0x20: JR NZ, imm8
        case 0b00101000:    // 0x28: JR Z,  imm8
        case 0b00110000:    // 0x30: JR NC, imm8
        case 0b00111000:    // 0x38: JR C,  imm8
            cpu_jr_cond_imm8(dev, (instr & 0b00011000) >> 3, cpu_fetch_byte(dev));
            break;

        case 0b00010000:    // 0x10: STOP
            cpu_stop(dev);
            break;

        case 0b01000000:    // 0x40: LD B, B
        case 0b01000001:    // 0x41: LD B, C
        case 0b01000010:    // 0x42: LD B, D
        case 0b01000011:    // 0x43: LD B, E
        case 0b01000100:    // 0x44: LD B, H
        case 0b01000101:    // 0x45: LD B, L
        case 0b01000110:    // 0x46: LD B, [HL]
        case 0b01000111:    // 0x47: LD B, A

        case 0b01001000:    // 0x48: LD C, B
        case 0b01001001:    // 0x49: LD C, C
        case 0b01001010:    // 0x4A: LD C, D
        case 0b01001011:    // 0x4B: LD C, E
        case 0b01001100:    // 0x4C: LD C, H
        case 0b01001101:    // 0x4D: LD C, L
        case 0b01001110:    // 0x4E: LD C, [HL]
        case 0b01001111:    // 0x4F: LD C, A

        case 0b01010000:    // 0x50: LD D, B
        case 0b01010001:    // 0x51: LD D, C
        case 0b01010010:    // 0x52: LD D, D
        case 0b01010011:    // 0x53: LD D, E
        case 0b01010100:    // 0x54: LD D, H
        case 0b01010101:    // 0x55: LD D, L
        case 0b01010110:    // 0x56: LD D, [HL]
        case 0b01010111:    // 0x57: LD D, A

        case 0b01011000:    // 0x58: LD E, B
        case 0b01011001:    // 0x59: LD E, C
        case 0b01011010:    // 0x5A: LD E, D
        case 0b01011011:    // 0x5B: LD E, E
        case 0b01011100:    // 0x5C: LD E, H
        case 0b01011101:    // 0x5D: LD E, L
        case 0b01011110:    // 0x5E: LD E, [HL]
        case 0b01011111:    // 0x5F: LD E, A

        case 0b01100000:    // 0x60: LD H, B
        case 0b01100001:    // 0x61: LD H, C
        case 0b01100010:    // 0x62: LD H, D
        case 0b01100011:    // 0x63: LD H, E
        case 0b01100100:    // 0x64: LD H, H
        case 0b01100101:    // 0x65: LD H, L
        case 0b01100110:    // 0x66: LD H, [HL]
        case 0b01100111:    // 0x67: LD H, A

        case 0b01101000:    // 0x68: LD L, B
        case 0b01101001:    // 0x69: LD L, C
        case 0b01101010:    // 0x6A: LD L, D
        case 0b01101011:    // 0x6B: LD L, E
        case 0b01101100:    // 0x6C: LD L, H
        case 0b01101101:    // 0x6D: LD L, L
        case 0b01101110:    // 0x6E: LD L, [HL]
        case 0b01101111:    // 0x6F: LD L, A

        case 0b01110000:    // 0x70: LD [HL], B
        case 0b01110001:    // 0x71: LD [HL], C
        case 0b01110010:    // 0x72: LD [HL], D
        case 0b01110011:    // 0x73: LD [HL], E
        case 0b01110100:    // 0x74: LD [HL], H
        case 0b01110101:    // 0x75: LD [HL], L
        case 0b01110111:    // 0x77: LD [HL], A

        case 0b01111000:    // 0x77: LD A, B
        case 0b01111001:    // 0x78: LD A, C
        case 0b01111010:    // 0x79: LD A, D
        case 0b01111011:    // 0x7A: LD A, E
        case 0b01111100:    // 0x7B: LD A, H
        case 0b01111101:    // 0x7C: LD A, L
        case 0b01111110:    // 0x7D: LD A, [HL]
        case 0b01111111:    // 0x7E: LD A, A
            cpu_ld_r8_r8(dev, (instr & 0b00111000) >> 3, instr & 0b00000111);
            break;
    }

}