import RamBank from "./RamBank";

export default class IO extends RamBank {
    constructor() {
        super(0x80);
    }

    /** Joypad */
    static JOYPAD_INPUT = 0xFF00;

    /** Serial Data Transfer */
    static SERIAL_DATA = 0xFF01;
    static SERIAL_CTRL = 0xFF02;

    /** Timer and Divider */
    static DIVIDER = 0xFF04;
    static TIMA = 0xFF05;
    static TMA = 0xFF06;
    static TAC = 0xFF07;

    /** Sound Channel 1 (Pulse w/ Period Sweep) */
    static NR10 = 0xFF10; // Sweep
    static NR11 = 0xFF11; // Length Timer & Duty Cycle
    static NR12 = 0xFF12; // Volume & Envelope
    static NR13 = 0xFF13; // Period Low
    static NR14 = 0xFF14; // Period High & Control

    /** Sound Channel 2 (Pulse) */
    static NR21 = 0xFF16; // Length Timer & Duty Cycle
    static NR22 = 0xFF17; // Volume & Envelope
    static NR23 = 0xFF18; // Period Low
    static NR24 = 0xFF19; // Period High & Control

    /** Sound Channel 3 (Wave Output) */
    static NR30 = 0xFF1A; // DAC Enable
    static NR31 = 0xFF1B; // Length Timer
    static NR32 = 0xFF1C; // Output Level
    static NR33 = 0xFF1D; // Period Low
    static NR34 = 0xFF1E; // Period High & Control
    static WAV = 0xFF30; // Wave Pattern RAM (16 bytes)

    /** Sound Channel 4 (Noise) */
    static NR41 = 0xFF20; // Length Timer
    static NR42 = 0xFF21; // Volume & Envelope
    static NR43 = 0xFF22; // Frequency & Randomness
    static NR44 = 0xFF23; // Control

    /** LCD/PPU Control */
    static LCD_CTRL = 0xFF40;
    static LCD_STAT = 0xFF41;
    static LCD_SCROLL_Y = 0xFF42;
    static LCD_SCROLL_X = 0xFF43;
    static LCD_Y = 0xFF44;
    static LCD_YC = 0xFF45;
    static LCD_DMA = 0xFF46;
    static LCD_BGP = 0xFF47;
    static LCD_OBP0 = 0xFF48;
    static LCD_OBP1 = 0xFF49;
    static LCD_WY = 0xFF4A;
    static LCD_WX = 0xFF4B;

    /** VRAM Bank */
    static VRAM_BANK = 0xFF4F;

    /** VRAM DMA */
    static HDMA1 = 0xFF51; // VRAM DMA Source (High)
    static HDMA2 = 0xFF52; // VRAM DMA Source (Low)
    static HDMA3 = 0xFF53; // VRAM DMA Destination (High)
    static HDMA4 = 0xFF54; // VRAM DMA Destination (Low)
    static HDMA5 = 0xFF55; // VRAM DMA Length/Mode/Start

    /** BOOT ROM Enable/Disable */
    static BOOT_ROM = 0xFF50;

    /** WRAM Bank */
    static WRAM_BANK = 0xFF70;
}