CC=gcc
CFLAGS=-Wall -Wextra -O2 -fomit-frame-pointer

main: main.o Intel8080/Cpu.o


clean: 
	rm -f main.o

