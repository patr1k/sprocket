import CPU from '../src/CPU/CPU';
import Instruction from '../src/CPU/Instruction';
import Memory from '../src/Memory';

type InstructionArg = ['BYTE' | 'WORD', number];

describe('testing CPU', () => {
    const mem = new Memory(0x8000);
    const cpu = new CPU(mem);

    const prepIns = (ins: Instruction, ...args: InstructionArg[]) => {
        cpu.Reg.PC = 0x00;
        cpu.Mem.WriteByte(0x00, ins);
        let addr = 0x01;
        args.forEach(([type, val]) => {
            if (type === 'BYTE') {
                cpu.Mem.WriteByte(addr, val);
                addr += 1;
            } else {
                cpu.Mem.WriteWord(addr, val);
                addr += 2;
            }
        });
        cpu.Mem.WriteByte(addr, Instruction.HALT);
    };

    test('LD_BC_IM', () => {
        cpu.Reg.Reset();
        prepIns(Instruction.LD_BC_IM, ['WORD', 0x1234]);
        cpu.Execute();
        expect(cpu.Reg.BC()).toBe(0x1234);
    });

    test('LD_pBC_A', () => {
        cpu.Reg.Reset();
        cpu.Reg.A = 0xAB;
        cpu.Reg.BC(0x1234);
        prepIns(Instruction.LD_pBC_A);
        cpu.Execute();
        expect(cpu.Mem.ReadByte(0x1234)).toBe(0xAB);
    });

    test('INC_BC', () => {
        cpu.Reg.Reset();
        cpu.Reg.BC(0x1234);
        prepIns(Instruction.INC_BC);
        cpu.Execute();
        expect(cpu.Reg.BC()).toBe(0x1235);
    });

    test('INC_B', () => {
        cpu.Reg.Reset();
        cpu.Reg.B = 0x01;
        prepIns(Instruction.INC_B);
        cpu.Execute();
        expect(cpu.Reg.B).toBe(0x02);
        expect(cpu.Flags.N).toBe(false);
        expect(cpu.Flags.Z).toBe(false);
        expect(cpu.Flags.H).toBe(false);

        cpu.Reg.Reset();
        cpu.Reg.B = 0x0F;
        prepIns(Instruction.INC_B);
        cpu.Execute();
        expect(cpu.Reg.B).toBe(0x10);
        expect(cpu.Flags.N).toBe(false);
        expect(cpu.Flags.Z).toBe(false);
        expect(cpu.Flags.H).toBe(true);

        cpu.Reg.Reset();
        cpu.Reg.B = 0xFF;
        prepIns(Instruction.INC_B);
        cpu.Execute();
        expect(cpu.Reg.B).toBe(0x00);
        expect(cpu.Flags.N).toBe(false);
        expect(cpu.Flags.Z).toBe(true);
        expect(cpu.Flags.H).toBe(true);
    });

    test('DEC_B', () => {
        cpu.Reg.Reset();
        cpu.Reg.B = 0x02;
        prepIns(Instruction.DEC_B);
        cpu.Execute();
        expect(cpu.Reg.B).toBe(0x01);
        expect(cpu.Flags.N).toBe(true);
        expect(cpu.Flags.Z).toBe(false);
        expect(cpu.Flags.H).toBe(false);

        cpu.Reg.Reset();
        cpu.Reg.B = 0x10;
        prepIns(Instruction.DEC_B);
        cpu.Execute();
        expect(cpu.Reg.B).toBe(0x0F);
        expect(cpu.Flags.N).toBe(true);
        expect(cpu.Flags.Z).toBe(false);
        expect(cpu.Flags.H).toBe(true);

        cpu.Reg.Reset();
        cpu.Reg.B = 0x01;
        prepIns(Instruction.DEC_B);
        cpu.Execute();
        expect(cpu.Reg.B).toBe(0x00);
        expect(cpu.Flags.N).toBe(true);
        expect(cpu.Flags.Z).toBe(true);
        expect(cpu.Flags.H).toBe(false);
    });

    test('LD_B_IM', () => {
        cpu.Reg.Reset();
        prepIns(Instruction.LD_B_IM, ['BYTE', 0xAB]);
        cpu.Execute();
        expect(cpu.Reg.B).toBe(0xAB);
    });

    test('RLCA', () => {
        cpu.Reg.Reset();
        cpu.Reg.A = 0b11110000;
        prepIns(Instruction.RLCA);
        cpu.Execute();
        expect(cpu.Reg.A).toBe(0b11100001);
        expect(cpu.Flags.C).toBe(true);

        cpu.Reg.Reset();
        cpu.Reg.A = 0b01110001;
        prepIns(Instruction.RLCA);
        cpu.Execute();
        expect(cpu.Reg.A).toBe(0b11100010);
        expect(cpu.Flags.C).toBe(false);
    });

    test('LD_ABS_SP', () => {
        cpu.Reg.Reset();
        cpu.Reg.SP = 0xABCD;
        prepIns(Instruction.LD_ABS_SP, ['WORD', 0x1234]);
        cpu.Execute();
        expect(cpu.Mem.ReadWord(0x1234)).toBe(0xABCD);
    });

    test('ADD_HL_BC', () => {
        cpu.Reg.Reset();
        cpu.Reg.HL(0x000F);
        cpu.Reg.BC(0x000F);
        prepIns(Instruction.ADD_HL_BC);
        cpu.Execute();
        expect(cpu.Reg.HL()).toBe(0x001E);
        expect(cpu.Flags.N).toBe(false);
        expect(cpu.Flags.H).toBe(false);
        expect(cpu.Flags.C).toBe(false);

        cpu.Reg.Reset();
        cpu.Reg.HL(0x0800);
        cpu.Reg.BC(0x0800);
        prepIns(Instruction.ADD_HL_BC);
        cpu.Execute();
        expect(cpu.Reg.HL()).toBe(0x1000);
        expect(cpu.Flags.N).toBe(false);
        expect(cpu.Flags.H).toBe(true);
        expect(cpu.Flags.C).toBe(false);

        cpu.Reg.Reset();
        cpu.Reg.HL(0x8000);
        cpu.Reg.BC(0x8000);
        prepIns(Instruction.ADD_HL_BC);
        cpu.Execute();
        expect(cpu.Reg.HL()).toBe(0x0000);
        expect(cpu.Flags.N).toBe(false);
        expect(cpu.Flags.H).toBe(false);
        expect(cpu.Flags.C).toBe(true);
    });

    test('LD_A_pBC', () => {
        cpu.Reg.Reset();
        cpu.Reg.BC(0x1234);
        cpu.Mem.WriteByte(0x1234, 0xAB);
        prepIns(Instruction.LD_A_pBC);
        cpu.Execute();
        expect(cpu.Reg.A).toBe(0xAB);
    });

    test('DEC_BC', () => {
        cpu.Reg.Reset();
        cpu.Reg.BC(0x1234);
        prepIns(Instruction.DEC_BC);
        cpu.Execute();
        expect(cpu.Reg.BC()).toBe(0x1233);
    });

    test('INC_C', () => {
        cpu.Reg.Reset();
        cpu.Reg.C = 0x01;
        prepIns(Instruction.INC_C);
        cpu.Execute();
        expect(cpu.Reg.C).toBe(0x02);
        expect(cpu.Flags.N).toBe(false);
        expect(cpu.Flags.Z).toBe(false);
        expect(cpu.Flags.H).toBe(false);

        cpu.Reg.Reset();
        cpu.Reg.C = 0x0F;
        prepIns(Instruction.INC_C);
        cpu.Execute();
        expect(cpu.Reg.C).toBe(0x10);
        expect(cpu.Flags.N).toBe(false);
        expect(cpu.Flags.Z).toBe(false);
        expect(cpu.Flags.H).toBe(true);

        cpu.Reg.Reset();
        cpu.Reg.C = 0xFF;
        prepIns(Instruction.INC_C);
        cpu.Execute();
        expect(cpu.Reg.C).toBe(0x00);
        expect(cpu.Flags.N).toBe(false);
        expect(cpu.Flags.Z).toBe(true);
        expect(cpu.Flags.H).toBe(true);
    });

    test('DEC_C', () => {
        cpu.Reg.Reset();
        cpu.Reg.C = 0x02;
        prepIns(Instruction.DEC_C);
        cpu.Execute();
        expect(cpu.Reg.C).toBe(0x01);
        expect(cpu.Flags.N).toBe(true);
        expect(cpu.Flags.Z).toBe(false);
        expect(cpu.Flags.H).toBe(false);

        cpu.Reg.Reset();
        cpu.Reg.C = 0x10;
        prepIns(Instruction.DEC_C);
        cpu.Execute();
        expect(cpu.Reg.C).toBe(0x0F);
        expect(cpu.Flags.N).toBe(true);
        expect(cpu.Flags.Z).toBe(false);
        expect(cpu.Flags.H).toBe(true);

        cpu.Reg.Reset();
        cpu.Reg.C = 0x01;
        prepIns(Instruction.DEC_C);
        cpu.Execute();
        expect(cpu.Reg.C).toBe(0x00);
        expect(cpu.Flags.N).toBe(true);
        expect(cpu.Flags.Z).toBe(true);
        expect(cpu.Flags.H).toBe(false);
    });

    test('LD_C_IM', () => {
        cpu.Reg.Reset();
        prepIns(Instruction.LD_C_IM, ['BYTE', 0xAB]);
        cpu.Execute();
        expect(cpu.Reg.C).toBe(0xAB);
    });

    test('RRCA', () => {
        cpu.Reg.Reset();
        cpu.Reg.A = 0b11110000;
        prepIns(Instruction.RRCA);
        cpu.Execute();
        expect(cpu.Reg.A).toBe(0b01111000);
        expect(cpu.Flags.C).toBe(false);

        cpu.Reg.Reset();
        cpu.Reg.A = 0b01110001;
        prepIns(Instruction.RRCA);
        cpu.Execute();
        expect(cpu.Reg.A).toBe(0b10111000);
        expect(cpu.Flags.C).toBe(true);
    });
});