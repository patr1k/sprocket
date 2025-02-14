/**
 * CPU Block 0 Instructions
 * 
 * @author patrik <patr1k@cyntacs.com>
 */

#include "cpu.h"
#include "cpu_instr_set.h"

void cpu_ld_r16_imm16(struct cpu_state *cpu, enum cpu_reg_r16 r16, uint16_t imm16)
{
    *cpu_ptr_r16(cpu, r16) = imm16;
}

void cpu_ld_r16mem_a(struct cpu_state *cpu, uint8_t *mem, enum cpu_reg_r16 r16mem)
{
    mem[*cpu_ptr_r16(cpu, r16mem)] = cpu->AF.byte.A;
}

void cpu_ld_a_r16mem(struct cpu_state *cpu, uint8_t *mem, enum cpu_reg_r16 r16mem)
{
    cpu->AF.byte.A = mem[*cpu_ptr_r16(cpu, r16mem)];
}