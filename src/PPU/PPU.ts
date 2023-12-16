import CPU from "../CPU/CPU";
import PPUFlag from "./PPUFlag";
import Memory from "../Memory/Memory";
import RenderMode from "./RenderMode";
import IO from "../Memory/IO";
import { Byte } from "../Utils";
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

    constructor(cpu: CPU, mem: Memory, ctx: CanvasRenderingContext2D, zoom: number = 1) {
        this.CPU = cpu;
        this.Mem = mem;
        this.LCD = ctx;

        this.Zoom = zoom;
        this.ZoomWidth = PPU.Width * zoom;
        this.ZoomHeight = PPU.Height * zoom;

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
                                this.GetBackgroundForLine(Y);
                            }
                            if (this.ObjEnabled) {
                                this.GetSpritesForLine(Y);
                            }
                            this.Mode = PPUMode.H_Blank;
                            if (this.STAT & StatusIRQ.Mode0) {
                                this.CPU.Interrupt(IRQ.LCD_STAT);
                            }
                        } else if (Y === 144) {
                            this.Mode = PPUMode.V_Blank;
                            this.CPU.Interrupt(IRQ.LCD_VBLANK);
                            this.MapColorsForFrame();

                            sendingFrame = calcFrame;
                            calcFrame = calcFrame ? 0 : 1;
                            // Draw the frame (this should already be done by the steps above)
                            // this.Mem.WriteByte(0, 2 * 160 * 144, frames[sendingFrame])
                        } else {
                            this.Mode = PPUMode.V_Blank;
                        }
                    }
                    break;
            }
        }
    }

    GetBackgroundForLine(y: Byte) {

    }

    GetSpritesForLine(y: Byte) {

    }

    MapColorsForFrame() {

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