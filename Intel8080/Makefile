CC=gcc
CFLAGS=-Wall -Wextra -fomit-frame-pointer -O2 -fPIC

main: Cpu.o
	rm -rf ./build
	mkdir build
	$(CC) -shared -Wl,-soname,libi8080.so.1 -o build/libi8080.so.1.0 Cpu.o

clean: 
	rm -rf ./build

