#include "cpu.h"

void cpu_set_flag(struct cpu_state *cpu, enum cpu_flag flag, bool value)
{
    if (value)
        cpu->AF.byte.F |= flag;
    else
        cpu->AF.byte.F &= ~flag;
}

bool cpu_get_flag(struct cpu_state *cpu, enum cpu_flag flag)
{
    return (cpu->AF.byte.F & flag) > 0;
}

uint16_t* cpu_ptr_r16(struct cpu_state *cpu, enum cpu_reg_r16 r16)
{
    switch (r16)
    {
        case R16_BC: return &cpu->BC.value; break;
        case R16_DE: return &cpu->DE.value; break;
        case R16_HL: return &cpu->HL.value; break;
        case R16_SP: return &cpu->SP; break;
    }
}

uint8_t* cpu_ptr_r8(struct cpu_state *cpu, enum cpu_reg_r8 r8)
{
    switch (r8)
    {
        case R8_A: return &cpu->AF.byte.A;
        default: return 0;
    }
}