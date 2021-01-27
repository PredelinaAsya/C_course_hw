#ifndef __MERGESORT_H__
#define __MERGESORT_H__


#include "stddef.h"

int mergesort(void *array, size_t elements, size_t element_size,
              int (*comparator)(const void*, const void*));

#endif
