interface BankRegisters {
    RAM_Enable: boolean,
    ROM_Bank_Num: number,
    RAM_Bank_Num: number,
    Bank_Mode: 0 | 1
}

export default BankRegisters;