#include "mem.h"

#include <stdlib.h>
#include <memory.h>

uint8_t* mem_create()
{
    const uint32_t size = 0x10000;
    uint8_t *mem = (uint8_t*)malloc(sizeof(uint8_t) * size);
    memset(mem, 0, size);
    return mem;
}

void mem_set_boot_state(uint8_t* mem)
{
    mem_load_rom(mem, boot_rom, boot_rom_len);

    mem[0xFF05] = 0x00;
    mem[0xFF06] = 0x00;
    mem[0xFF07] = 0x00;
    mem[0xFF10] = 0x80;
    mem[0xFF11] = 0xBF;
    mem[0xFF12] = 0xF3;
    mem[0xFF14] = 0xBF;
    mem[0xFF16] = 0x3F;
    mem[0xFF17] = 0x00;
    mem[0xFF19] = 0xBF;
    mem[0xFF1A] = 0x7F;
    mem[0xFF1B] = 0xFF;
    mem[0xFF1C] = 0x9F;
    mem[0xFF1E] = 0xBF;
    mem[0xFF20] = 0xFF;
    mem[0xFF21] = 0x00;
    mem[0xFF22] = 0x00;
    mem[0xFF23] = 0xBF;
    mem[0xFF24] = 0x77;
    mem[0xFF25] = 0xF3;
    mem[0xFF26] = 0xF1;
    mem[0xFF40] = 0x91;
    mem[0xFF42] = 0x00;
    mem[0xFF43] = 0x00;
    mem[0xFF45] = 0x00;
    mem[0xFF47] = 0xFC;
    mem[0xFF48] = 0xFF;
    mem[0xFF49] = 0xFF;
    mem[0xFF4A] = 0x00;
    mem[0xFF4B] = 0x00;
    mem[0xFFFF] = 0x00;
}

void mem_destroy(uint8_t* mem)
{
    free(mem);
}

void mem_load_rom(uint8_t* mem, uint8_t* rom, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++)
    {
        mem[i] = rom[i];
    }
}

void mem_write(struct gbc *dev, uint16_t addr, uint8_t data)
{
    if (addr < 0x8000)
    {
        DEBUG("Tried to write to read-only memory: $%04x", addr);
        return;
    }

    if ((addr >= 0xE000) && (addr < 0xFE00))
    {
        dev->mem[addr] = data;
        mem_write(dev, addr - 0x2000, data);
        return;
    }

    if ((addr >= 0xFEA0) && (addr < 0xFEFF))
    {
        DEBUG("Tried to write to read-only memory: $%04x", addr);
        return;
    }

    dev->mem[addr] = data;
}