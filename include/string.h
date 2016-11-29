#ifndef __STRING_H
#define __STRING_H
#include <sys/types.h>
size_t strlen(const char *str);
int kstrcpy(char *dest,const char *src);
int kstrcat(char *dest,const char *src);
int strcmp(const char *str1,const char *str2);
int strncmp(const char *str1,const char *str2,int n);
#endif
