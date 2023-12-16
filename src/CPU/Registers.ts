import { Byte, Word } from "../Utils";

class Registers {
    public A: Byte;
    public B: Byte;
    public C: Byte;
    public D: Byte;
    public E: Byte;
    public F: Byte;
    public H: Byte;
    public L: Byte;
    public SP: Word;
    public PC: Word;

    constructor() {
        this.Reset();
    }

    Reset() {
        this.A = 0x00;
        this.B = 0x00;
        this.C = 0x00;
        this.D = 0x00;
        this.E = 0x00;
        this.F = 0x00;
        this.H = 0x00;
        this.L = 0x00;
        this.SP = 0x0000;
        this.PC = 0x0000;
    }

    public get BC(): Word {
        return (this.C << 8) | this.B;
    }

    public set BC(word: Word) {
        this.B = word & 0xFF;
        this.C = word >> 8;
    }

    public get DE(): Word {
        return (this.E << 8) | this.D;
    }

    public set DE(word: Word) {
        this.D = word & 0xFF;
        this.E = word >> 8;
    }

    public get HL(): Word {
        return (this.L << 8) | this.H;
    }

    public set HL(word: Word) {
        this.H = word & 0xFF;
        this.L = word >> 8;
    }
}

export default Registers;