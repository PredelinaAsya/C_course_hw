#include "str.h"

size_t my_strlen(const char *s){
	const char *p = s;
	while (*p){
		p++;
	}
	return (p - s);
}

char *my_strcpy(char * restrict s1, const char * restrict s2){
	char *ans = s1;
	while (*s1 = *s2){
		s1++;
		s2++;
	}
	return ans;
}

char *my_strcat(char * restrict s1, const char * restrict s2){
	char *ans = s1;
	while (*s1){
		s1++;
	}
	while (*s1 = *s2){
		s1++;
		s2++;
	}
	*s1 = '\0';
	return ans;
}

int my_strcmp(const char *s1, const char *s2){
	while (*s1 && *s2){
		char c1 = *s1;
		char c2 = *s2;
		if (c1 == c2){
			s1++;
			s2++;
		} else if (c1 < c2) {
			return -1;
		} else{
			return 1;
		}
	}
	if (*s1 && !(*s2)){
		return 1;
	}
	if (*s2 && !(*s1)){
		return -1;
	}
	return 0;
}
