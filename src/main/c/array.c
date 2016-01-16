#include "array.h"

int array_create(array ** A, uint32_t size) {
  *A = (array *) malloc(sizeof(array));
  (*A)->data = (uint32_t *) malloc(size * sizeof(uint32_t));
  (*A)->size = size;
  return 0;
}

int array_destroy(array ** A) {
  free((*A)->data);
  free(*A);
  return 0;
}

void array_print(array * A) {
  for (int i = 0; i < A->size; i++) {
    printf("%d: %d\n", i, A->data[i]);
  }
  printf("\n");
}

void array_swap(array * A, int a, int b) {
  uint32_t tmp = A->data[a];
  A->data[a] = A->data[b];
  A->data[b] = tmp;
}

void array_randomize(array * A) {
  for (int i = 0; i < A->size; i++) {
    A->data[i] = rand() % 100;
  }
}

void array_sort_insertion(array * A) {
  for (int i = 1; i < A->size; i++) {
    int j = i - 1;
    while (j >= 0 && A->data[j] > A->data[j+1]) {
      array_swap(A, j, j+1);
      j--;
    }
  }
}

int array_test_sorted(array * A) {
  for (int i = 1; i < A->size; i++)
    if (A->data[i] < A->data[i-1]) return 1;
  return 0;
}
