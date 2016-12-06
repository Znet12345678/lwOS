#ifndef __STDLIB_H
#define __STDLIB_H
#include <sys/types.h>
#define MEM_SIG 0x7F
#include <stdint.h>
void *kmalloc(size_t size);
struct mem_seg{
	int sig;
	int size;
};
#define LAST_MEM_SEGMENT 0x1f
struct memory_data{
        int sig;
        int alloc;
        int size;
        int pntr;
};
int getlba(int partnum);
int write_part(uint8_t *buf,int lba,int partnum);
int read_part(uint8_t *buf,int lba,int partnum);
void panic();
#endif
