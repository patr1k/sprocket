import CPU from "../CPU/CPU";
import Memory from "../Memory";
import { Byte } from "../Utils";
import Flags from "./Flags";
import RenderMode from "./RenderMode";

class PPU {
    Mem: Memory;
    CPU: CPU;
    LCD: CanvasRenderingContext2D;
    Mode: RenderMode;

    Run: boolean = true;
    DrawLoop: NodeJS.Timeout;

    Zoom: number;
    ZoomWidth: number;
    ZoomHeight: number;

    private static Width: number = 160;
    private static Height: number = 144;

    LX: number = 0;
    LY: number = 0;

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
            this.Mode = RenderMode.V_Blank;
        } else {
            if (this.LX < 80) {
                this.Mode = RenderMode.OAM_Scan;
            } else if (this.LX < 144) {
                this.Mode = RenderMode.Drawing;
            } else {
                this.Mode = RenderMode.H_Blank;
            }
        }

        setTimeout(() => this.Draw(Date.now()), 16);
    }

    LCDEnabled(bit: boolean = null): boolean {
        return this.GetSetFlag(Flags.LCDEnabled, bit);
    }

    WndTileMapArea(bit: boolean = null): boolean {
        return this.GetSetFlag(Flags.WndTileMapArea, bit);
    }

    WndEnabled(bit: boolean = null): boolean {
        return this.GetSetFlag(Flags.WndEnabled, bit);
    }

    BgWndTileDataArea(bit: boolean = null): boolean {
        return this.GetSetFlag(Flags.BgWndTileDataArea, bit);
    }

    BgTileMapArea(bit: boolean = null): boolean {
        return this.GetSetFlag(Flags.BgTileMapArea, bit);
    }

    ObjSize(bit: boolean = null): boolean {
        return this.GetSetFlag(Flags.ObjSize, bit);
    }

    ObjEnabled(bit: boolean = null): boolean {
        return this.GetSetFlag(Flags.ObjEnabled, bit);
    }

    BgWndEnabled(bit: boolean = null): boolean {
        return this.GetSetFlag(Flags.BgWndEnabled, bit);
    }

    BgWndPriority(bit: boolean = null): boolean {
        return this.GetSetFlag(Flags.BgWndPriority, bit);
    }

    private GetSetFlag(flag: Byte, bit: boolean): boolean {
        const flags = this.CPU.Mem.ReadByte(0xFF40);
        if (null === bit) {
            return !!(flags & flag);
        } else {
            this.CPU.Mem.WriteByte(0xFF40, bit ? (flags | flag) : (flags & (~flag)));
            return bit;
        }
    }
}

export default PPU;