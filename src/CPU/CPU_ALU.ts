import CPU from "./CPU";

const CPU_ALU = {
    INC_BC: (cpu: CPU) => {
        let val = cpu.Reg.BC;
        val = (val === 0xFFFF) ? 0 : val + 1;
        cpu.Reg.BC = val;
        cpu.Ticks += 8;
    },
    DEC_BC: (cpu: CPU) => {
        let val = cpu.Reg.BC;
        val = (val === 0) ? 0xFFFF : val - 1;
        cpu.Reg.BC = val;
        cpu.Ticks += 8;
    },
    INC_B: (cpu: CPU) => {
        let val = cpu.Reg.B;
        val += 1;
        cpu.Flags.H = (cpu.Reg.B & 0xF) === 0xF;
        cpu.Reg.B = val & 0xFF;
        cpu.Flags.Z = cpu.Reg.B === 0;
        cpu.Flags.N = false;
        cpu.Ticks += 4;
    },
    DEC_B: (cpu: CPU) => {
        let val = cpu.Reg.B;
        val -= 1;
        cpu.Flags.H = (cpu.Reg.B & 0xF) === 0x0;
        cpu.Reg.B = val & 0xFF;
        cpu.Flags.Z = cpu.Reg.B === 0;
        cpu.Flags.N = true;
        cpu.Ticks += 4;
    },
    INC_C: (cpu: CPU) => {
        let val = cpu.Reg.C;
        val += 1;
        cpu.Flags.H = (cpu.Reg.C & 0xF) === 0xF;
        cpu.Reg.C = val & 0xFF;
        cpu.Flags.Z = cpu.Reg.C === 0;
        cpu.Flags.N = false;
        cpu.Ticks += 4;
    },
    DEC_C: (cpu: CPU) => {
        let val = cpu.Reg.C;
        val -= 1;
        cpu.Flags.H = (cpu.Reg.C & 0xF) === 0x0;
        cpu.Reg.C = val & 0xFF;
        cpu.Flags.Z = cpu.Reg.C === 0;
        cpu.Flags.N = true;
        cpu.Ticks += 4;
    },
    RLCA: (cpu: CPU) => {
        cpu.Reg.A = ((cpu.Reg.A >> 7) | cpu.Reg.A << 1) & 0xFF;
        cpu.Flags.C = !!(cpu.Reg.A & 0x01);
        cpu.Flags.Z = false;
        cpu.Flags.N = false;
        cpu.Flags.H = false;
        cpu.Ticks += 4;
    },
    RRCA: (cpu: CPU) => {
        cpu.Reg.A = ((cpu.Reg.A << 7) | cpu.Reg.A >> 1) & 0xFF;
        cpu.Flags.C = !!(cpu.Reg.A & 0x80);
        cpu.Flags.Z = false;
        cpu.Flags.N = false;
        cpu.Flags.H = false;
        cpu.Ticks += 4;
    },
    ADD_HL_BC: (cpu: CPU) => {
        cpu.Flags.H = ((cpu.Reg.HL & 0x0FFF) + (cpu.Reg.BC & 0x0FFF)) > 0x0FFF;
        const val = cpu.Reg.HL + cpu.Reg.BC;
        cpu.Flags.C = val > 0xFFFF;
        cpu.Reg.HL = val & 0xFFFF;
        cpu.Flags.N = false;
        cpu.Ticks += 8;
    },
    INC_DE: (cpu: CPU) => {
        let val = cpu.Reg.DE;
        val = (val === 0xFFFF) ? 0 : val + 1;
        cpu.Reg.DE = val;
        cpu.Ticks += 8;
    },
    INC_D: (cpu: CPU) => {
        let val = cpu.Reg.D;
        val += 1;
        cpu.Flags.H = (cpu.Reg.D & 0xF) === 0xF;
        cpu.Reg.D = val & 0xFF;
        cpu.Flags.Z = cpu.Reg.D === 0;
        cpu.Flags.N = false;
        cpu.Ticks += 4;
    },
    DEC_D: (cpu: CPU) => {
        let val = cpu.Reg.D;
        val -= 1;
        cpu.Flags.H = (cpu.Reg.D & 0xF) === 0x0;
        cpu.Reg.D = val & 0xFF;
        cpu.Flags.Z = cpu.Reg.D === 0;
        cpu.Flags.N = true;
        cpu.Ticks += 4;
    },
    RLA: (cpu: CPU) => {
        cpu.Flags.C = !!(cpu.Reg.A & 0x80);
        cpu.Reg.A = (cpu.Reg.A << 1) & 0xFF;
        cpu.Flags.Z = false;
        cpu.Flags.N = false;
        cpu.Flags.H = false;
        cpu.Ticks += 4;
    },
    ADD_HL_DE: (cpu: CPU) => {
        cpu.Flags.H = ((cpu.Reg.HL & 0x0FFF) + (cpu.Reg.DE & 0x0FFF)) > 0x0FFF;
        const val = cpu.Reg.HL + cpu.Reg.DE;
        cpu.Flags.C = val > 0xFFFF;
        cpu.Reg.HL = val & 0xFFFF;
        cpu.Flags.N = false;
        cpu.Ticks += 8;
    },
    DEC_DE: (cpu: CPU) => {
        let val = cpu.Reg.DE;
        val = (val === 0) ? 0xFFFF : val - 1;
        cpu.Reg.DE = val;
        cpu.Ticks += 8;
    },
    INC_E: (cpu: CPU) => {
        let val = cpu.Reg.E;
        val += 1;
        cpu.Flags.H = (cpu.Reg.E & 0xF) === 0xF;
        cpu.Reg.E = val & 0xFF;
        cpu.Flags.Z = cpu.Reg.E === 0;
        cpu.Flags.N = false;
        cpu.Ticks += 4;
    },
    DEC_E: (cpu: CPU) => {
        let val = cpu.Reg.E;
        val -= 1;
        cpu.Flags.H = (cpu.Reg.E & 0xF) === 0x0;
        cpu.Reg.E = val & 0xFF;
        cpu.Flags.Z = cpu.Reg.E === 0;
        cpu.Flags.N = true;
        cpu.Ticks += 4;
    },
    RRA: (cpu: CPU) => {
        cpu.Flags.C = !!(cpu.Reg.A & 0x01);
        cpu.Reg.A = (cpu.Reg.A >> 1) & 0xFF;
        cpu.Flags.Z = false;
        cpu.Flags.N = false;
        cpu.Flags.H = false;
        cpu.Ticks += 4;
    },
    INC_HL: (cpu: CPU) => {
        let val = cpu.Reg.HL;
        val = (val === 0xFFFF) ? 0 : val + 1;
        cpu.Reg.HL = val;
        cpu.Ticks += 8;
    },
    INC_H: (cpu: CPU) => {
        let val = cpu.Reg.H;
        val += 1;
        cpu.Flags.H = (cpu.Reg.H & 0xF) === 0xF;
        cpu.Reg.H = val & 0xFF;
        cpu.Flags.Z = cpu.Reg.H === 0;
        cpu.Flags.N = false;
        cpu.Ticks += 4;
    },
    DEC_H: (cpu: CPU) => {
        let val = cpu.Reg.H;
        val -= 1;
        cpu.Flags.H = (cpu.Reg.H & 0xF) === 0x0;
        cpu.Reg.H = val & 0xFF;
        cpu.Flags.Z = cpu.Reg.H === 0;
        cpu.Flags.N = true;
        cpu.Ticks += 4;
    },
    DAA: (cpu: CPU) => {
        if (!cpu.Flags.N) {
            if (cpu.Flags.C || cpu.Reg.A > 0x99) {
                cpu.Reg.A += 0x60;
                cpu.Flags.C = true;
            }
            if (cpu.Flags.H || ((cpu.Reg.A & 0xF) > 0x9)) {
                cpu.Reg.A += 0x6;
            }
        } else {
            if (cpu.Flags.C) {
                cpu.Reg.A -= 0x60;
            }
            if (cpu.Flags.H) {
                cpu.Reg.A -= 0x6;
            }
        }
        cpu.Flags.Z = cpu.Reg.A === 0;
        cpu.Flags.H = false;
        cpu.Ticks += 4;
    },
    ADD_HL_HL: (cpu: CPU) => {
        cpu.Flags.H = ((cpu.Reg.HL & 0x0FFF) + (cpu.Reg.HL & 0x0FFF)) > 0x0FFF;
        const val = cpu.Reg.HL + cpu.Reg.HL;
        cpu.Flags.C = val > 0xFFFF;
        cpu.Reg.HL = val & 0xFFFF;
        cpu.Flags.N = false;
        cpu.Ticks += 8;
    },
    DEC_HL: (cpu: CPU) => {
        let val = cpu.Reg.HL;
        val = (val === 0) ? 0xFFFF : val - 1;
        cpu.Reg.HL = val;
        cpu.Ticks += 8;
    },
    INC_L: (cpu: CPU) => {
        let val = cpu.Reg.L;
        val += 1;
        cpu.Flags.H = (cpu.Reg.L & 0xF) === 0xF;
        cpu.Reg.L = val & 0xFF;
        cpu.Flags.Z = cpu.Reg.L === 0;
        cpu.Flags.N = false;
        cpu.Ticks += 4;
    },
    DEC_L: (cpu: CPU) => {
        let val = cpu.Reg.L;
        val -= 1;
        cpu.Flags.H = (cpu.Reg.L & 0xF) === 0x0;
        cpu.Reg.L = val & 0xFF;
        cpu.Flags.Z = cpu.Reg.L === 0;
        cpu.Flags.N = true;
        cpu.Ticks += 4;
    },
    CPL: (cpu: CPU) => {
        cpu.Reg.A = ~cpu.Reg.A;
        cpu.Flags.N = true;
        cpu.Flags.H = true;
        cpu.Ticks += 4;
    },

    XOR_A_A: (cpu: CPU) => {
        cpu.Reg.A = 0;
        cpu.Flags.Z = true;
        cpu.Flags.N = false;
        cpu.Flags.N = false;
        cpu.Flags.N = false;
        cpu.Ticks += 4;
    },
};

export default CPU_ALU;