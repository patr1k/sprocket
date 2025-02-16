WASM_OBJECTS = main.wasm.o mem.wasm.o cpu.wasm.o cpu_block_0.wasm.o cpu_block_1.wasm.o cpu_block_2.wasm.o cpu_block_3.wasm.o
C_OBJECTS = main.o mem.o cpu.o cpu_block_0.o cpu_block_1.o cpu_block_2.o cpu_block_3.o
CC=gcc
WASM=emcc
CFLAGS=-I./include

all: exe wasm

exe: $(C_OBJECTS)
	$(CC) -o gbjs $(C_OBJECTS)

wasm: $(WASM_OBJECTS)
	$(WASM) -o gbjs.js $(WASM_OBJECTS) -WASM=1

%.wasm.o: src/%.c
	$(WASM) $(CFLAGS) -g -c $< -o $@

%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf *.js *.wasm *.o gbjs
