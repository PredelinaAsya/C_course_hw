#ifndef __STR_H__
#define __STR_H__


#include "stddef.h"

size_t my_strlen(const char *s);
char *my_strcpy(char * restrict s1, const char * restrict s2);
char *my_strcat(char * restrict s1, const char * restrict s2);
int my_strcmp(const char *s1, const char *s2);

#endif
