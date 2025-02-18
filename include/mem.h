#pragma once

#include "gameboy.h"

#include <stdint.h>

uint8_t* mem_create();
void mem_set_boot_state(uint8_t* mem);
void mem_destroy(uint8_t* mem);
void mem_load_rom(uint8_t* mem, uint8_t* rom, uint32_t len);
void mem_write(struct gbc *dev, uint16_t addr, uint8_t data);