#include "mergesort.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"


int int_comparator(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

int char_comparator(const void* a, const void* b)
{
    return (int)*(char*)a - (int)*(char*)b;
}

int str_comparator(const void* a, const void* b)
{
    char* str1 = *(char**)a;
    char* str2 = *(char**)b;
    return strcmp(str1, str2);
}

int main(int argc, char* argv[])
{
    int n = argc - 2;
    char* type = argv[1];
    
    if (n <= 0) {
        return 1;
    }
    
    if (strcmp(type, "int") == 0) {
        int* data = (int*)malloc(n * sizeof(int));
        if (data == NULL) {
            printf("Error: memory allocation failed.\n");
            exit(1);
        }
        for (int i = 0; i < n; i++) {
            data[i] = atoi(argv[i + 2]);
        }
        
        int ret = mergesort(data, (size_t)n, sizeof data[0], int_comparator);
        if (ret == -1) {
            printf("Error: memory allocation failed.\n");
            exit(1);
        }
        
        for (int i = 0; i < n; i++) {
            printf("%d", data[i]);
            if (i != n - 1) {
                printf(" ");
            }
        }
        
        free(data);
    }
    
    if (strcmp(type, "char") == 0) {
        char* data = (char*)malloc(n * sizeof(char));
        if (data == NULL) {
            printf("Error: memory allocation failed.\n");
            exit(1);
        }
        for (int i = 0; i < n; i++) {
            data[i] = *argv[i + 2];
        }
        
        int ret = mergesort(data, (size_t)n, sizeof data[0], char_comparator);
        if (ret == -1) {
            printf("Error: memory allocation failed.\n");
            exit(1);
        }
        
        for (int i = 0; i < n; i++) {
            printf("%c", data[i]);
            if (i != n - 1) {
                printf(" ");
            }
        }
        
        free(data);
    }
    
    if (strcmp(type, "str") == 0) {
        argv += 2;
        
        int ret = mergesort(argv, (size_t)n, sizeof argv[0], str_comparator);
        if (ret == -1) {
            printf("Error: memory allocation failed.\n");
            exit(1);
        }
        
        for (int i = 0; i < n; i++) {
            printf("%s", argv[i]);
            if (i != n - 1) {
                printf(" ");
            }
        }
    }
    
    printf("\n");
}
