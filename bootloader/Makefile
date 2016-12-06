all:
	nasm -f bin bootloader.asm -o bootloader.bin
	gcc -c makeloader.c -o makeloader.o
	gcc makeloader.o -o makeloader
