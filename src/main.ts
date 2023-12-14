import Gameboy from "./Gameboy";

document.addEventListener('DOMContentLoaded', () => {
    const canvas = document.getElementById('screen') as HTMLCanvasElement;
    const gb = new Gameboy({ canvas, zoom: 4 });

    const file = document.getElementById('romFile') as HTMLInputElement;
    file.addEventListener('change', () => {
        gb.StartRom(file.files[0]);
    });
});