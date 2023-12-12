import Gameboy from './Gameboy';

const gb = new Gameboy();

const file = document.getElementById('romFile') as HTMLInputElement;
file.addEventListener('change', () => {
    gb.StartRom(file.files[0]);
});

//gb.StartRom(`${__dirname}/roms/cpu_instrs/cpu_instrs.gb`);