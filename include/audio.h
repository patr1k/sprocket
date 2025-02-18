#pragma once

#define AUDIO_NR10      0xFF10
#define AUDIO_NR11      0xFF11
#define AUDIO_NR12      0xFF12
#define AUDIO_NR13      0xFF13
#define AUDIO_NR14      0xFF14
#define AUDIO_NR21      0xFF16
#define AUDIO_NR22      0xFF17
#define AUDIO_NR23      0xFF18
#define AUDIO_NR24      0xFF19
#define AUDIO_NR30      0xFF1A
#define AUDIO_NR31      0xFF1B
#define AUDIO_NR32      0xFF1C
#define AUDIO_NR33      0xFF1D
#define AUDIO_NR34      0xFF1E
#define AUDIO_NR41      0xFF20
#define AUDIO_NR42      0xFF21
#define AUDIO_NR43      0xFF22
#define AUDIO_NR44      0xFF23
#define AUDIO_NR50      0xFF24
#define AUDIO_NR51      0xFF25
#define AUDIO_NR52      0xFF26

#define NR52_AUDIO_ON           0b10000000
#define NR52_CH4_ON             0b00001000
#define NR52_CH3_ON             0b00000100
#define NR52_CH2_ON             0b00000010
#define NR52_CH1_ON             0b00000001

#define NR51_CH4_LEFT           0b10000000
#define NR51_CH3_LEFT           0b01000000
#define NR51_CH2_LEFT           0b00100000
#define NR51_CH1_LEFT           0b00010000
#define NR51_CH4_RIGHT          0b00001000
#define NR51_CH3_RIGHT          0b00000100
#define NR51_CH2_RIGHT          0b00000010
#define NR51_CH1_RIGHT          0b00000001

#define NR50_VIN_LEFT           0b10000000
#define NR50_VOL_LEFT           0b01110000
#define NR50_VIN_RIGHT          0b00001000
#define NR50_VOL_RIGHT          0b00000111

#define NR10_PACE               0b01110000
#define NR10_DIRECTION          0b00001000
#define NR10_STEP               0b00000111

#define NR11_WAVE_DUTY          0b11000000
#define NR11_LENGTH_TIMER       0b00111111
#define WAVE_DUTY_12_5          0x0
#define WAVE_DUTY_25            0x1
#define WAVE_DUTY_50            0x2
#define WAVE_DUTY_75            0x3

#define NR12_VOLUME             0b11110000
#define NR12_ENV_DIR            0b00001000
#define NR12_SWEEP_PACE         0b00000111

#define NR13_PERIOD_LO          0b11111111

#define NR14_TRIGGER            0b10000000
#define NR14_LENGTH_ENABLE      0b01000000
#define NR14_PERIOD_HI          0b00000111

// NR21 same as NR11
// NR22 same as NR12
// NR23 same as NR13
// NR24 same as NR14

#define NR30_DAC_ON             0b10000000

#define NR31_LENGTH_TIMER       0b11111111

#define NR32_OUTPUT_LEVEL       0b01100000
#define OUTPUT_LEVEL_0          0x0
#define OUTPUT_LEVEL_100        0x1
#define OUTPUT_LEVEL_50         0x2
#define OUTPUT_LEVEL_25         0x3

#define NR34_TRIGGER            0b10000000
#define NR34_LENGTH_ENABLE      0b01000000
#define NR34_PERIOD             0b00000111

#define NR41_LENGTH_TIMER       0b00111111

// NR42 is the same as NR12

#define NR43_CLOCK_SHIFT        0b11110000
#define NR43_LFSR_WIDTH         0b00001000
#define NR43_CLOCK_DIVIDER      0b00000111

#define NR44_TRIGGER            0b10000000
#define NR44_LEN_ENABLE         0b01000000