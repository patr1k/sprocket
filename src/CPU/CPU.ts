import Clock from "../Clock";
import Memory from "../Memory/Memory";
import { Byte, Word } from "../Utils";
import CPU_ALU from "./CPU_ALU";
import CPU_BIT from "./CPU_BIT";
import CPU_MMU from "./CPU_MMU";
import CPU_PGM from "./CPU_PGM";
import Flags from "./Flags";
import Registers from "./Registers";

class CPU {
    Mem: Memory;
    Clk: Clock;
    Reg: Registers;
    Flags: Flags;
    Ticks: number;
    Ins: Byte;
    InsEx: Byte;
    Timer: NodeJS.Timeout;

    constructor(mem: Memory) {
        this.Mem = mem;
        this.Reg = new Registers();
        this.Flags = new Flags(this.Reg);
        this.Ticks = 0;
    }

    Start() {
        this.Timer = setInterval(() => this.Execute(), 500);
    }

    Pause() {
        clearInterval(this.Timer);
    }

    Step() {
        this.Execute();
    }

    FetchOp() {
        this.Ins = this.FetchByte();
    }

    FetchOpEx() {
        this.InsEx = this.FetchByte();
    }

    FetchByte(): Byte {
        return this.Mem.ReadByte(this.Reg.PC++);
    }

    FetchWord(): Word {
        const word = this.Mem.ReadInt(this.Reg.PC, 2);
        this.Reg.PC += 2;
        return word;
    }

    Execute() {
        this.FetchOp();

        console.log(`Ins: ${this.Ins.toString(16)}  PC: ${this.Reg.PC.toString(16)}`)

        switch (this.Ins) {
            case 0x00: /** no op */ break;
            case 0x01: CPU_MMU.LD_BC_IM(this); break;
            case 0x02: CPU_MMU.LD_pBC_A(this); break;
            case 0x03: CPU_ALU.INC_BC(this); break;
            case 0x04: CPU_ALU.INC_B(this); break;
            case 0x05: CPU_ALU.DEC_B(this); break;
            case 0x06: CPU_MMU.LD_B_IM(this); break;
            case 0x07: CPU_ALU.RLCA(this); break;
            case 0x08: CPU_MMU.LD_ABS_SP(this); break;
            case 0x09: CPU_ALU.ADD_HL_BC(this); break;
            case 0x0A: CPU_MMU.LD_A_pBC(this); break;
            case 0x0B: CPU_ALU.DEC_BC(this); break;
            case 0x0C: CPU_ALU.INC_C(this); break;
            case 0x0D: CPU_ALU.DEC_C(this); break;
            case 0x0E: CPU_MMU.LD_C_IM(this); break;
            case 0x0F: CPU_ALU.RRCA(this); break;
            // case 0x10: CPU.STOP(this); break;
            case 0x11: CPU_MMU.LD_DE_IM(this); break;
            case 0x12: CPU_MMU.LD_pDE_A(this); break;
            case 0x13: CPU_ALU.INC_DE(this); break;
            case 0x14: CPU_ALU.INC_D(this); break;
            case 0x15: CPU_ALU.DEC_D(this); break;
            case 0x16: CPU_MMU.LD_D_IM(this); break;
            case 0x17: CPU_ALU.RLA(this); break;
            case 0x18: CPU_PGM.JR_REL(this); break;
            case 0x19: CPU_ALU.ADD_HL_DE(this); break;
            case 0x1A: CPU_MMU.LD_A_pDE(this); break;
            case 0x1B: CPU_ALU.DEC_DE(this); break;
            case 0x1C: CPU_ALU.INC_E(this); break;
            case 0x1D: CPU_ALU.DEC_E(this); break;
            case 0x1E: CPU_MMU.LD_E_IM(this); break;
            case 0x1F: CPU_ALU.RRA(this); break;

            case 0x20: CPU_PGM.JR_NZ_REL(this); break;
            case 0x21: CPU_MMU.LD_HL_IM(this); break;
            case 0x31: CPU_MMU.LD_SP_IM(this); break;
            case 0x32: CPU_MMU.LD_pHLd_A(this); break;
            case 0x3E: CPU_MMU.LD_A_IM(this); break;
            case 0x77: CPU_MMU.LD_pHL_A(this); break;
            case 0xAF: CPU_ALU.XOR_A_A(this); break;
            // ...
            case 0xCB: this.ExecuteEx(); break;
            // ...
            case 0xE2: CPU_MMU.LD_pC_A(this); break;
            case 0xEA: CPU_MMU.LD_ABS_A(this); break;
        }
    }

    ExecuteEx() {
        this.FetchOpEx();

        switch (this.InsEx) {
            case 0x40: CPU_BIT.BIT_0_B(this); break;
            case 0x41: CPU_BIT.BIT_0_C(this); break;
            case 0x42: CPU_BIT.BIT_0_D(this); break;
            case 0x43: CPU_BIT.BIT_0_E(this); break;
            case 0x44: CPU_BIT.BIT_0_H(this); break;
            case 0x45: CPU_BIT.BIT_0_L(this); break;
            case 0x46: CPU_BIT.BIT_0_pHL(this); break;
            case 0x47: CPU_BIT.BIT_0_A(this); break;
            case 0x48: CPU_BIT.BIT_1_B(this); break;
            case 0x49: CPU_BIT.BIT_1_C(this); break;
            case 0x4A: CPU_BIT.BIT_1_D(this); break;
            case 0x4B: CPU_BIT.BIT_1_E(this); break;
            case 0x4C: CPU_BIT.BIT_1_H(this); break;
            case 0x4D: CPU_BIT.BIT_1_L(this); break;
            case 0x4E: CPU_BIT.BIT_1_pHL(this); break;
            case 0x4F: CPU_BIT.BIT_1_A(this); break;

            case 0x50: CPU_BIT.BIT_2_B(this); break;
            case 0x51: CPU_BIT.BIT_2_C(this); break;
            case 0x52: CPU_BIT.BIT_2_D(this); break;
            case 0x53: CPU_BIT.BIT_2_E(this); break;
            case 0x54: CPU_BIT.BIT_2_H(this); break;
            case 0x55: CPU_BIT.BIT_2_L(this); break;
            case 0x56: CPU_BIT.BIT_2_pHL(this); break;
            case 0x57: CPU_BIT.BIT_2_A(this); break;
            case 0x58: CPU_BIT.BIT_3_B(this); break;
            case 0x59: CPU_BIT.BIT_3_C(this); break;
            case 0x5A: CPU_BIT.BIT_3_D(this); break;
            case 0x5B: CPU_BIT.BIT_3_E(this); break;
            case 0x5C: CPU_BIT.BIT_3_H(this); break;
            case 0x5D: CPU_BIT.BIT_3_L(this); break;
            case 0x5E: CPU_BIT.BIT_3_pHL(this); break;
            case 0x5F: CPU_BIT.BIT_3_A(this); break;

            case 0x60: CPU_BIT.BIT_4_B(this); break;
            case 0x61: CPU_BIT.BIT_4_C(this); break;
            case 0x62: CPU_BIT.BIT_4_D(this); break;
            case 0x63: CPU_BIT.BIT_4_E(this); break;
            case 0x64: CPU_BIT.BIT_4_H(this); break;
            case 0x65: CPU_BIT.BIT_4_L(this); break;
            case 0x66: CPU_BIT.BIT_4_pHL(this); break;
            case 0x67: CPU_BIT.BIT_4_A(this); break;
            case 0x68: CPU_BIT.BIT_5_B(this); break;
            case 0x69: CPU_BIT.BIT_5_C(this); break;
            case 0x6A: CPU_BIT.BIT_5_D(this); break;
            case 0x6B: CPU_BIT.BIT_5_E(this); break;
            case 0x6C: CPU_BIT.BIT_5_H(this); break;
            case 0x6D: CPU_BIT.BIT_5_L(this); break;
            case 0x6E: CPU_BIT.BIT_5_pHL(this); break;
            case 0x6F: CPU_BIT.BIT_5_A(this); break;

            case 0x70: CPU_BIT.BIT_6_B(this); break;
            case 0x71: CPU_BIT.BIT_6_C(this); break;
            case 0x72: CPU_BIT.BIT_6_D(this); break;
            case 0x73: CPU_BIT.BIT_6_E(this); break;
            case 0x74: CPU_BIT.BIT_6_H(this); break;
            case 0x75: CPU_BIT.BIT_6_L(this); break;
            case 0x76: CPU_BIT.BIT_6_pHL(this); break;
            case 0x77: CPU_BIT.BIT_6_A(this); break;
            case 0x78: CPU_BIT.BIT_7_B(this); break;
            case 0x79: CPU_BIT.BIT_7_C(this); break;
            case 0x7A: CPU_BIT.BIT_7_D(this); break;
            case 0x7B: CPU_BIT.BIT_7_E(this); break;
            case 0x7C: CPU_BIT.BIT_7_H(this); break;
            case 0x7D: CPU_BIT.BIT_7_L(this); break;
            case 0x7E: CPU_BIT.BIT_7_pHL(this); break;
            case 0x7F: CPU_BIT.BIT_7_A(this); break;
        }
    }
}

export default CPU;