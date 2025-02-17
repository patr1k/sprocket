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
    union {
        struct {
            uint8_t L;
            uint8_t H;
        } byte;
        uint16_t val;
    } SP;
    union {
        struct {
            uint8_t L;
            uint8_t H;
        } byte;
        uint16_t val;
    } PC;
    union {
        struct {
            uint8_t : 4;
            uint8_t IME : 1;
            uint8_t HALT : 1;
            uint8_t STOP : 1;
            uint8_t LOCKED : 1;
        } flag;
        uint8_t val;
    } mode;
    uint8_t IR;
};

#define MODE_IME    0x8
#define MODE_HALT   0x4
#define MODE_STOP   0x2
#define MODE_LOCKED 0x1

struct gbc
{
    struct cpu_state cpu;
    uint8_t* mem;
};

#define FETCH_BYTE() (dev->mem[dev->cpu.PC.val++])
#define FETCH_WORD() (dev->mem[dev->cpu.PC.val++] | (dev->mem[dev->cpu.PC.val++] << 8))

#define PUSH_BYTE(byte) dev->mem[dev->cpu.SP.val++] = byte
#define PUSH_WORD(word) dev->mem[dev->cpu.SP.val++] = word & 0xFF; dev->mem[dev->cpu.SP.val++] = word >> 8
#define POP_BYTE() dev->mem[--dev->cpu.SP.val]
#define POP_WORD() (dev->mem[--dev->cpu.SP.val] << 8) | dev->mem[--dev->cpu.SP.val]

#define HLMEM dev->mem[dev->cpu.HL.val]

#define CPU_INSTR(name) void cpu_##name(struct gbc *dev)

#define DECOMP_ON 1
// Decompilation logging
#ifdef DECOMP_ON
#include <stdio.h>
#define DECOMP(str, ...) printf(str "\n" __VA_OPT__(,) __VA_ARGS__);
#else
#define DECOMP(...)
#endif

void (*cpu_isa[0x100])(struct gbc *);
void (*cpu_isa_cb[0x100])(struct gbc *);