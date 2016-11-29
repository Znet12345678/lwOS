#include "lfs.h"
#include <io.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int __mkfs_lfs(){
	struct init_blk *init = kmalloc(sizeof(struct init_blk *) * sizeof(*init));
	init->alloc = 1;
	init->fsvers = 1;
	init->first_dir = 2;
	char buf[512] = {init->alloc,init->fsvers,init->first_dir >> 24,init->first_dir >> 16,init->first_dir >> 8,init->first_dir,[6 ... 511]0};
	if(ata_write_master(buf,0) < 0)
		panic();
	struct dirent_lfs *rootdir = kmalloc(sizeof(struct dirent_lfs *) * sizeof(*rootdir));
	rootdir->alloc = 1;
	rootdir->namelen = 1;
	kstrcpy(rootdir->name,"/");
	rootdir->next_file_offset = 0;
	rootdir->next_dir_offset = 0;
	rootdir->next_file_lba = 0;
	rootdir->next_dir_lba = 0;
	for(int i = 0; i < 512 ;i++)
		buf[i] = 0;
	buf[0] = rootdir->alloc;
	buf[1] = rootdir->namelen;
	buf[2] = '/';
	buf[3] = rootdir->next_file_offset;
	buf[4] = rootdir->next_dir_offset;
	buf[5] = rootdir->next_file_lba >> 24;
	buf[6] = rootdir->next_file_lba >> 16;
	buf[7] = rootdir->next_file_lba >> 8;
	buf[8] = rootdir->next_file_lba;
	buf[9] = rootdir->next_dir_lba >> 24;
	buf[10] = rootdir->next_dir_lba >> 16;
	buf[11] = rootdir->next_dir_lba >> 8;
	buf[12] = rootdir->next_dir_lba;
	if(ata_write_master(buf,init->first_dir) < 0)
		panic();
	return 1;
}
int __mkfs_lfs_part(int partnum){
	struct init_blk *init = kmalloc(sizeof(struct init_blk *) * sizeof(*init));
        init->alloc = 1;
        init->fsvers = 1;
        init->first_dir = 2;
        char buf[512] = {init->alloc,init->fsvers,init->first_dir >> 24,init->first_dir >> 16,init->first_dir >> 8,init->first_dir,[6 ... 511]0};
        if(write_part(buf,0,partnum) < 0)
                panic();
        struct dirent_lfs *rootdir = kmalloc(sizeof(struct dirent_lfs *) * sizeof(*rootdir));
        rootdir->alloc = 1;
        rootdir->namelen = 1;
        kstrcpy(rootdir->name,"/");
        rootdir->next_file_offset = 0;
        rootdir->next_dir_offset = 0;
	rootdir->next_file_lba = 0;
	rootdir->next_dir_lba = 0;
        for(int i = 0; i < 512 ;i++)
                buf[i] = 0;
        buf[0] = rootdir->alloc;
        buf[1] = rootdir->namelen;
        buf[2] = '/';
	buf[3] = rootdir->next_file_offset;
	buf[4] = rootdir->next_dir_offset;
	buf[5] = rootdir->next_file_lba >> 24;
	buf[6] = rootdir->next_file_lba >> 16;
	buf[7] = rootdir->next_file_lba >> 8;
	buf[8] = rootdir->next_file_lba;
	buf[9] = rootdir->next_dir_lba >> 24;
	buf[10] = rootdir->next_dir_lba >> 16;
	buf[11] = rootdir->next_dir_lba >> 8;
	buf[12] = rootdir->next_dir_lba;
        if(write_part(buf,init->first_dir,partnum) < 0)
                panic();
        return 1;

}
int __is_lfs(){
	char *buf = kmalloc(1024);
	ata_read_master(buf,0,0);
	if(buf[0] == 1 && buf[1] == 1)
		return 1;
	return 0;
}
int __is_lfs_part(int partnum){
	char *buf = kmalloc(1024);
	read_part(buf,0,partnum);
	if(buf[0] == 1 && buf[1] == 1)
		return 1;
	return 0;
}
struct init_blk *__lfs_parse_initblk(){
	struct init_blk *ret = kmalloc(sizeof(*ret) * sizeof(struct init_blk *));
	char *buf = kmalloc(513);
	ata_read_master(buf,0,0);
	ret->alloc = buf[0];
	ret->fsvers = buf[1];
	ret->first_dir = buf[2] << 24 | buf[3] << 16 | buf[4] << 8 | buf[5];
	return ret;
}
struct dirent_lfs *__lfs_parse_dirent(int num){
	struct init_blk *initblk = __lfs_parse_initblk();
	int lba = initblk->first_dir;
	struct dirent_lfs *ret = kmalloc(sizeof(*ret) * sizeof(struct dirent_lfs *));
	int pos = 0;
	for(int i = 0; i < num;i++){
		char *buf = kmalloc(1024);
		ata_read_master(buf,lba,0);
		ret->alloc = buf[pos];
		pos++;
		ret->namelen = buf[pos];
		pos++;
		for(int j = 0; j < ret->namelen;j++){
			ret->name[j] = buf[pos + j];
			pos++;
		}
		ret->next_file_offset = buf[pos];
		pos++;
		ret->next_dir_offset = buf[pos];
		pos++;
		ret->next_file_lba = buf[pos] << 24 | buf[pos + 1] << 16 | buf[pos + 2] << 8 | buf[pos + 3];
		pos+=4;
		ret->next_dir_lba = buf[pos] << 24 | buf[pos + 1] << 16 | buf[pos +2] << 8 | buf[pos + 3];
		pos+=4;
		pos = ret->next_dir_offset;
		lba = ret->next_dir_lba;

	}
	return ret;
}
int __lfs_write(char *dir,char *name,int *cont,int n){
	struct init_blk *initblk = __lfs_parse_initblk();
	char *buf = kmalloc(513);
	int i = 0;
	while(1){
		struct dirent_lfs *ent = __lfs_parse_dirent(i);
		if(strcmp(ent->name,name) == 0)
			break;
		i++;
	}
}
