import CPU from "./CPU";

const CPU_BIT = {
    BIT_n_r: (cpu: CPU, bit: number, reg: number) => {
        cpu.Flags.Z = !!(reg & (0x1 << bit));
        cpu.Flags.N = false;
        cpu.Flags.H = true;
        cpu.Ticks += 8;
    },

    BIT_0_B: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 0, cpu.Reg.B),
    BIT_1_B: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 1, cpu.Reg.B),
    BIT_2_B: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 2, cpu.Reg.B),
    BIT_3_B: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 3, cpu.Reg.B),
    BIT_4_B: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 4, cpu.Reg.B),
    BIT_5_B: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 5, cpu.Reg.B),
    BIT_6_B: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 6, cpu.Reg.B),
    BIT_7_B: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 7, cpu.Reg.B),

    BIT_0_C: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 0, cpu.Reg.C),
    BIT_1_C: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 1, cpu.Reg.C),
    BIT_2_C: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 2, cpu.Reg.C),
    BIT_3_C: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 3, cpu.Reg.C),
    BIT_4_C: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 4, cpu.Reg.C),
    BIT_5_C: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 5, cpu.Reg.C),
    BIT_6_C: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 6, cpu.Reg.C),
    BIT_7_C: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 7, cpu.Reg.C),

    BIT_0_D: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 0, cpu.Reg.D),
    BIT_1_D: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 1, cpu.Reg.D),
    BIT_2_D: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 2, cpu.Reg.D),
    BIT_3_D: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 3, cpu.Reg.D),
    BIT_4_D: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 4, cpu.Reg.D),
    BIT_5_D: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 5, cpu.Reg.D),
    BIT_6_D: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 6, cpu.Reg.D),
    BIT_7_D: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 7, cpu.Reg.D),

    BIT_0_E: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 0, cpu.Reg.E),
    BIT_1_E: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 1, cpu.Reg.E),
    BIT_2_E: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 2, cpu.Reg.E),
    BIT_3_E: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 3, cpu.Reg.E),
    BIT_4_E: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 4, cpu.Reg.E),
    BIT_5_E: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 5, cpu.Reg.E),
    BIT_6_E: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 6, cpu.Reg.E),
    BIT_7_E: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 7, cpu.Reg.E),

    BIT_0_H: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 0, cpu.Reg.H),
    BIT_1_H: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 1, cpu.Reg.H),
    BIT_2_H: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 2, cpu.Reg.H),
    BIT_3_H: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 3, cpu.Reg.H),
    BIT_4_H: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 4, cpu.Reg.H),
    BIT_5_H: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 5, cpu.Reg.H),
    BIT_6_H: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 6, cpu.Reg.H),
    BIT_7_H: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 7, cpu.Reg.H),

    BIT_0_L: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 0, cpu.Reg.L),
    BIT_1_L: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 1, cpu.Reg.L),
    BIT_2_L: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 2, cpu.Reg.L),
    BIT_3_L: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 3, cpu.Reg.L),
    BIT_4_L: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 4, cpu.Reg.L),
    BIT_5_L: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 5, cpu.Reg.L),
    BIT_6_L: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 6, cpu.Reg.L),
    BIT_7_L: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 7, cpu.Reg.L),

    BIT_0_pHL: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 0, cpu.Mem.ReadByte(cpu.Reg.HL)),
    BIT_1_pHL: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 1, cpu.Mem.ReadByte(cpu.Reg.HL)),
    BIT_2_pHL: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 2, cpu.Mem.ReadByte(cpu.Reg.HL)),
    BIT_3_pHL: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 3, cpu.Mem.ReadByte(cpu.Reg.HL)),
    BIT_4_pHL: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 4, cpu.Mem.ReadByte(cpu.Reg.HL)),
    BIT_5_pHL: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 5, cpu.Mem.ReadByte(cpu.Reg.HL)),
    BIT_6_pHL: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 6, cpu.Mem.ReadByte(cpu.Reg.HL)),
    BIT_7_pHL: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 7, cpu.Mem.ReadByte(cpu.Reg.HL)),

    BIT_0_A: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 0, cpu.Reg.A),
    BIT_1_A: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 1, cpu.Reg.A),
    BIT_2_A: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 2, cpu.Reg.A),
    BIT_3_A: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 3, cpu.Reg.A),
    BIT_4_A: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 4, cpu.Reg.A),
    BIT_5_A: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 5, cpu.Reg.A),
    BIT_6_A: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 6, cpu.Reg.A),
    BIT_7_A: (cpu: CPU) => CPU_BIT.BIT_n_r(cpu, 7, cpu.Reg.A),
};

export default CPU_BIT;