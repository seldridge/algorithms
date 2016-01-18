#include "heap.h"

void heap_print(array * H) {
  int shift_amount = 1;
  int count = 0, max = 0;
  for (int i = 0; i < H->size; i++) {
    printf("%d ", H->data[i]);
    if (count == max) {
      printf("\n");
      count = 0;
      max = 1 << shift_amount++;
    }
    count++;
  }
  printf("\n");
}

int heap_parent(array * H, int i) {
  return (i - 1) / 2;
}

int heap_left(array * H, int i) {
  return i * 2 + 1;
}

int heap_right(array * H, int i) {
  return i * 2 + 2;
}

void heap_max_heapify(array * H, int i) {
  int left = heap_left(H, i);
  int right = heap_right(H, i);
  int largest = i;
  if (left < H->size && H->data[left] > H->data[i])
    largest = left;
  if (right < H->size && H->data[right] > H->data[largest])
    largest = right;
  if (largest != i) {
    array_swap(H->data, largest, i);
    heap_max_heapify(H, largest);
  }
}

void heap_build_max_heap(array * H) {
  for (int i = H->size / 2 - 1; i >= 0; i--)
    heap_max_heapify(H, i);
}

int heap_is_max_heap(array * H, int i) {
  int return_val = 0;
  int left = heap_left(H, i);
  int right = heap_right(H, i);
  if (left < H->size && H->data[left] > H->data[i])
    return_val--;
  if (right < H->size && H->data[right] > H->data[i])
    return_val--;
  if (left < H->size)
    return_val += heap_is_max_heap(H, heap_left(H, i));
  if (right < H->size)
    return_val += heap_is_max_heap(H, heap_right(H, i));
  return return_val;
}

int heap_insert(array ** H, uint32_t val) {
  // If the array is not large enough, then we need to reallocate the
  // data portion of the array.
  int return_val = 0;
  if ((*H)->size == (*H)->length) {
    (*H)->data = (uint32_t *) realloc((*H)->data, (*H)->length * 2 * sizeof(uint32_t));
    (*H)->length = (*H)->length * 2;
    return_val = (*H)->length;
  }

  int i = (*H)->size;
  (*H)->data[(*H)->size++] = val;
  while (i > 0 && (*H)->data[i] > (*H)->data[heap_parent(*H, i)]) {
    array_swap((*H)->data, heap_parent(*H, i), i);
    i = heap_parent(*H, i);
  }
  return return_val;
}

void heap_sort(array * A) {
  heap_build_max_heap(A);
  int size_d = A->size;
  for (int i = 0; i < size_d; i++) {
    array_swap(A->data, 0, A->size - 1);
    A->size--;
    heap_max_heapify(A, 0);
  }
  A->size = size_d;
}
