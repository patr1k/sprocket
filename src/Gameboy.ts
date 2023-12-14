import CPU from "./CPU/CPU";
import CartridgeInfo from "./Cartridge/CartridgeInfo";
import CartridgeType from "./Cartridge/CartridgeType";
import NewLicensee from "./Cartridge/NewLicensee";
import OldLicensee from "./Cartridge/OldLicensee";
import RamSize from "./Cartridge/RamSize";
import RomSize from "./Cartridge/RomSize";
import GameboyConfig from "./GameboyConfig";
import Memory from "./Memory";
import PPU from "./PPU/PPU";

class Gameboy {
    public ZoomFactor = 4;
    public readonly Width: number;
    public readonly Height: number;

    private Canvas: HTMLCanvasElement;
    private Ctx: CanvasRenderingContext2D;

    private Mem: Memory;
    private CPU: CPU;
    private PPU: PPU;
    private CartInfo: CartridgeInfo;

    constructor(config: GameboyConfig) {
        this.Width = 160 * this.ZoomFactor;
        this.Height = 144 * this.ZoomFactor;
        this.Canvas = config.canvas;
        this.Canvas.width = this.Width;
        this.Canvas.height = this.Height;
        this.Ctx = this.Canvas.getContext('2d');

        this.Mem = new Memory(8000);
        this.CPU = new CPU(this.Mem);
        this.PPU = new PPU(this.CPU, this.Mem, this.Ctx, config.zoom || 1);
    }

    async StartRom(romFile: File) {
        const buffer = await romFile.arrayBuffer();

        this.Mem.LoadRom(buffer);

        this.ParseHeader();

        this.CPU.Start();
        this.OutputInfo();
    }

    ParseHeader() {
        this.CartInfo = {
            Title: this.Mem.ReadString(0x0134),
            ManufacturerCode: this.Mem.ReadString(0x013F, 4),
            CGB_Flag: (0xC0 === this.Mem.ReadByte(0x0143)),
            SGB_Flag: (0x03 === this.Mem.ReadByte(0x0146)),
            CartType: this.Mem.ReadByte(0x0147),
            RomSize: this.Mem.ReadByte(0x0148),
            RamSize: this.Mem.ReadByte(0x0149),
            DestCode: this.Mem.ReadByte(0x014A),
            Licensee: (0x33 === this.Mem.ReadByte(0x014B)) ? NewLicensee[this.Mem.ReadString(0x0144, 2)] : OldLicensee[this.Mem.ReadByte(0x014B)],
            RomVersion: this.Mem.ReadByte(0x014C),
            HeaderChecksum: this.Mem.ReadByte(0x014D),
            GlobalChecksum: this.Mem.ReadInt(0x014E, 2)
        };
    }

    OutputInfo() {
        console.log('Game Name: %s', this.CartInfo.Title);
        console.log('Developer: %s', this.CartInfo.Licensee);

        let romSize: string;
        switch (this.CartInfo.RomSize) {
            case RomSize.KB32_2:
                romSize = '32KB / 2 Banks';
                break;
            case RomSize.KB64_4:
                romSize = '64KB / 4 Banks';
                break;
            case RomSize.KB128_8:
                romSize = '128KB / 8 Banks';
                break;
            case RomSize.KB256_16:
                romSize = '256KB / 16 Banks';
                break;
            case RomSize.KB512_32:
                romSize = '512KB / 32 Banks';
                break;
            case RomSize.MB1_64:
                romSize = '1MB / 64 Banks';
                break;
            case RomSize.MB2_128:
                romSize = '2MB / 128 Banks';
                break;
            case RomSize.MB4_256:
                romSize = '4MB / 256 Banks';
                break;
            case RomSize.MB8_512:
                romSize = '8MB / 512 Banks';
                break;
            default:
                romSize = 'Unknown';
        }
        console.log('ROM Size: %s', romSize);

        let ramSize: string;
        switch (this.CartInfo.RamSize) {
            case RamSize.NO_RAM:
                ramSize = 'No RAM';
                break;
            case RamSize.UNUSED:
                ramSize = 'Unused';
                break;
            case RamSize.KB8:
                ramSize = '8KB';
                break;
            case RamSize.KB32:
                ramSize = '32KB';
                break;
            case RamSize.KB128:
                ramSize = '128KB';
                break;
            case RamSize.KB64:
                ramSize = '64KB';
                break;
            default:
                ramSize = 'Unknown';
        }
        console.log('RAM Size: %s', ramSize);

        let type: string;
        switch (this.CartInfo.CartType) {
            case CartridgeType.ROM_ONLY:
                type = 'ROM Only';
                break;
            case CartridgeType.MBC1:
                type = 'MBC1';
                break;
            case CartridgeType.MBC1_RAM:
                type = 'MBC1+RAM';
                break;
            case CartridgeType.MBC1_RAM_BAT:
                type = 'MBC1+RAM+Battery';
                break;
            case CartridgeType.MBC2:
                type = 'MBC2';
                break;
            case CartridgeType.MBC2_BAT:
                type = 'MBC2+Battery';
                break;
            case CartridgeType.ROM_RAM:
                type = 'ROM+RAM';
                break;
            case CartridgeType.ROM_RAM_BAT:
                type = 'ROM+RAM+Battery';
                break;
            case CartridgeType.MMM01:
                type = 'MMM01';
                break;
            case CartridgeType.MMM01_RAM:
                type = 'MMM01+RAM';
                break;
            case CartridgeType.MMM01_RAM_BAT:
                type = 'MMM01+RAM+Battery';
                break;
            case CartridgeType.MBC3_TMR_BAT:
                type = 'MBC3+Timer+Battery';
                break;
            case CartridgeType.MBC3_TMR_RAM_BAT:
                type = 'MBC3+Timer+RAM+Battery';
                break;
            case CartridgeType.MBC3:
                type = 'MBC3';
                break;
            case CartridgeType.MBC3_RAM:
                type = 'MBC3+RAM';
                break;
            case CartridgeType.MBC3_RAM_BAT:
                type = 'MBC3+RAM+Battery';
                break;
            case CartridgeType.MBC5:
                type = 'MBC5';
                break;
            case CartridgeType.MBC5_RAM:
                type = 'MBC5+RAM';
                break;
            case CartridgeType.MBC5_RAM_BAT:
                type = 'MBC5+RAM++Battery';
                break;
            case CartridgeType.MBC5_RBL:
                type = 'MBC5+Rumble';
                break;
            case CartridgeType.MBC5_RBL_RAM:
                type = 'MBC5+Rumble+RAM';
                break;
            case CartridgeType.MBC5_RBL_RAM_BAT:
                type = 'MBC5+Rumble+RAM+Battery';
                break;
            case CartridgeType.MBC6:
                type = 'MBC6';
                break;
            case CartridgeType.MBC7_SEN_RBL_RAM_BAT:
                type = 'MBC7+Sensor+Rumble+RAM+Battery';
                break;
            case CartridgeType.POCKET_CAM:
                type = 'Pocket Camera';
                break;
            case CartridgeType.BANDAI_TAMA5:
                type = 'Bandai Tama 5';
                break;
            case CartridgeType.HUC3:
                type = 'HuC3';
                break;
            case CartridgeType.HUC1_RAM_BAT:
                type = 'HuC1+RAM+Battery';
                break;
            default:
                type = 'Unknown';
        }
        console.log('Cartridge Type: %s\n', type);
    }
}

export default Gameboy;