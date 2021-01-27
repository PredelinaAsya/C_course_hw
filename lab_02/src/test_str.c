#include "string.h"
#include "assert.h"
#include "test_str.h"
#include "str.h"

void test_strlen(){
	assert(my_strlen("") == strlen(""));
	assert(my_strlen("Hello") == strlen("Hello"));
	assert(my_strlen("Hello, it's me") == strlen("Hello, it's me"));
}

void test_strcpy(){
	char s1[4];
	char s2[] = "wow";
	assert(strcmp(my_strcpy(s1, s2), "wow") == 0);
}

void test_strcat(){
	char s1[4] = "one";
	char s2[4] = "two";
	assert(strcmp(my_strcat(s1, s2),"onetwo") == 0);
}

void test_strcmp(){
	char s1[4] = "one";
	char s2[4] = "two";
	assert(my_strcmp(s1, s2) < 0);
	assert(my_strcmp(s2, s1) > 0);
	assert(my_strcmp(s1, s1) == 0);
	char s3[7] = "onetwo";
	assert(my_strcmp(s1, s3) < 0);
	assert(my_strcmp(s3, s1) > 0);
}
