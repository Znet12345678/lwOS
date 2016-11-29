#include <stdio.h>
int panic(){
	kprintf("panic()\n");
	while(1) { }
}
