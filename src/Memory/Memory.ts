import Cartridge from "../Cartridge/Cartridge";
import { Byte, Word } from "../Utils";
import CartridgeInfo from "../Cartridge/CartridgeInfo";
import CartridgeType from "../Cartridge/CartridgeType";
import RamBank from "./RamBank";
import BankRegisters from "./BankRegisters";
import RamSize from "../Cartridge/RamSize";
import IO from "./IO";
import MbcMode from "./MbcMode";
import IRQ from "../CPU/IRQ";

class Memory {
    private cart: Cartridge;

    /** WRAM Banks (8) */
    private wram: RamBank[];

    /** VRAM Banks (2) */
    private vram: RamBank[];

    /** External RAM */
    private xram: RamBank;

    /** High RAM */
    private hram: RamBank;

    /** I/O Memory */
    private io: RamBank;

    /** MBC Bank Registers */
    private bank_reg: BankRegisters = {
        RAM_Enable: false,
        ROM_Bank_Num: 0,
        RAM_Bank_Num: 0,
        Bank_Mode: 0
    };

    private mbc: MbcMode;

    /** Boot ROM */
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
        this.wram = [
            new RamBank(0x1000), // Bank 0
            new RamBank(0x1000), // Bank 1
            new RamBank(0x1000), // Bank 2
            new RamBank(0x1000), // Bank 3
            new RamBank(0x1000), // Bank 4
            new RamBank(0x1000), // Bank 5
            new RamBank(0x1000), // Bank 6
            new RamBank(0x1000), // Bank 7
        ];

        this.vram = [
            new RamBank(0x2000), // Bank 0
            new RamBank(0x2000), // Bank 1
        ];

        this.io = new IO();

        this.hram = new RamBank(0x7F);
    }

    Reset() {
        this.wram.forEach(r => r.Reset());
        this.vram.forEach(r => r.Reset());
        this.io.Reset();
        this.hram.Reset();
        this.cart = null;
        this.mbc = null;
    }

    LoadROM(data: ArrayBuffer): CartridgeInfo {
        this.cart = new Cartridge(data);

        // TODO: Incomplete
        switch (this.cart.Info.CartType) {
            case CartridgeType.MBC1:
            case CartridgeType.MBC1_RAM:
            case CartridgeType.MBC1_RAM_BAT:
                this.mbc = MbcMode.MBC1;
                break;
            case CartridgeType.MBC2:
            case CartridgeType.MBC2_BAT:
                this.mbc = MbcMode.MBC2;
                break;
            case CartridgeType.MBC3:
            case CartridgeType.MBC3_RAM:
            case CartridgeType.MBC3_RAM_BAT:
            case CartridgeType.MBC3_TMR_BAT:
            case CartridgeType.MBC3_TMR_RAM_BAT:
                this.mbc = MbcMode.MBC3;
                break;
            case CartridgeType.HUC1_RAM_BAT:
                this.mbc = MbcMode.HuC1;
                break;
        }

        // Initialize External RAM
        switch (this.cart.Info.RamSize) {
            case RamSize.KB8:
                this.xram = new RamBank(0x2000);
                break;
            case RamSize.KB32:
                this.xram = new RamBank(0x8000);
                break;
            case RamSize.KB64:
                this.xram = new RamBank(0x10000);
                break;
            case RamSize.KB128:
                this.xram = new RamBank(0x20000);
                break;
        }

        return this.cart.Info;
    }

    WriteByte(addr: Word, byte: Byte) {
        // Bank Register Operations
        if (addr < 0x2000) {
            this.bank_reg.RAM_Enable = (byte & 0xF) === 0xA;
            return;
        } else if (addr < 0x4000) {
            this.bank_reg.ROM_Bank_Num = byte & 0b00011111;
            return;
        } else if (addr < 0x6000) {
            this.bank_reg.RAM_Bank_Num = byte & 0b0011;
            return;
        } else if (addr < 0x8000) {
            this.bank_reg.Bank_Mode = byte & 0x1 ? 1 : 0;
            return;
        }

        switch (true) {
            case (addr < 0xA000): // 0x8000 - 0x9FFF
                // Video RAM
                return this.vram[this.io.ReadByte(IO.VRAM_BANK) & 0b0001].WriteByte(addr - 0x8000, byte);

            case (addr < 0xC000): // 0xA000 - 0xBFFF
                // Switchable RAM Bank
                return this.xram.WriteByte(this.bank_reg.Bank_Mode ? ((this.bank_reg.RAM_Bank_Num << 13) | (addr & 0x1FFF)) : (addr & 0x1FFF), byte);

            case (addr < 0xD000): // 0xC000 - 0xCFFF
                // Internal/Work RAM (Bank 0)
                return this.wram[0].WriteByte(addr - 0xC000, byte);

            case (addr < 0xE000): // 0xD000 - 0xDFFF
                // Internal/Work RAM (Bank 1-7)
                return this.wram[this.io.ReadByte(IO.WRAM_BANK) & 0b0111].WriteByte(addr - 0xD000, byte);

            case (addr < 0xFE00): // 0xE000 - 0xFDFF
                // ECHO RAM (Mirror of 0xC000 - 0xDDFF)
                return this.WriteByte(addr - 0x2000, byte);

            case (addr < 0xFEA0): // 0xFE00 - 0xFE9F
                // Object Attribute Memory (Sprite Attributes)
                break;

            case (addr < 0xFF00): // 0xFEA0 - 0xFEFF
                // Unusable
                break;

            case (addr < 0xFF80): // 0xFF00 - 0xFF7F
                // I/O
                this.io.WriteByte(addr - 0xFF00, byte);
                break;

            case (addr < 0xFFFF): // 0xFF80 - 0xFFFE
                // High RAM
                this.hram.WriteByte(addr - 0xFF80, byte);
                break;

            case (addr === 0xFFFF): // 0xFFFF
                // Interrupt Register
                break;
        }
    }

    WriteWord(addr: Word, word: Word) {
        this.WriteByte(addr, word & 0xFF);
        this.WriteByte(addr + 1, word >> 8);
    }

    ReadByte(addr: Word): Byte {
        switch (true) {
            case (addr < 0x0100): // 0x0000 - 0x00FF
                // Boot ROM
                if (0 === this.bank_reg.Bank_Mode) {
                    return this.boot_rom[addr];
                } else {
                    return this.cart.ReadByte((this.bank_reg.RAM_Bank_Num << 19) | addr);
                }

            case (addr < 0x4000): // 0x0000 - 0x3FFF
                // ROM Access
                if (0 === this.bank_reg.Bank_Mode) {
                    return this.cart.ReadByte(addr & 0x3FFF);
                } else {
                    return this.cart.ReadByte((this.bank_reg.RAM_Bank_Num << 19) | (addr & 0x3FFF));
                }

            case (addr < 0x8000): // 0x4000 - 0x7FFF
                // Switchable ROM Bank
                return this.cart.ReadByte((this.bank_reg.RAM_Bank_Num << 19) | (this.bank_reg.ROM_Bank_Num << 14) | addr);

            case (addr < 0xA000): // 0x8000 - 0x9FFF
                // Video RAM
                return this.vram[this.io.ReadByte(IO.VRAM_BANK) & 0b0001].ReadByte(addr - 0x8000);

            case (addr < 0xC000): // 0xA000 - 0xBFFF
                // Switchable External RAM
                if (0 === this.bank_reg.Bank_Mode) {
                    return this.xram.ReadByte(addr & 0x1FFF);
                } else {
                    return this.xram.ReadByte((this.bank_reg.RAM_Bank_Num << 13) | (addr & 0x1FFF));
                }

            case (addr < 0xD000): // 0xC000 - 0xCFFF
                // Internal/Work RAM (Bank 0)
                return this.wram[0].ReadByte(addr - 0xC000);

            case (addr < 0xE000): // 0xD000 - 0xDFFF
                // Internal/Work RAM (Bank 1-7)
                return this.wram[this.io.ReadByte(IO.WRAM_BANK) & 0b0111].ReadByte(addr - 0xD000);

            case (addr < 0xFE00): // 0xE000 - 0xFDFF
                // ECHO RAM
                return this.ReadByte(addr - 0x2000);

            case (addr < 0xFEA0): // 0xFE00 - 0xFE9F
                // Object Attribute Memory (OAM)
                break;

            case (addr < 0xFF00): // 0xFEA0 - 0xFEFF
                console.log('Accessing unusable memory: READ %d', addr);
                return 0x00;

            case (addr < 0xFF80): // 0xFF00 - 0xFF7F
                // I/O
                return this.io.ReadByte(addr - 0x00FF);

            case (addr < 0xFFFF): // 0xFF80 - 0xFFFE
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
        return this.ReadByte(addr) | (this.ReadByte(addr + 1) << 8);
    }

    ReadString(addr: number, len: number = 0): string {
        let str = '';
        let offset = 0;

        if (0 === len) {
            let chr = this.ReadByte(addr + offset);
            while (0x00 !== chr) {
                str += String.fromCharCode(chr);
                offset++;
                chr = this.ReadByte(addr + offset);
            }
        } else {
            while (offset < len) {
                str += String.fromCharCode(this.ReadByte(addr + offset));
                offset++;
            }
        }

        return str;
    }

    ReadInt(addr: number, size: number = 2): number {
        let num = 0;
        for (let i = 0; i < size; i++) {
            num |= (this.ReadByte(addr + i) << (i * 8));
        }
        return num;
    }
}

export default Memory;