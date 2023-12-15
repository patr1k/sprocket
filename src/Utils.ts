export type Byte = number;
export type Word = Byte;

export const H = (word: Word): Byte => word >> 8;
export const L = (word: Word): Byte => word & 0xF;

export enum Endian {
    BIG,
    LITTLE
}
export const WORD = (low: Byte, high: Byte, endian: Endian = Endian.LITTLE): Word => endian === Endian.LITTLE ? (low << 8) | high : (high << 8) | low;

export const TC = (byte: Byte): Byte => {
    if (!(byte & 0x80)) {
        return byte;
    }

    let val = -128;
    for (let i = 0; i < 7; i++) {
        val += (byte & (0x1 << i)) * (2 ** i);
    }
    return val;
};