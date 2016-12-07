#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <io.h>
#define NULL ((char*)0)
/*
*Header:
*next mem pntr
*h.size
*h.free?
*/

void free(void *v){
	char *mem = v;
	*mem--;
	*mem--;
	*mem = 0;
	*mem++;
	int size = *mem;
	*mem++;
	for(int i = 0; i < size;i++,*mem++)
		*mem = 0;
}
struct header{
	int nxt;
	int size;
	int free;
};
void init_mem(){
//	int *mem = (int*)0x00100000;
	int lowmem,highmem,total;
	outb(0x70,0x30);
	lowmem = inb(0x71);
	outb(0x70,0x31);
	highmem = inb(0x71);
	total = lowmem | highmem << 8;
	int *mem = (int*)total;
	*mem = 0;
	*mem++;
	*mem = 0;
	*mem++;
//	while(*mem < highmem){
//		*mem = 0;
//		*mem++;
//	}
}
int *__find_next_free_head(int *curr){
	int *dup = curr;
	while(1){
		struct header h;
		
		h.nxt = *dup;
		*dup++;
		h.size = *dup;
		*dup++;
		h.free = *dup;
		*dup++;
		for(int i = 0; i < h.size;i++)
			*dup++;
		if(*dup == 0)
			return dup;
	}
}
int init_memblk(int *pntr,struct header init){
	*pntr = init.nxt;
	*pntr++;
	*pntr = init.size;
	*pntr++;
	*pntr = init.free;
	*pntr++;
	int *dup = pntr;
	for(int i = 0; i < init.size; i++){
		*pntr = 0;
		*pntr++;
	}
}
void *kmalloc(size_t n){
	//kprintf("kmalloc(%d)\n",n);
	int *ret;
	int mema,meml,memh;
	outb(0x70,0x30);
	meml = inb(0x71);
	outb(0x71,0x31);
	memh = inb(0x71);
	mema = meml | memh << 8;
	int *mem = (int*)mema;
	int *orig;
	int allocated = 0;
	while(allocated < n){
		int free = *mem;
		*mem++;
		int size = *mem;;
		*mem++;
		*mem-=2;
		if(free == 0){
			*mem = 1;
			if(size == 0){
				*mem++;
				*mem = n;
				*mem++;
				for(int i = 0; i < n;i++){
					*ret = *mem;
					*mem = 0;
					*mem++;
					allocated++;
					*ret++;
				}
			}
			else{
				*mem++;
				*mem++;
				for(int i = 0; i < size;i++){
					*ret = *mem;
					*mem = 0;
					*mem++;
					allocated++;
					*ret++;
				}
			}
			struct header nxt;
			nxt.free = *mem;
			*mem++;
			nxt.size = *mem;
			if(nxt.size == 0){
				*mem--;
				*mem = 1;
				*mem++;
			}
		}else{
			for(int i = 0; i < size;i++)
				*mem++;
		}
	}
	return (void *)ret;

}
