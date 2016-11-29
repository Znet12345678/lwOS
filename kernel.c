#include <stdio.h>
#include <fat.h>
#include "lfs/lfs.h"
void kernel(){
	t_init();

	kprintf("Loading...\n");
	char *test = kmalloc(1024);
	kstrcpy(test,"Malloc works!\n");
	char *n = kmalloc(1024);
	kprintf("%s",test);
	//kprintf("%d\n",getlba(0));
	if(__is_lfs() == 0){
		kprintf("Making lfs file system\n");
		__mkfs_lfs();

	}
	kprintf("Writing test file\n");
	__lfs_write("/","test","test",4);
	kprintf("Done\n");
	while(1)
		;
	//if(__is_lfs() == 0){
	//	kprintf("%d\n",getlba(0));
	//}

}
