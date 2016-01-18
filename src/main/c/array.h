#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
  uint32_t * data;
  uint32_t length; // length of the array
  uint32_t size;   // number of valid elements in the heap
} array;

int array_create(array ** A, uint32_t length);
int array_destroy(array ** A);

void array_print(array * A);

void array_swap(uint32_t * data, int a, int b);
void array_set(array ** A, uint32_t val, uint32_t size);
void array_copy(uint32_t * data_A, uint32_t * data_B, int start_A, int start_B, int num);
void array_randomize(array ** A, uint32_t size);

int array_sort_merge(array * A, array * B, array * C, int l, int r, int mid);
int array_sort_quicksort_partition(array *A, int l, int r);

int array_test_sorted(array * A);

void array_sort_insertion(array * A);
int array_sort_mergesort(array * A, array * B, array * C, int l, int r);
int array_sort_quicksort(array * A, int l, int r);

#endif
