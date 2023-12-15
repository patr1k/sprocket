import { TC } from "../Utils";
import CPU from "./CPU";

const CPU_PGM = {
    JR_NZ_REL: (cpu: CPU) => {
        if (!cpu.Flags.Z) {
            cpu.Reg.PC += TC(cpu.FetchByte());
        }
    },
    CALL_ABS: (cpu: CPU) => {
        const addr = cpu.FetchWord();
        cpu.Mem.WriteWord(cpu.Reg.SP, cpu.Reg.PC);
        cpu.Reg.PC = addr;
    },
};

export default CPU_PGM;