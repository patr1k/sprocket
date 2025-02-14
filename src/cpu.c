#include "cpu.h"

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