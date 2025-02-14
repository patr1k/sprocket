#pragma once

#include <stdbool.h>
#include <stdint.h>

enum cpu_flag
{
    FLAG_ZERO = 0x80,
    FLAG_SUBTRACT = 0x40,
    FLAG_HALF_CARRY = 0x20,
    FLAG_CARRY = 0x10
};

enum cpu_flag_cond
{
    NZ = 0,
    Z = 1,
    NC = 2,
    C = 3
};

enum cpu_reg_r8
{
    R8_B  = 0,
    R8_C  = 1,
    R8_D  = 2,
    R8_E  = 3,
    R8_H  = 4,
    R8_L  = 5,
    R8_HL = 6,
    R8_A  = 7,
};

enum cpu_reg_r16
{
    R16_BC  = 0,
    R16_DE  = 1,
    R16_HL  = 2,
    R16_SP  = 3,
};

struct cpu_state
{
    union {
        struct {
            uint8_t F;
            uint8_t A;
        } byte;
        struct {
            uint8_t : 4;
            uint8_t C : 1;
            uint8_t H : 1;
            uint8_t N : 1;
            uint8_t Z : 1;
            uint8_t : 8;
        } flag;
        uint16_t val;
    } AF;
    union {
        struct {
            uint8_t C;
            uint8_t B;
        } byte;
        uint16_t val;
    } BC;
    union {
        struct {
            uint8_t E;
            uint8_t D;
        } byte;
        uint16_t val;
    } DE;
    union {
        struct {
            uint8_t L;
            uint8_t H;
        } byte;
        uint16_t val;
    } HL;
    uint16_t SP;
    uint16_t PC;
};

struct gbc
{
    struct cpu_state cpu;
    uint8_t* mem;
};

uint16_t* cpu_r16_ptr(struct gbc* dev, enum cpu_reg_r16 r16);
uint8_t* cpu_r8_ptr(struct gbc* dev, enum cpu_reg_r8 r8);
uint16_t cpu_r16_val(struct gbc* dev, enum cpu_reg_r16 r16);
uint8_t cpu_r8_val(struct gbc* dev, enum cpu_reg_r8 r8);