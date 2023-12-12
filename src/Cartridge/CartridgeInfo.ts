import CartridgeType from "./CartridgeType";
import DestinationCode from "./DestinationCode";
import RamSize from "./RamSize";
import RomSize from "./RomSize";

interface CartridgeInfo {
    Title: string;
    ManufacturerCode: string;
    CGB_Flag: boolean;
    Licensee: string;
    SGB_Flag: boolean;
    CartType: CartridgeType;
    RomSize: RomSize;
    RamSize: RamSize;
    DestCode: DestinationCode;
    RomVersion: number;
    HeaderChecksum: number;
    GlobalChecksum: number;
}

export default CartridgeInfo;