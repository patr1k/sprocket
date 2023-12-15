import { TC } from "../Utils";
import CPU from "./CPU";

const CPU_PGM = {
    JR_NZ_REL: (cpu: CPU) => {
        if (!cpu.Flags.Z) {
            cpu.Reg.PC += TC(cpu.FetchByte());
        }
    }
};

export default CPU_PGM;