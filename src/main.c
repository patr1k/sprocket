#include <stdio.h>
#include <stdlib.h>

#define DECOMP_ON 1

#include "cpu_isa.h"
#include "mem.h"

#include "boot_rom.h"

int main()
{
    struct gbc gameboy = {};

    gameboy.cpu.AF.byte.A = 0x11;
    gameboy.cpu.AF.byte.F = 0;
    gameboy.cpu.AF.flag.Z = 1;
    gameboy.cpu.BC.val = 0;
    gameboy.cpu.DE.val = 0xFF56;
    gameboy.cpu.HL.val = 0x000D;
    gameboy.cpu.PC.val = 0x0000;
    gameboy.cpu.SP.val = 0xFFFE;

    gameboy.mem = mem_create();
    mem_load_rom(gameboy.mem, boot_rom, boot_rom_len);

    uint64_t step = 0;
    while (gameboy.cpu.mode.val == 0)
    {
        gameboy.cpu.IR = gameboy.mem[gameboy.cpu.PC.val];
        printf("PC = 0x%04x IR = 0x%02x : ", gameboy.cpu.PC.val, gameboy.cpu.IR);
        gameboy.cpu.PC.val++;
        cpu_isa[gameboy.cpu.IR](&gameboy);
        step++;
        if (step == 50) gameboy.cpu.mode.flag.LOCKED = 1;
    }

    printf("CPU stopped on B = 0x66\n");

    mem_destroy(gameboy.mem);

    return 0;
}