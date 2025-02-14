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
    COND_NZ = 0,
    COND_Z = 1,
    COND_NC = 2,
    COND_C = 3
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

#define FLAG_NAME(n) \
    ((n) == 0x80 ? "Z" : \
     (n) == 0x40 ? "N" : \
     (n) == 0x20 ? "H" : \
     (n) == 0x10 ? "C" : "")

#define COND_NAME(n) \
    ((n) == 0 ? "NZ" : \
     (n) == 1 ? "Z" : \
     (n) == 2 ? "NC" : \
     (n) == 3 ? "C" : "")

#define R8_NAME(n) \
    ((n) == 0 ? "B" : \
     (n) == 1 ? "C" : \
     (n) == 2 ? "D" : \
     (n) == 3 ? "E" : \
     (n) == 4 ? "H" : \
     (n) == 5 ? "L" : \
     (n) == 6 ? "[HL]" : \
     (n) == 7 ? "A" : "")

#define R16_NAME(n) \
    ((n) == 0 ? "BC" : \
     (n) == 1 ? "DE" : \
     (n) == 2 ? "HL" : \
     (n) == 3 ? "SP" : "")

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