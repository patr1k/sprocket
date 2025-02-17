#include "mem.h"

#include <stdlib.h>
#include <memory.h>

uint8_t* mem_create()
{
    const uint16_t size = 0xFFFF;
    uint8_t *mem = (uint8_t*)malloc(sizeof(uint8_t) * size);
    memset(mem, 0, size);
    return mem;
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