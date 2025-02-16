#include <stdio.h>
#include <stdlib.h>

#define DECOMP_ON 1

#include "cpu_isa.h"
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
        const instr = cpu_fetch_byte(&gameboy);
        if (instr == 0xCB) {
            cpu_isa[instr](&gameboy);
        } else {
            cpu_isa_cb[instr](&gameboy);
        }
        
        if (gameboy.cpu.BC.byte.B == 0x66) running = false;
    }

    printf("CPU stopped on B = 0x66\n");

    mem_destroy(gameboy.mem);

    return 0;
}