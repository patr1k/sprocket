enum Instruction {
    NOP = 0x00,
    LD_BC_IM = 0x01,
    LD_pBC_A = 0x02,
    INC_BC = 0x03,
    INC_B = 0x04,
    DEC_B = 0x05,
    LD_B_IM = 0x06,
    RLCA = 0x07,
    LD_ABS_SP = 0x08,
    ADD_HL_BC = 0x09,
    LD_A_pBC = 0x0A,
    DEC_BC = 0x0B,
    INC_C = 0x0C,
    DEC_C = 0x0D,
    LD_C_IM = 0x0E,
    RRCA = 0x0F,
    STOP = 0x10,



    HALT = 0x76,
}

export default Instruction;