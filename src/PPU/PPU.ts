import CPU from "../CPU/CPU";
import PPUFlag from "./PPUFlag";
import Memory from "../Memory/Memory";
import RenderMode from "./RenderMode";
import IO from "../Memory/IO";
import { Byte, TC } from "../Utils";
import PPUMode from "./PPUMode";
import StatusIRQ from "./StatusIRQ";
import IRQ from "../CPU/IRQ";

class PPU {
    Mem: Memory;
    CPU: CPU;
    LCD: CanvasRenderingContext2D;

    Run: boolean = true;
    DrawLoop: NodeJS.Timeout;

    Zoom: number;
    ZoomWidth: number;
    ZoomHeight: number;

    private static Width: number = 160;
    private static Height: number = 144;

    LX: number = 0;
    LY: number = 0;

    Ticks: number = 0;

    OriginX: number = 0;
    OriginY: number = 0;

    private FrameBuffer: number[][];

    static MEM_VRAM_TILES = 0x8000;
    static MEM_VRAM_TILES_B1 = 0x8800;
    static MEM_VRAM_TILES_B2 = 0x9000;

    static MEM_VRAM_MAP1 = 0x9800;
    static MEM_VRAM_MAP2 = 0x9C00;

    static COLOR1 = 0x0000;
    static COLOR2 = 0x4BC4;
    static COLOR3 = 0x968B;
    static COLOR4 = 0xFFFF;

    constructor(cpu: CPU, mem: Memory, ctx: CanvasRenderingContext2D, zoom: number = 1) {
        this.CPU = cpu;
        this.Mem = mem;
        this.LCD = ctx;

        this.Zoom = zoom;
        this.ZoomWidth = PPU.Width * zoom;
        this.ZoomHeight = PPU.Height * zoom;

        this.FrameBuffer = [[], []];
        for (let f = 0; f < 2; f++) {
            for (let i = 0; i < 160 * 144; i++) {
                this.FrameBuffer[f][i] = 0x0;
            }
        }

        this.LCD.fillStyle = '#000000';
        this.LCD.fillRect(0, 0, this.ZoomWidth, this.ZoomHeight);

        // setTimeout(() => this.Draw(Date.now()), 16);
    }

    Draw(time: number) {
        if (this.LX < 455) {
            this.LX++;
        } else {
            this.LX = 0;
            if (this.LY < 153) {
                this.LY++;
            } else {
                this.LY = 0;
            }
        }

        if (this.LY >= 144) {
            this.Mode = PPUMode.V_Blank;
        } else {
            if (this.LX < 80) {
                this.Mode = PPUMode.OAM_Scan;
            } else if (this.LX < 144) {
                this.Mode = PPUMode.Drawing;
            } else {
                this.Mode = PPUMode.H_Blank;
            }
        }

        setTimeout(() => this.Draw(Date.now()), 16);
    }

    Step() {
        let Y = this.Mem.ReadByte(IO.LCD_Y) % 152;
        let sendingFrame = 1;
        let calcFrame = 0;

        while (this.Ticks < this.CPU.Ticks) {
            this.Ticks++;
            const cycleTicks = this.Ticks % 114;

            switch (cycleTicks) {
                case 0: // reading from OAM
                    this.Mode = PPUMode.OAM_Scan;
                    if (this.STAT & StatusIRQ.Mode2) {
                        this.CPU.Interrupt(IRQ.LCD_STAT);
                    }
                    break;
                case 20: // reading from both OAM and VRAM
                    this.Mode = PPUMode.Drawing;
                    if (Y === this.Mem.ReadByte(IO.LCD_YC)) {
                        this.LYC = true;
                        if (this.STAT & StatusIRQ.LYC) {
                            this.CPU.Interrupt(IRQ.LCD_STAT);
                        }
                    } else {
                        this.LYC = false;
                    }
                    break;
                case 43:
                    if (this.LCDEnabled) {
                        Y = (Y + 1) % 152;
                        this.Mem.WriteByte(IO.LCD_Y, Y);
                        this.OriginX = this.Mem.ReadByte(IO.LCD_SCROLL_X);
                        this.OriginY = this.Mem.ReadByte(IO.LCD_SCROLL_Y);
                        if (Y < 144) {
                            if (this.BgWndEnabled) {
                                this.GetBackgroundForLine(Y, calcFrame);
                            }
                            if (this.ObjEnabled) {
                                this.GetSpritesForLine(Y, calcFrame);
                            }
                            this.Mode = PPUMode.H_Blank;
                            if (this.STAT & StatusIRQ.Mode0) {
                                this.CPU.Interrupt(IRQ.LCD_STAT);
                            }
                        } else if (Y === 144) {
                            this.Mode = PPUMode.V_Blank;
                            this.CPU.Interrupt(IRQ.LCD_VBLANK);
                            this.MapColorsForFrame(calcFrame);

                            sendingFrame = calcFrame;
                            calcFrame = calcFrame ? 0 : 1;

                            let pixel = 0;
                            for (let dy = 0; dy < 144; dy += this.Zoom) {
                                for (let dx = 0; dx < 160; dx += this.Zoom) {
                                    switch (this.FrameBuffer[sendingFrame][pixel]) {
                                        case PPU.COLOR1: this.LCD.fillStyle = '#000000'; break;
                                        case PPU.COLOR2: this.LCD.fillStyle = '#444444'; break;
                                        case PPU.COLOR3: this.LCD.fillStyle = '#888888'; break;
                                        case PPU.COLOR4: this.LCD.fillStyle = '#BBBBBB'; break;
                                    }
                                    this.LCD.fillRect(dx, dy, this.Zoom, this.Zoom);
                                    pixel++;
                                }
                            }
                        } else {
                            this.Mode = PPUMode.V_Blank;
                        }
                    }
                    break;
            }
        }
    }

    GetBackgroundForLine(y: Byte, frame: number) {
        const offset = y * 160;
        for (let i = offset; i < offset + 320; i++) {
            this.FrameBuffer[frame][i] = 0x33;
        }
        let tileIndex, tileLineU, tileLineL;
        let signedTileIndex;

        let tilePosY = Math.floor(y / 8) * 8;
        let tileLineY = y - tilePosY;

        const bgTileMap = this.BgTileMapArea ? PPU.MEM_VRAM_MAP2 : PPU.MEM_VRAM_MAP1;

        let baseTilePtr: number;
        let convertTileIndex: boolean;
        if (this.BgWndTileDataArea) {
            baseTilePtr = PPU.MEM_VRAM_TILES;
            convertTileIndex = false;
        } else {
            baseTilePtr = PPU.MEM_VRAM_TILES_B2;
            convertTileIndex = true;
        }

        for (let i = 0; i < 20; i++) {
            tileIndex = this.CPU.Mem.ReadByte(bgTileMap + i + 32 * (tilePosY / 8));
            if (convertTileIndex) {
                signedTileIndex = TC(tileIndex);
                const offset = baseTilePtr + signedTileIndex * 16 + tileLineY * 2;
                tileLineL = this.CPU.Mem.ReadByte(offset);
                tileLineU = this.CPU.Mem.ReadByte(offset + 1);
            } else {
                const offset = baseTilePtr + tileIndex * 16 + tileLineY * 2;
                tileLineL = this.CPU.Mem.ReadByte(offset);
                tileLineU = this.CPU.Mem.ReadByte(offset + 1);
            }
            for (let c = 0; c < 8; c++) {
                this.FrameBuffer[frame][y * 160 + i * 8 + c] = (((tileLineU >> (7 - c)) << 1) & 0x2) | ((tileLineL >> (7 - c)) & 0x1);
            }
        }
    }

    GetSpritesForLine(y: number, frame: number) {
        let spritePosX: number, spritePosY: number;
        let tileIndex: number, attribs: number, tileLineU: number, tileLineL: number, pixel: number;
        let spriteLineY: number, x: number;

        for (let i = 0xFE00; i < 0xFEA0; i += 4) {
            spritePosY = this.CPU.Mem.ReadByte(i) - 16;
            spriteLineY = y - spritePosY;
            if (spriteLineY >= 0 && spriteLineY < 8) {
                spritePosX = this.CPU.Mem.ReadByte(i + 1) - 8;
                tileIndex = this.CPU.Mem.ReadByte(i + 2);
                attribs = this.CPU.Mem.ReadByte(i + 3);

                const offset = PPU.MEM_VRAM_TILES + tileIndex * 16 + spriteLineY * 2;
                tileLineL = this.CPU.Mem.ReadByte(offset);
                tileLineU = this.CPU.Mem.ReadByte(offset + 1);

                for (let c = 0; c < 8; c++) {
                    x = spritePosX + c;
                    if (x >= 0) {
                        if ((attribs & 0x80) == 0 || this.FrameBuffer[frame][y * 160 + x] == 0) {
                            pixel = (((tileLineU >> (7 - c)) << 1) & 0x2) | ((tileLineL >> (7 - c)) & 0x1);
                            if (pixel != 0) this.FrameBuffer[frame][y * 160 + x] = pixel;
                        }
                    }
                }
            }
        }
    }

    MapColorsForFrame(frame: number) {
        for (let i = 0; i < 160 * 144; i++) {
            const frameData = this.FrameBuffer[frame][i];
            this.FrameBuffer[frame][i] = (frameData === 0x3) ? PPU.COLOR1 : ((frameData === 0x2) ? PPU.COLOR2 : ((frameData === 0x1) ? PPU.COLOR3 : PPU.COLOR4));
        }
    }

    private get LCDEnabled(): boolean {
        return this.GetCtrlFlag(PPUFlag.LCDEnabled);
    }

    private set LCDEnabled(bit: boolean) {
        this.SetCtrlFlag(PPUFlag.LCDEnabled, bit);
    }

    private get WndTileMapArea(): boolean {
        return this.GetCtrlFlag(PPUFlag.WndTileMapArea);
    }

    private set WndTileMapArea(bit: boolean) {
        this.SetCtrlFlag(PPUFlag.WndTileMapArea, bit);
    }

    private get WndEnabled(): boolean {
        return this.GetCtrlFlag(PPUFlag.WndEnabled);
    }

    private set WndEnabled(bit: boolean) {
        this.SetCtrlFlag(PPUFlag.WndEnabled, bit);
    }

    private get BgWndTileDataArea(): boolean {
        return this.GetCtrlFlag(PPUFlag.BgWndTileDataArea);
    }

    private set BgWndTileDataArea(bit: boolean) {
        this.SetCtrlFlag(PPUFlag.BgWndTileDataArea, bit);
    }

    private get BgTileMapArea(): boolean {
        return this.GetCtrlFlag(PPUFlag.BgTileMapArea);
    }

    private set BgTileMapArea(bit: boolean) {
        this.SetCtrlFlag(PPUFlag.BgTileMapArea, bit);
    }

    private get ObjSize(): boolean {
        return this.GetCtrlFlag(PPUFlag.ObjSize);
    }

    private set ObjSize(bit: boolean) {
        this.SetCtrlFlag(PPUFlag.ObjSize, bit);
    }

    private get ObjEnabled(): boolean {
        return this.GetCtrlFlag(PPUFlag.ObjEnabled);
    }

    private set ObjEnabled(bit: boolean) {
        this.SetCtrlFlag(PPUFlag.ObjEnabled, bit);
    }

    private get BgWndEnabled(): boolean {
        return this.GetCtrlFlag(PPUFlag.BgWndEnabled);
    }

    private set BgWndEnabled(bit: boolean) {
        this.SetCtrlFlag(PPUFlag.BgWndEnabled, bit);
    }

    private get BgWndPriority(): boolean {
        return this.GetCtrlFlag(PPUFlag.BgWndPriority);
    }

    private set BgWndPriority(bit: boolean) {
        this.SetCtrlFlag(PPUFlag.BgWndPriority, bit);
    }

    private get Mode(): PPUMode {
        return this.CPU.Mem.ReadByte(0xFF41) & 0b0011;
    }

    private set Mode(mode: PPUMode) {
        const flags = this.CPU.Mem.ReadByte(0xFF41) & 0b11111100;
        this.CPU.Mem.WriteByte(0xFF41, flags | mode);
    }

    private get LYC(): boolean {
        return !!(this.CPU.Mem.ReadByte(0xFF41) & 0b0100);
    }

    private set LYC(bit: boolean) {
        const flags = this.CPU.Mem.ReadByte(0xFF41) & 0b11111011;
        this.Mem.WriteByte(0xFF41, flags | (bit ? 0b00000100 : 0));
    }

    private get STAT(): number {
        const flags = this.CPU.Mem.ReadByte(0xFF41);
        let stat = 0;
        if (flags & 0b01000000) {
            stat |= StatusIRQ.LYC;
        }
        if (flags & 0b00100000) {
            stat |= StatusIRQ.Mode2;
        }
        if (flags & 0b00010000) {
            stat |= StatusIRQ.Mode1;
        }
        if (flags & 0b00001000) {
            stat |= StatusIRQ.Mode0;
        }
        return stat;
    }

    private set STAT(stat: number) {
        let flags = this.CPU.Mem.ReadByte(0xFF41) & 0b10000111;
        if (stat & StatusIRQ.LYC) {
            flags |= 0b01000000;
        }
        if (stat & StatusIRQ.Mode2) {
            flags |= 0b00100000;
        }
        if (stat & StatusIRQ.Mode1) {
            flags |= 0b00010000;
        }
        if (stat & StatusIRQ.Mode0) {
            flags |= 0b00001000;
        }
        this.CPU.Mem.WriteByte(0xFF41, flags);
    }

    private GetCtrlFlag(flag: PPUFlag): boolean {
        return !!(this.CPU.Mem.ReadByte(0xFF40) & flag);
    }

    private SetCtrlFlag(flag: PPUFlag, bit: boolean) {
        const flags = this.CPU.Mem.ReadByte(0xFF40);
        this.CPU.Mem.WriteByte(0xFF40, bit ? (flags | flag) : (flags & (~flag)));
    }
}

export default PPU;