#include <stdio.h>
#include <stdlib.h>

#define DECOMP_ON 1
#include "cpu.h"
#include "cpu_instr_set.h"
#include "mem.h"

#include "boot_rom.h"

int main()
{
    struct gbc gameboy = {};
    gameboy.mem = mem_create();
    mem_load_rom(gameboy.mem, boot_rom);

    bool running = true;
    while (running)
    {
        cpu_exe(&gameboy);
        if (gameboy.cpu.BC.byte.B == 0x66) running = false;
    }

    printf("CPU stopped on B = 0x66\n");

    mem_destroy(gameboy.mem);

    return 0;
}