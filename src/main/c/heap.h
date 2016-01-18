#ifndef __HEAP_H__
#define __HEAP_H__

#include "array.h"

typedef struct {
  uint32_t * data;
  uint32_t length; // length of the array
  uint32_t size;   // number of valid elements in the heap
} heap;

int heap_create(heap ** H, uint32_t length);
int heap_destroy(heap ** H);
void heap_randomize(heap * H, uint32_t size);
void heap_print(heap * H);

int heap_parent(heap * H, int i);
int heap_left(heap * H, int i);
int heap_right(heap * H, int i);

void heap_max_heapify(heap * H, int i);
void heap_build_max_heap(heap * H);

int heap_insert(heap * H, uint32_t val);
uint32_t heap_extract_max(heap * H);
void heap_increase_key(heap * H, int i);
uint32_t heap_max(heap * H);

int heap_is_max_heap(heap * H, int i);

#endif
