import Registers from "./Registers";

class Flags {
    private Reg: Registers;

    constructor(reg: Registers) {
        this.Reg = reg;
    }

    public get Z(): boolean {
        return !!(this.Reg.F & 0b10000000);
    }

    public get N(): boolean {
        return !!(this.Reg.F & 0b01000000);
    }

    public get H(): boolean {
        return !!(this.Reg.F & 0b00100000);
    }

    public get C(): boolean {
        return !!(this.Reg.F & 0b00010000);
    }

    public set Z(val: boolean) {
        this.Reg.F |= val ? 0b10000000 : ~0b10000000;
    }

    public set N(val: boolean) {
        this.Reg.F |= val ? 0b01000000 : ~0b01000000;
    }

    public set H(val: boolean) {
        this.Reg.F |= val ? 0b00100000 : ~0b00100000;
    }

    public set C(val: boolean) {
        this.Reg.F |= val ? 0b00010000 : ~0b00010000;
    }
}

export default Flags;