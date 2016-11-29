#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int getlba(int partnum){
	char *buf = kmalloc(1024);
	//char buf[512];
	ata_read_master(buf,0,0);
	return (buf[partnum * 16 + 454] << 24 | buf[partnum * 16 + 455] << 16 | buf[partnum * 16 + 456] << 8 | buf[partnum * 16 + 457]);
}
int write_part(uint8_t *buf,int lba,int partnum){
	return ata_write_master(buf,lba + getlba(partnum));
}
int read_part(uint8_t *buf,int lba,int partnum){
	return ata_read_master(buf,lba + getlba(partnum),0);
}
