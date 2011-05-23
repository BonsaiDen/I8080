CC=gcc
CFLAGS=-Wall -Wextra

main: main.o Intel8080/Cpu.o


clean: 
	rm -f main.o

