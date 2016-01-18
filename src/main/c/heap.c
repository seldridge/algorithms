#include "heap.h"

int heap_create(array ** H, uint32_t length) {
  (*H) = (array *) malloc(sizeof(array));
  (*H)->data = (uint32_t *) malloc(length * sizeof(uint32_t));
  (*H)->length = length;
  (*H)->size = 0;
  return 0;
}

int heap_destroy(array ** H) {
  free((*H)->data);
  free(*H);
  return 0;
}

void heap_randomize(array * H, uint32_t size) {
  for (int i = 0; i < size; i++)
    H->data[i] = rand() % 100;
  H->size = size;
}

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
  if (left < H->size - 1 && H->data[left] > H->data[i])
    largest = left;
  if (right < H->size - 1 && H->data[right] > H->data[largest])
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
  if (left < H->size - 1 && H->data[left] > H->data[i])
    return_val--;
  if (right < H->size - 1 && H->data[right] > H->data[i])
    return_val--;
  if (left < H->size - 1)
    return_val += heap_is_max_heap(H, heap_left(H, i));
  if (right < H->size - 1)
    return_val += heap_is_max_heap(H, heap_right(H, i));
  return return_val;
}
