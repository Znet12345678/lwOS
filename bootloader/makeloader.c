#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(int argc,char *argv[]){
	if(argc != 3)
		return -1;
	FILE *out = fopen(argv[1],"ab");
	FILE *in = fopen(argv[2],"rb");
	int c;
	if(!in || !out){
		perror("Couldn't open file");
		return -1;
	}
	while((c = getc(in)) != EOF)
		putc(c,out);
	fclose(out);
	fclose(in);
	return 0;
}
