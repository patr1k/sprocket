#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "cpu_instr_set.h"
#include "mem.h"

int main()
{
    struct gbc gameboy = {};
    gameboy.mem = mem_create();

    gameboy.cpu.AF.byte.A = 0;
    gameboy.cpu.AF.flag.C = 1;
    gameboy.cpu.AF.flag.N = 1;

    printf("The current flags are: 0x%x%x\n", (gameboy.cpu.AF.byte.F & 0xF0) >> 4, gameboy.cpu.AF.byte.F & 0x0F);
    printf("Flag Z: %u\n", gameboy.cpu.AF.flag.Z);
    printf("Flag N: %u\n", gameboy.cpu.AF.flag.N);
    printf("Flag H: %u\n", gameboy.cpu.AF.flag.H);
    printf("Flag C: %u\n", gameboy.cpu.AF.flag.C);
    printf("A: 0x%x\n", gameboy.cpu.AF.byte.A);
    printf("F: 0x%x\n", gameboy.cpu.AF.byte.F);
    printf("AF: 0x%x\n", gameboy.cpu.AF.val);
    
    gameboy.cpu.HL.byte.H = 0x3c;
    gameboy.cpu.HL.byte.L = 0xbf;

    printf("The low byte is: 0x%x\n", gameboy.cpu.HL.byte.L);
    printf("The high byte is: 0x%x\n", gameboy.cpu.HL.byte.H);
    printf("The register is: 0x%x\n", gameboy.cpu.HL.val);

    cpu_ld_r16_imm16(&gameboy, R16_DE, 12345);

    printf("The value of DE is: %u\n", gameboy.cpu.DE.val);

    gameboy.mem[12345] = 5;
    cpu_ld_a_r16mem(&gameboy, R16_DE);

    printf("The value of A is %u \n", gameboy.cpu.AF.byte.A);

    mem_destroy(gameboy.mem);

    return 0;
}