enum CartridgeType {
    ROM_ONLY = 0x00,
    MBC1 = 0x01,
    MBC1_RAM = 0x02,
    MBC1_RAM_BAT = 0x03,
    MBC2 = 0x05,
    MBC2_BAT = 0x06,
    ROM_RAM = 0x08,
    ROM_RAM_BAT = 0x09,
    MMM01 = 0x0B,
    MMM01_RAM = 0x0C,
    MMM01_RAM_BAT = 0x0D,
    MBC3_TMR_BAT = 0x0F,
    MBC3_TMR_RAM_BAT = 0x10,
    MBC3 = 0x11,
    MBC3_RAM = 0x12,
    MBC3_RAM_BAT = 0x13,
    MBC5 = 0x19,
    MBC5_RAM = 0x1A,
    MBC5_RAM_BAT = 0x1B,
    MBC5_RBL = 0x1C,
    MBC5_RBL_RAM = 0x1D,
    MBC5_RBL_RAM_BAT = 0x1E,
    MBC6 = 0x20,
    MBC7_SEN_RBL_RAM_BAT = 0x22,
    POCKET_CAM = 0xFC,
    BANDAI_TAMA5 = 0xFD,
    HUC3 = 0xFE,
    HUC1_RAM_BAT = 0xFF
}

export default CartridgeType;