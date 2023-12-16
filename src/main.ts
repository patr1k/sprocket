import Gameboy from "./Gameboy";

document.addEventListener('DOMContentLoaded', () => {
    const btnPause = document.getElementById('btnPause') as HTMLButtonElement;
    const btnStep = document.getElementById('btnStep') as HTMLButtonElement;

    const canvas = document.getElementById('screen') as HTMLCanvasElement;
    const gb = new Gameboy({ canvas, zoom: 4 });

    const file = document.getElementById('romFile') as HTMLInputElement;
    file.addEventListener('change', () => {
        gb.StartRom(file.files[0]);
        btnPause.disabled = false;
        btnStep.disabled = false;
    });

    btnPause.addEventListener('click', () => {
        if (btnPause.innerText === 'Pause') {
            gb.Pause();
            btnPause.innerText = 'Resume';
        } else {
            gb.Resume();
            btnPause.innerText = 'Pause';
        }
    });

    btnStep.addEventListener('click', () => {
        gb.Step();
    });

});