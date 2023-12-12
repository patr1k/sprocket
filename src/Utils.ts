export type Byte = number;
export type Word = Byte;

export const H = (word: Word): Byte => word >> 8;
export const L = (word: Word): Byte => word & 0xF;

export enum Endian {
    BIG,
    LITTLE
}
export const WORD = (low: Byte, high: Byte, endian: Endian = Endian.LITTLE): Word => endian === Endian.LITTLE ? (low << 8) | high : (high << 8) | low;