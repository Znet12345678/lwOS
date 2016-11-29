CRTBEGIN=$(shell $(CC) -print-file-name=crtbegin.o)
CRTEND=$(shell $(CC) -print-file-name=crtend.o)
NASM = nasm -f elf
CC=i386-elf-gcc
LDFLAGS = 
CFLAGS = -std=gnu99 -nostdlib -ffreestanding -Iinclude
OBJ = xw.o inportsl.o str.o boot.o crti.o crtn.o kprintf.o tty.o kernel.o kmalloc.o inportb.o fat.o ata.o panic.o lfs.o libpart.o
all:
	${CC} -c libasm/inportsl.c -o inportsl.o ${CFLAGS}
	${CC} -c libasm/xw.c -o xw.o ${CFLAGS}
	${CC} -c libc/str.c -o str.o ${CFLAGS}
	${CC} -c libkern/kprintf.c -o kprintf.o ${CFLAGS}
	${CC} -c libkern/tty.c -o tty.o ${CFLAGS}
	${CC} -c libkern/boot.S -o boot.o ${CFLAGS}
	${CC} -c libkern/crti.S -o crti.o ${CFLAGS}
	${CC} -c libkern/crtn.S -o crtn.o ${CFLAGS}
	${CC} -c kernel.c -o kernel.o ${CFLAGS}
	${CC} -c mem/kmalloc.c -o kmalloc.o ${CFLAGS}
	${CC} -c libfat/fat.c -o fat.o ${CFLAGS}
	${CC} -c libkern/ata.c -o ata.o ${CFLAGS}
	${CC} -c libkern/panic.c -o panic.o ${CFLAGS}
	${NASM} libasm/inportb.asm -o inportb.o
	${CC} -c lfs/lfs.c -o lfs.o ${CFLAGS}
	${CC} -c libpart/libpart.c -o libpart.o ${CFLAGS}
	${CC} ${OBJ} $(CRTBEGIN) $(CRTEND) -o kernel.elf -nostdlib -T linker.ld
