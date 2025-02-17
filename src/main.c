#include <stdio.h>
#include <stdlib.h>

#define DECOMP_ON 1

#include "cpu_isa.h"
#include "mem.h"

int main()
{
    struct gbc gameboy = {};

    gameboy.cpu.AF.byte.A = 0x01;
    gameboy.cpu.AF.byte.F = 0xB0;
    gameboy.cpu.BC.val = 0x0013;
    gameboy.cpu.DE.val = 0x00D8;
    gameboy.cpu.HL.val = 0x014D;
    gameboy.cpu.PC.val = 0x0000;
    gameboy.cpu.SP.val = 0xFFFE;

    gameboy.mem = mem_create();
    mem_set_boot_state(gameboy.mem);

    uint64_t step = 0;
    while (gameboy.cpu.mode.val == 0)
    {
        gameboy.cpu.IR = gameboy.mem[gameboy.cpu.PC.val];
        printf("PC = 0x%04x IR = 0x%02x : ", gameboy.cpu.PC.val, gameboy.cpu.IR);
        gameboy.cpu.PC.val++;
        cpu_isa[gameboy.cpu.IR](&gameboy);
        step++;
        if (step == 10000) gameboy.cpu.mode.flag.LOCKED = 1;
    }

    printf("CPU stopped on step = %lu\n", step);

    mem_destroy(gameboy.mem);

    return 0;
}