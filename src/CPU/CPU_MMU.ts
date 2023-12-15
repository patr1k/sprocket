import CPU from "./CPU";

const CPU_MMU = {
    LD_BC_IM: (cpu: CPU) => {
        cpu.Reg.BC(cpu.FetchWord());
        cpu.Ticks += 12;
    },
    LD_pBC_A: (cpu: CPU) => {
        cpu.Mem.WriteByte(cpu.Reg.BC(), cpu.Reg.A);
        cpu.Ticks += 8;
    },
    LD_B_IM: (cpu: CPU) => {
        cpu.Reg.B = cpu.FetchByte();
        cpu.Ticks += 8;
    },
    LD_C_IM: (cpu: CPU) => {
        cpu.Reg.C = cpu.FetchByte();
        cpu.Ticks += 8;
    },
    LD_ABS_SP: (cpu: CPU) => {
        cpu.Mem.WriteWord(cpu.FetchWord(), cpu.Reg.SP);
        cpu.Ticks += 20;
    },
    LD_A_pBC: (cpu: CPU) => {
        cpu.Reg.A = cpu.Mem.ReadByte(cpu.Reg.BC());
        cpu.Ticks += 8;
    },


    LD_A_IM: (cpu: CPU) => {
        cpu.Reg.A = cpu.FetchByte();
        cpu.Ticks += 8;
    },

    LD_pC_A: (cpu: CPU) => {
        cpu.Mem.WriteByte(0xFF00 | cpu.Reg.C, cpu.Reg.A);
        cpu.Ticks += 8;
    },

    LD_SP_IM: (cpu: CPU) => {
        cpu.Reg.SP = cpu.FetchWord();
        cpu.Ticks += 12;
    },
    LD_HL_IM: (cpu: CPU) => {
        cpu.Reg.HL(cpu.FetchWord());
        cpu.Ticks += 12;
    },
    LD_pHLd_A: (cpu: CPU) => {
        const addr = cpu.Reg.HL();
        cpu.Mem.WriteByte(addr, cpu.Reg.A);
        cpu.Reg.HL(addr ? addr - 1 : 0xFFFF);
        cpu.Ticks += 8;
    },
};

export default CPU_MMU;