enum PPUFlag {
    LCDEnabled = 0b10000000,
    WndTileMapArea = 0b01000000,
    WndEnabled = 0b00100000,
    BgWndTileDataArea = 0b00010000,
    BgTileMapArea = 0b00001000,
    ObjSize = 0b00000100,
    ObjEnabled = 0b00000010,
    BgWndEnabled = 0b00000001,
    BgWndPriority = 0b00000001
};

export default PPUFlag;