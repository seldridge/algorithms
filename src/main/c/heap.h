#ifndef __HEAP_H__
#define __HEAP_H__

#include "array.h"

void heap_print(array * H);

int heap_parent(array * H, int i);
int heap_left(array * H, int i);
int heap_right(array * H, int i);

void heap_max_heapify(array * H, int i);
void heap_build_max_heap(array * H);

int heap_insert(array ** H, uint32_t val);
uint32_t heap_extract_max(array * H);
void heap_increase_key(array * H, int i);
uint32_t heap_max(array * H);

int heap_is_max_heap(array * H, int i);

#endif
