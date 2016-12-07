#include <stdlib.h>
#include "libfat/fat.h"
void kernel(){
	kprintf("Loading...\n");
	char *test =kmalloc(1024);
	kstrcpy(test,"Malloc works!");
	kprintf("%s\n",test);
	struct fat_bpb *bpb = parse_bpb();
	int type = fat_type();
        if(type == FAT12)
                kprintf("Detected FAT12\n");
        else if(type == FAT16)
                kprintf("Detected FAT16\n");
        else if(type == FAT32)
                kprintf("Detected FAT32\n");
        else{
             	kprintf("Error determining fat type!\n");
                panic();
        }
	while(1)
		;
}
