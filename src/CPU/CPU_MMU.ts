import CPU from "./CPU";

const CPU_MMU = {
    LD_BC_IM: (cpu: CPU) => {
        cpu.Reg.BC(cpu.FetchWord());
    },
    LD_pBC_A: (cpu: CPU) => {
        cpu.Mem.WriteByte(cpu.Reg.BC(), cpu.Reg.A);
    },
    LD_B_IM: (cpu: CPU) => {
        cpu.Reg.B = cpu.FetchByte();
    },
    LD_C_IM: (cpu: CPU) => {
        cpu.Reg.C = cpu.FetchByte();
    },
    LD_ABS_SP: (cpu: CPU) => {
        const addr = cpu.FetchWord();
        cpu.Mem.WriteWord(addr, cpu.Reg.SP);
    },
    LD_A_pBC: (cpu: CPU) => {
        cpu.Reg.A = cpu.Mem.ReadByte(cpu.Reg.BC());
    },
};

export default CPU_MMU;