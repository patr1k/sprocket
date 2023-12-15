import CPU from "./CPU";

const CPU_ALU = {
    INC_BC: (cpu: CPU) => {
        let val = cpu.Reg.BC();
        val = (val === 0xFFFF) ? 0 : val + 1;
        cpu.Reg.BC(val);
        cpu.Ticks += 8;
    },
    DEC_BC: (cpu: CPU) => {
        let val = cpu.Reg.BC();
        val = (val === 0) ? 0xFFFF : val - 1;
        cpu.Reg.BC(val);
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
        cpu.Flags.H = ((cpu.Reg.HL() & 0x0FFF) + (cpu.Reg.BC() & 0x0FFF)) > 0x0FFF;
        const val = cpu.Reg.HL() + cpu.Reg.BC();
        cpu.Flags.C = val > 0xFFFF;
        cpu.Reg.HL(val & 0xFFFF);
        cpu.Flags.N = false;
        cpu.Ticks += 8;
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