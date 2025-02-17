#pragma once

#include "cpu.h"

struct gbc
{
    struct cpu_state cpu;
    uint8_t* mem;
};

#ifdef DEBUG_ON
#include <stdio.h>
#define DEBUG(str, ...) printf(str "\n" __VA_OPT__(,) __VA_ARGS__);
#else
#define DEBUG(...)
#endif