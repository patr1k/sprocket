import RamBank from "./RamBank";

export default class IO extends RamBank {
    constructor() {
        super(0x80);
    }

    /** Joypad */
    static JOYPAD_INPUT = 0x00;

    /** Serial Data Transfer */
    static SERIAL_DATA = 0x01;
    static SERIAL_CTRL = 0x02;

    /** Timer and Divider */
    static DIVIDER = 0x04;
    static TIMA = 0x05;
    static TMA = 0x06;
    static TAC = 0x07;

    /** Sound Channel 1 (Pulse w/ Period Sweep) */
    static NR10 = 0x10; // Sweep
    static NR11 = 0x11; // Length Timer & Duty Cycle
    static NR12 = 0x12; // Volume & Envelope
    static NR13 = 0x13; // Period Low
    static NR14 = 0x14; // Period High & Control

    /** Sound Channel 2 (Pulse) */
    static NR21 = 0x16; // Length Timer & Duty Cycle
    static NR22 = 0x17; // Volume & Envelope
    static NR23 = 0x18; // Period Low
    static NR24 = 0x19; // Period High & Control

    /** Sound Channel 3 (Wave Output) */
    static NR30 = 0x1A; // DAC Enable
    static NR31 = 0x1B; // Length Timer
    static NR32 = 0x1C; // Output Level
    static NR33 = 0x1D; // Period Low
    static NR34 = 0x1E; // Period High & Control
    static WAV = 0x30; // Wave Pattern RAM (16 bytes)

    /** Sound Channel 4 (Noise) */
    static NR41 = 0x20; // Length Timer
    static NR42 = 0x21; // Volume & Envelope
    static NR43 = 0x22; // Frequency & Randomness
    static NR44 = 0x23; // Control

    /** VRAM Bank */
    static VRAM_BANK = 0x4F;

    /** VRAM DMA */
    static HDMA1 = 0x51; // VRAM DMA Source (High)
    static HDMA2 = 0x52; // VRAM DMA Source (Low)
    static HDMA3 = 0x53; // VRAM DMA Destination (High)
    static HDMA4 = 0x54; // VRAM DMA Destination (Low)
    static HDMA5 = 0x55; // VRAM DMA Length/Mode/Start

    /** BOOT ROM Enable/Disable */
    static BOOT_ROM = 0x50;

    /** WRAM Bank */
    static WRAM_BANK = 0x70;
}