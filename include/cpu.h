#pragma once

#include <stdbool.h>
#include <stdint.h>

enum cpu_flag
{
    FLAG_ZERO = 1,
    FLAG_SUBTRACT = 2,
    FLAG_HALF_CARRY = 4,
    FLAG_CARRY = 8
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
        uint16_t value;
    } AF;
    union {
        struct {
            uint8_t C;
            uint8_t B;
        } byte;
        uint16_t value;
    } BC;
    union {
        struct {
            uint8_t E;
            uint8_t D;
        } byte;
        uint16_t value;
    } DE;
    union {
        struct {
            uint8_t L;
            uint8_t H;
        } byte;
        uint16_t value;
    } HL;
    uint16_t SP;
    uint16_t PC;
};

void cpu_set_flag(struct cpu_state *cpu, enum cpu_flag flag, bool value);
bool cpu_get_flag(struct cpu_state *cpu, enum cpu_flag flag);

uint16_t* cpu_ptr_r16(struct cpu_state *cpu, enum cpu_reg_r16 r16);
uint8_t* cpu_ptr_r8(struct cpu_state *cpu, enum cpu_reg_r8 r8);
