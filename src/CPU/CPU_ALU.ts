import CPU from "./CPU";

const CPU_ALU = {
    INC_BC: (cpu: CPU) => {
        let val = cpu.Reg.BC();
        val = (val === 0xFFFF) ? 0 : val + 1;
        cpu.Reg.BC(val);
    },
    DEC_BC: (cpu: CPU) => {
        let val = cpu.Reg.BC();
        val = (val === 0) ? 0xFFFF : val - 1;
        cpu.Reg.BC(val);
    },
    INC_B: (cpu: CPU) => {
        let val = cpu.Reg.B;
        val += 1;
        cpu.Flags.H = !!(val & 0b10000);
        cpu.Reg.B = val & 0xFF;
        cpu.Flags.Z = cpu.Reg.B === 0;
        cpu.Flags.N = false;
    },
    DEC_B: (cpu: CPU) => {
        let val = cpu.Reg.B;
        val -= 1;
        cpu.Flags.H = !!(val & 0b100000000);
        cpu.Reg.B = val & 0xFF;
        cpu.Flags.Z = cpu.Reg.B === 0;
        cpu.Flags.N = true;
    },
    INC_C: (cpu: CPU) => {
        let val = cpu.Reg.C;
        val += 1;
        cpu.Flags.H = !!(val & 0b10000);
        cpu.Reg.C = val & 0xFF;
        cpu.Flags.Z = cpu.Reg.C === 0;
        cpu.Flags.N = false;
    },
    DEC_C: (cpu: CPU) => {
        let val = cpu.Reg.C;
        val -= 1;
        cpu.Flags.H = !!(val & 0b100000000);
        cpu.Reg.C = val & 0xFF;
        cpu.Flags.Z = cpu.Reg.C === 0;
        cpu.Flags.N = true;
    },
    RLCA: (cpu: CPU) => {
        let val = cpu.Reg.A;
        val << 1;
        cpu.Flags.C = !!(val & 0b100000000);
        if (cpu.Flags.C) {
            val |= 0b1;
            cpu.Reg.A = val & 0xFF;
        }
        cpu.Flags.Z = false;
        cpu.Flags.N = false;
        cpu.Flags.H = false;
    },
    RRCA: (cpu: CPU) => {
        let val = cpu.Reg.A;
        cpu.Flags.C = !!(val & 0b1);
        val >> 1;
        if (cpu.Flags.C) {
            val |= 0b10000000;
            cpu.Reg.A = val;
        }
        cpu.Flags.Z = false;
        cpu.Flags.N = false;
        cpu.Flags.H = false;
    },
    ADD_HL_BC: (cpu: CPU) => {
        let val = cpu.Reg.HL();
        const preHalf = !!(val & 0b100000000);
        val += cpu.Reg.BC();
        cpu.Reg.HL(val & 0xFFFF);
        cpu.Flags.C = !!(val & 0b10000000000000000);
        cpu.Flags.H = !preHalf && !!(val & 0b100000000);
        cpu.Flags.N = false;
    },
};

export default CPU_ALU;