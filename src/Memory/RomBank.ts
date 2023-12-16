import { Byte, Word } from "../Utils";

class RomBank {
    private size: number = 0x4000;
    private data: Byte[];

    constructor() {
        this.Reset();
    }

    Reset() {
        this.data = [];
        for (let i = 0; i < this.size; i++) {
            this.data[i] = 0x00;
        }
    }

    public get Size(): number {
        return this.size;
    }

    ReadByte(addr: Word): Byte {
        return this.data[addr];
    }

    ReadWord(addr: number): number {
        return this.data[addr] | (this.data[addr + 1] << 8);
    }

    ReadString(addr: number, len: number = 0): string {
        let str = '';
        let offset = 0;

        if (0 === len) {
            while (0x00 !== this.data[addr + offset]) {
                str += String.fromCharCode(this.data[addr + offset]);
                offset++;
            }
        } else {
            while (offset < len) {
                str += String.fromCharCode(this.data[addr + offset]);
                offset++;
            }
        }

        return str;
    }

    ReadInt(addr: number, size: number = 2): number {
        let num = 0;
        for (let i = 0; i < size; i++) {
            num |= (this.data[addr + i] << (i * 8));
        }
        return num;
    }
}

export default RomBank;