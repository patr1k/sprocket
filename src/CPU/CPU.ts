import Clock from "../Clock";
import Memory from "../Memory";
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
    Flags: Flags = {
        Z: false,
        N: false,
        H: false,
        C: false
    };
    Ticks: number;
    Ins: Byte;
    InsEx: Byte;
    BootROM: number[] = [
        0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32, 0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF, 0x0E,
        0x11, 0x3E, 0x80, 0x32, 0xE2, 0x0C, 0x3E, 0xF3, 0xE2, 0x32, 0x3E, 0x77, 0x77, 0x3E, 0xFC, 0xE0,
        0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1A, 0xCD, 0x95, 0x00, 0xCD, 0x96, 0x00, 0x13, 0x7B,
        0xFE, 0x34, 0x20, 0xF3, 0x11, 0xD8, 0x00, 0x06, 0x08, 0x1A, 0x13, 0x22, 0x23, 0x05, 0x20, 0xF9,
        0x3E, 0x19, 0xEA, 0x10, 0x99, 0x21, 0x2F, 0x99, 0x0E, 0x0C, 0x3D, 0x28, 0x08, 0x32, 0x0D, 0x20,
        0xF9, 0x2E, 0x0F, 0x18, 0xF3, 0x67, 0x3E, 0x64, 0x57, 0xE0, 0x42, 0x3E, 0x91, 0xE0, 0x40, 0x04,
        0x1E, 0x02, 0x0E, 0x0C, 0xF0, 0x44, 0xFE, 0x90, 0x20, 0xFA, 0x0D, 0x20, 0xF7, 0x1D, 0x20, 0xF2,
        0x0E, 0x13, 0x24, 0x7C, 0x1E, 0x83, 0xFE, 0x62, 0x28, 0x06, 0x1E, 0xC1, 0xFE, 0x64, 0x20, 0x06,
        0x7B, 0xE2, 0x0C, 0x3E, 0x87, 0xE2, 0xF0, 0x42, 0x90, 0xE0, 0x42, 0x15, 0x20, 0xD2, 0x05, 0x20,
        0x4F, 0x16, 0x20, 0x18, 0xCB, 0x4F, 0x06, 0x04, 0xC5, 0xCB, 0x11, 0x17, 0xC1, 0xCB, 0x11, 0x17,
        0x05, 0x20, 0xF5, 0x22, 0x23, 0x22, 0x23, 0xC9, 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B,
        0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
        0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC,
        0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E, 0x3C, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x3C,
        0x21, 0x04, 0x01, 0x11, 0xA8, 0x00, 0x1A, 0x13, 0xBE, 0x20, 0xFE, 0x23, 0x7D, 0xFE, 0x34, 0x20,
        0xF5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xFB, 0x86, 0x20, 0xFE, 0x3E, 0x01, 0xE0, 0x50,
    ];

    constructor(mem: Memory) {
        this.Mem = mem;
        this.Reg = new Registers();
        this.Ticks = 0;
    }

    Start() {
        // Overwrite the first 0x100 bytes with boot ROM
        const size = this.BootROM.length;
        for (let i = 0; i < size; i++) {
            this.Mem.WriteByte(i, this.BootROM[i]);
        }
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



            case 0x20: CPU_PGM.JR_NZ_REL(this); break;
            case 0x21: CPU_MMU.LD_HL_IM(this); break;
            case 0x31: CPU_MMU.LD_SP_IM(this); break;
            case 0x32: CPU_MMU.LD_pHLd_A(this); break;
            case 0x3E: CPU_MMU.LD_A_IM(this); break;
            case 0xAF: CPU_ALU.XOR_A_A(this); break;

            case 0xCB: this.ExecuteEx(); break;
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