#include <string.h>
size_t strlen(const char *str){
	int i = 0;
	while(str[i] != 0)
		i++;
	return i;
}
int kstrcpy(char *dest,const char *src){
	int i = strlen(dest);
	int j = 0;
	while(j < strlen(src)){
		dest[i] = src[j];
		j++;
		i++;
	}
	return 1;
}
int kstrcat(char *dest,const char *src){
	return kstrcpy(&dest[strlen(dest)],src);
}
int strcmp(const char *str1,const char *str2){
	if(strlen(str1) != strlen(str2))
		return -1;
	for(int i =0; i < strlen(str1);i++)
		if(str1[i] != str2[i])
			return ++i;
	return 0;
}
int strncmp(const char *str1,const char *str2,int n){
	for(int i = 0; i < n;i++)
		if(str1[i] != str2[i])
			return ++i;
	return 0;
}

