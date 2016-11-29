#ifndef __MBR_H
#define __MBR_H
struct mbr{
	char bootabe;
	char start_head;
	short start_sector;
	int start_cylinder;
	char id;
	char end_head;
	short end_sector;
	int end_cylinder;
	uint32_t lba;
	uint32_t sectors;
};
struct mbr *parse_mbr();
#endif
