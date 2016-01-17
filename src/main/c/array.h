#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
  uint32_t * data;
  uint32_t size;
} array;

int array_create(array ** A, uint32_t size);

int array_destroy(array ** A);

void array_print(array * A);

void array_swap(array * A, int a, int b);

void array_set(array * A, uint32_t val);

void array_copy(array * A, array * B, int start_A, int start_B, int num);

void array_randomize(array * A);

void array_sort_insertion(array * A);

int array_sort_mergesort(array * A, array * B, array * C, int l, int r);

int array_sort_merge(array * A, array * B, array * C, int l, int r, int mid);

int array_test_sorted(array * A);

#endif
