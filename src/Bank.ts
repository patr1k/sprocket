import { Byte } from "./Utils";

class Bank {
  private Size = 16000;
  private Mem: Byte[];

  constructor() {
    this.Reset();
  }

  Reset() {
    this.Mem = [];
    for (let i = 0; i < this.Size; i++) {
      this.Mem[i] = 0x00;
    }
  }
}

export default Bank;