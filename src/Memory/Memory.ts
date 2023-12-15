import Bank from "../Bank";
import Cartridge from "../Cartridge/Cartridge";
import BankMode from "./BankMode";
import { Byte, Word } from "../Utils";
import CartridgeInfo from "../Cartridge/CartridgeInfo";
import CartridgeType from "../Cartridge/CartridgeType";
import RamBank from "./RamBank";

class Memory {
    private cart: Cartridge;

    private rom_banks: Bank[];
    private ram_banks: Bank[];

    private wram: RamBank;
    private vram: RamBank;

    private bank_mode: BankMode;

    private boot_rom: number[] = [
        0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32, 0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF, 0x0E,
        0x11, 0x3E, 0x80, 0x32, 0xE2, 0x0C, 0x3E, 0xF3, 0xE2, 0x32, 0x3E, 0x77, 0x77, 0x3E, 0xFC, 0xE0,
        0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1A, 0xCD, 0x95, 0x00, 0xCD, 0x96, 0x00, 0x13, 0x7B,
        0xFE, 0x34, 0x20, 0xF3, 0x11, 0xD8, 0x00, 0x06, 0x08, 0x1A, 0x13, 0x22, 0x23, 0x05, 0x20, 0xF9,
        0x3E, 0x19, 0xEA, 0x10, 0x99, 0x21, 0x2F, 0x99, 0x0E, 0x0C, 0x3D, 0x28, 0x08, 0x32, 0x0D, 0x20,
        0xF9, 0x2E, 0x0F, 0x18, 0xF3, 0x67, 0x3E, 0x64, 0x57, 0xE0, 0x42, 0x3E, 0x91, 0xE0, 0x40, 0x04,
        0x1E, 0x02, 0x0E, 0x0C, 0xF0, 0x44, 0xFE, 0x90, 0x20, 0xFA, 0x0D, 0x20, 0xF7, 0x1D, 0x20, 0xF2,
        0x0E, 0x13, 0x24, 0x7C, 0x1E, 0x83, 0xFE, 0x62, 0x28, 0x06, 0x1E, 0xC1, 0xFE, 0x64, 0x20, 0x06,
        0x7B, 0xE2, 0x0C, 0x3E, 0x87, 0xE2, 0xF0, 0x42, 0x90, 0xE0, 0x42, 0x15, 0x20, 0xD2, 0x05, 0x20,
        0x4F, 0x16, 0x20, 0x18, 0xCB, 0x4F, 0x06, 0x04, 0xC5, 0xCB, 0x11, 0x17, 0xC1, 0xCB, 0x11, 0x17,
        0x05, 0x20, 0xF5, 0x22, 0x23, 0x22, 0x23, 0xC9, 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B,
        0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
        0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC,
        0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E, 0x3C, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x3C,
        0x21, 0x04, 0x01, 0x11, 0xA8, 0x00, 0x1A, 0x13, 0xBE, 0x20, 0xFE, 0x23, 0x7D, 0xFE, 0x34, 0x20,
        0xF5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xFB, 0x86, 0x20, 0xFE, 0x3E, 0x01, 0xE0, 0x50,
    ];

    constructor() {
        this.wram = new RamBank(0x2000);
        this.vram = new RamBank(0x2000);
    }

    Reset() {
        this.wram.Reset();
        this.vram.Reset();
        this.cart = null;
        this.bank_mode = null;
    }

    LoadROM(data: ArrayBuffer): CartridgeInfo {
        this.cart = new Cartridge(data);

        // TODO: Incomplete
        switch (this.cart.Info.CartType) {
            case CartridgeType.MBC1:
            case CartridgeType.MBC1_RAM:
            case CartridgeType.MBC1_RAM_BAT:
                this.bank_mode = BankMode.MBC1;
                break;
            case CartridgeType.MBC2:
            case CartridgeType.MBC2_BAT:
                this.bank_mode = BankMode.MBC2;
                break;
            case CartridgeType.MBC3:
            case CartridgeType.MBC3_RAM:
            case CartridgeType.MBC3_RAM_BAT:
            case CartridgeType.MBC3_TMR_BAT:
            case CartridgeType.MBC3_TMR_RAM_BAT:
                this.bank_mode = BankMode.MBC3;
                break;
            case CartridgeType.HUC1_RAM_BAT:
                this.bank_mode = BankMode.HuC1;
                break;
        }

        return this.cart.Info;
    }

    WriteByte(addr: Word, byte: Byte) {
        switch (true) {
            case (addr < 0x0100): // 0x0000 - 0x00FF
                // Boot ROM

                break;
            case (addr < 0x4000): // 0x0000 - 0x3FFF
                // ROM Access

                break;
            case (addr < 0x8000): // 0x4000 - 0x7FFF
                // Switchable ROM Bank
                break;

            case (addr < 0xA000): // 0x8000 - 0x9FFF
                // Video RAM
                return this.vram.WriteByte(byte, addr);

            case (addr < 0xC000): // 0xA000 - 0xBFFF
                // Switchable RAM Bank
                break;
            case (addr < 0xF000): // 0xC000 - 0xEFFF
                // Internal RAM
                return this.wram.WriteByte(byte, addr);

            case (addr < 0xFE00):
                // Unusable
                break;
            case (addr < 0xFEA0):
                // Sprite Attribs
                break;
            case (addr < 0xFF00):
                // Unusable
                break;
            case (addr < 0xFF4C):
                // I/O
                break;
            case (addr < 0xFF80):
                // Unusable
                break;
            case (addr < 0xFFFF):
                // High RAM
                break;
            case (addr === 0xFFFF):
                // Interrupt Register
                break;
        }

        this.MBC.WriteByte(addr, byte);
        this.mem[addr] = byte;
    }

    WriteWord(addr: Word, word: Word) {
        this.mem[addr] = word & 0xFF;
        this.mem[addr + 1] = word >> 8;
    }

    ReadByte(addr: Word): Byte {
        switch (true) {
            case (addr < 0x0100): // 0x0000 - 0x00FF
                // Boot ROM
                return this.boot_rom[addr];

            case (addr < 0x4000): // 0x0000 - 0x3FFF
                // ROM Access
                return this.cart.ReadByte(addr);

            case (addr < 0x8000): // 0x4000 - 0x7FFF
                // Switchable ROM Bank
                return this.cart.ReadByte(addr);

            case (addr < 0xA000): // 0x8000 - 0x9FFF
                // Video RAM
                return this.vram.ReadByte(addr - 0x8000);

            case (addr < 0xC000): // 0xA000 - 0xBFFF
                // Switchable RAM Bank
                break;

            case (addr < 0xF000): // 0xC000 - 0xEFFF
                // Internal RAM
                break;

            case (addr < 0xFE00):
                console.log('Accessing unusable memory: READ %d', addr);
                return 0x00;

            case (addr < 0xFEA0):
                // Sprite Attribs
                break;

            case (addr < 0xFF00):
                console.log('Accessing unusable memory: READ %d', addr);
                return 0x00;

            case (addr < 0xFF4C):
                // I/O
                break;

            case (addr < 0xFF80):
                // Unusable
                console.log('Accessing unusable memory: READ %d', addr);
                return 0x00;

            case (addr < 0xFFFF):
                // High RAM
                break;
            case (addr === 0xFFFF):
                // Interrupt Register
                break;
        }

        console.log('Address Overflow: READ %d', addr);
        return 0x00;
    }

    ReadWord(addr: number): number {
        return this.mem[addr] | (this.mem[addr + 1] << 8);
    }

    ReadString(addr: number, len: number = 0): string {
        let str = '';
        let offset = 0;

        if (0 === len) {
            while (0x00 !== this.mem[addr + offset]) {
                str += String.fromCharCode(this.mem[addr + offset]);
                offset++;
            }
        } else {
            while (offset < len) {
                str += String.fromCharCode(this.mem[addr + offset]);
                offset++;
            }
        }

        return str;
    }

    ReadInt(addr: number, size: number = 2): number {
        let num = 0;
        for (let i = 0; i < size; i++) {
            num |= (this.mem[addr + i] << (i * 8));
        }
        return num;
    }
}

export default Memory;