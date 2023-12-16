import { TC } from "../Utils";
import CPU from "./CPU";

const CPU_PGM = {
    JR_NZ_REL: (cpu: CPU) => {
        if (!cpu.Flags.Z) {
            cpu.Reg.PC += TC(cpu.FetchByte());
            cpu.Ticks += 12;
        } else {
            cpu.Ticks += 8;
        }
    },
    CALL_ABS: (cpu: CPU) => {
        const addr = cpu.FetchWord();
        cpu.Mem.WriteWord(cpu.Reg.SP, cpu.Reg.PC);
        cpu.Reg.PC = addr;
        cpu.Ticks += 24;
    },
    JR_REL: (cpu: CPU) => {
        cpu.Reg.PC += TC(cpu.FetchByte());
        cpu.Ticks += 12;
    },
    JR_Z_REL: (cpu: CPU) => {
        if (cpu.Flags.Z) {
            cpu.Reg.PC += TC(cpu.FetchByte());
            cpu.Ticks += 12;
        } else {
            cpu.Ticks += 8;
        }
    },
};

export default CPU_PGM;