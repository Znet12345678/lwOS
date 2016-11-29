#ifndef __MINOS_LFS_H
#define __MINOS_LFS_H
struct init_blk{
	int alloc;
	int fsvers;
	int first_dir;
};
struct dirent_lfs{
	int alloc;
	int namelen;
	char name[255];
	int next_file_offset;
	int next_dir_offset;
	int next_file_lba;
	int next_dir_lba;
};
struct file{
	int alloc;
	int start_lba;
	int start_offset;
	int end_lba;
	int end_offset;
	int next_file_offset;
	int next_file_lba;
};
struct init_blk *__lfs_parse_initblk();
struct dirent_lfs *__lfs_parse_dirent(int num);
int __mkfs_lfs();
int __is_lfs();
int __lfs_ls(char *dir);
int __lfs_write(char *dir,char *name,int *cont,int n);
int __lfs_read(char *dir,char *name,int *buf,int n);
int __lfs_mkdir(char *name);
struct FILE{
	int pos;
	int mode;
};
typedef struct FILE file;
#endif
