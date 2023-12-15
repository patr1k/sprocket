import { Byte } from "../Utils";
import CartridgeInfo from "./CartridgeInfo";
import NewLicensee from "./NewLicensee";
import OldLicensee from "./OldLicensee";

class Cartridge {
  public Info: CartridgeInfo;

  private size: number;
  private data: Byte[];

  constructor(data: ArrayBuffer) {
    // Convert byte stream into array
    const bytes = new Uint8Array(data);

    // Store ROM size
    this.size = bytes.byteLength;

    // Store ROM bytes
    for (let i = 0; i < bytes.byteLength; i++) {
      this.data[i] = bytes.at(i);
    }

    // TODO: Analyze header for validity

    // Parse cartridge header
    this._ParseHeader();
  }

  private _ParseHeader() {
    this.Info = {
      Title: this.ReadString(0x0134),
      ManufacturerCode: this.ReadString(0x013F, 4),
      CGB_Flag: (0xC0 === this.ReadByte(0x0143)),
      SGB_Flag: (0x03 === this.ReadByte(0x0146)),
      CartType: this.ReadByte(0x0147),
      RomSize: this.ReadByte(0x0148),
      RamSize: this.ReadByte(0x0149),
      DestCode: this.ReadByte(0x014A),
      Licensee: (0x33 === this.ReadByte(0x014B)) ? NewLicensee[this.ReadString(0x0144, 2)] : OldLicensee[this.ReadByte(0x014B)],
      RomVersion: this.ReadByte(0x014C),
      HeaderChecksum: this.ReadByte(0x014D),
      GlobalChecksum: this.ReadInt(0x014E, 2)
    };
  }

  public get Size(): number {
    return this.size;
  }

  /** Read Byte */
  ReadByte(addr: number): number {
    return this.data[addr];
  }

  /** Read Word (little endian) */
  ReadWord(addr: number): number {
    return this.data[addr] | (this.data[addr + 1] << 8);
  }

  /** Read String */
  ReadString(addr: number, len: number = 0): string {
    let str = '';
    let offset = 0;

    if (0 === len) {
      while (0x00 !== this.data[addr + offset]) {
        str += String.fromCharCode(this.data[addr + offset]);
        offset++;
      }
    } else {
      while (offset < len) {
        str += String.fromCharCode(this.data[addr + offset]);
        offset++;
      }
    }

    return str;
  }

  /** Read Integer */
  ReadInt(addr: number, size: number = 2): number {
    let num = 0;
    for (let i = 0; i < size; i++) {
      num |= (this.data[addr + i] << (i * 8));
    }
    return num;
  }
}

export default Cartridge;