#include "mergesort.h"
#include "stdlib.h"


void give_value(char* pointer, char* value, size_t elem_size)
{
    for (int i = 0; i < elem_size; i++) {
        *pointer = *value;
        pointer++;
        value++;
    }
}

int merge(void* left, void* mid, void* right, size_t elem_size,
          int (*cmp)(const void*, const void*)) {
    int n = (right - left) / elem_size;
    int m = (mid - left) / elem_size;

    void* result = malloc(n * elem_size);
    if (result == NULL) {
        return -1;
    }

    int it1 = 0;
    int it2 = m;
    void* elem1 = left;
    void* elem2 = mid;
    
    while (it1 < m && it2 < n) {
        if (cmp(elem1, elem2) < 0) {
            give_value(result + (it1 + it2 - m) * elem_size, (char*)elem1,
                       elem_size);
            it1++;
            elem1 = (char*)elem1 + elem_size;
        }
        else {
            give_value(result + (it1 + it2 - m) * elem_size, (char*)elem2,
                       elem_size);
            it2++;
            elem2 = (char*)elem2 + elem_size;
        }
    }

    while (it1 < m) {
        give_value(result + (it1 + it2 - m) * elem_size, (char*)elem1,
                   elem_size);
        it1++;
        elem1 = (char*)elem1 + elem_size;
    }

    while (it2 < n) {
        give_value(result + (it1 + it2 - m) * elem_size, (char*)elem2,
                   elem_size);
        it2++;
        elem2 = (char*)elem2 + elem_size;
    }

    char* ptr = left;
    for (int i = 0; i < it1 + it2 - m; i++) {
        give_value(ptr, result + i * elem_size, elem_size);
        ptr += elem_size;
    }
    
    free(result);
    return 0;
}

int mergesort(void* array, size_t elements, size_t element_size,
              int (*comparator)(const void*, const void*)) {
    if (elements <= 1) {
        return 0;
    }
    
    void* right = (char*)array + elements * element_size;
    void* mid = (char*)array + (elements / 2) * element_size;
    
    int ret = mergesort(array, elements / 2, element_size, comparator);
    if (ret == -1) {
        return -1;
    }
    ret = mergesort(mid, elements - (elements / 2), element_size, comparator);
    if (ret == -1) {
        return -1;
    }
    ret = merge(array, mid, right, element_size, comparator);
    if (ret == -1) {
        return -1;
    }
    return 0;
}
