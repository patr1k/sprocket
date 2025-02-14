CC=emcc
CCFLAGS=-I./include

all: main.o mem.o cpu.o cpu_0.o
	$(CC) -o gbjs.js main.o mem.o cpu.o cpu_0.o -WASM=1

main.o: src/main.c
	$(CC) $(CCFLAGS) -g -c src/main.c

mem.o: src/mem.c
	$(CC) $(CCFLAGS) -g -c src/mem.c

cpu.o: src/cpu.c
	$(CC) $(CCFLAGS) -g -c src/cpu.c

cpu_0.o: src/cpu_0.c
	$(CC) $(CCFLAGS) -g -c src/cpu_0.c

.PHONY: clean
clean:
	rm -rf *.js *.wasm *.o
