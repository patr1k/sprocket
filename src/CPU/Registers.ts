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

    BC(newVal: Word = null): Word {
        if (null === newVal) {
            return (this.C << 8) | this.B;
        } else {
            this.B = newVal & 0xFF;
            this.C = newVal >> 8;
        }
    }

    DE(newVal: Word = null): Word {
        if (null === newVal) {
            return (this.E << 8) | this.D;
        } else {
            this.D = newVal & 0xFF;
            this.E = newVal >> 8;
        }
    }

    HL(newVal: Word = null): Word {
        if (null === newVal) {
            return (this.L << 8) | this.H;
        } else {
            this.H = newVal & 0xFF;
            this.L = newVal >> 8;
        }
    }
}

export default Registers;