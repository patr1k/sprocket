#include <stdio.h>
#include <stdlib.h>

#define ENABLE_DECOMP
#include "cpu.h"
#include "cpu_instr_set.h"
#include "mem.h"

int main()
{
    struct gbc gameboy = {};
    gameboy.mem = mem_create();

    
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

    uint8_t daa_num = 0xB5;
    cpu_ld_r8_imm8(&gameboy, R8_A, daa_num);
    cpu_daa(&gameboy);
    printf("The daa value of 0x%x is 0x%x \n", daa_num, gameboy.cpu.AF.byte.A);
    printf("C = %u\n", gameboy.cpu.AF.flag.C);

    uint8_t test = 0x8F;
    int8_t test2 = test;
    printf("The unsigned is %u and the signed is %i\n", test, test2);

    mem_destroy(gameboy.mem);

    return 0;
}