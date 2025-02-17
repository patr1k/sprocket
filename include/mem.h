#pragma once

#include <stdint.h>

uint8_t* mem_create();
void mem_destroy(uint8_t* mem);
void mem_load_rom(uint8_t* mem, uint8_t* rom, uint32_t len);