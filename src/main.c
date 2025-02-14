#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "cpu_instr_set.h"
#include "mem.h"

int main()
{
    struct cpu_state state = {};
    uint8_t *mem = mem_create();

    cpu_set_flag(&state, FLAG_SUBTRACT, true);
    
    state.HL.byte.H = 0x3c;
    state.HL.byte.L = 0xbf;

    printf("The low byte is: 0x%x\n", state.HL.byte.L);
    printf("The high byte is: 0x%x\n", state.HL.byte.H);
    printf("The register is: 0x%x\n", state.HL.value);

    cpu_ld_r16_imm16(&state, R16_DE, 12345);

    printf("The value of DE is: %u\n", state.DE.value);

    mem[12345] = 5;
    cpu_ld_a_r16mem(&state, mem, R16_DE);

    printf("The value of A is %u \n", state.AF.byte.A);

    mem_destroy(mem);

    return 0;
}