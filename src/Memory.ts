import { Byte, Word } from "./Utils";

class Memory {
    private size: number;
    private mem: Byte[];

    constructor(sizeInBytes: number) {
        this.mem = [];
        for (let i = 0; i < sizeInBytes; i++) {
            this.mem[i] = 0x00;
        }
    }

    Reset() {
        this.mem = [];
        for (let i = 0; i < this.size; i++) {
            this.mem[i] = 0x00;
        }
    }

    LoadRom(data: ArrayBuffer) {
        const bytes = new Uint8Array(data);
        for (let i = 0; i < bytes.byteLength; i++) {
            this.mem[i] = bytes.at(i);
        }
    }

    WriteByte(addr: Word, byte: Byte) {
        this.mem[addr] = byte;
    }

    WriteWord(addr: Word, word: Word) {
        this.mem[addr] = word & 0xFF;
        this.mem[addr + 1] = word >> 8;
    }

    ReadByte(addr: Word): Byte {
        return this.mem[addr];
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

    ReadFloat(addr: number, precision: number = 0): number {
        // this will be fun
        return 0.0;
    }
}

export default Memory;