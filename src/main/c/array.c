#include "array.h"

int array_create(array ** A, uint32_t length) {
  *A = (array *) malloc(sizeof(array));
  (*A)->data = (uint32_t *) malloc(length * sizeof(uint32_t));
  (*A)->length = length;
  (*A)->size = 0;
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

void array_swap(uint32_t * data, int a, int b) {
  uint32_t tmp = data[a];
  data[a] = data[b];
  data[b] = tmp;
}

void array_set(array ** A, uint32_t val, uint32_t size) {
  if ((*A)->length < size) {
    (*A)->data = (uint32_t *) realloc((*A)->data, size * 2 * sizeof(uint32_t));
    (*A)->length = size * 2;
  }
  for (int i = 0; i < size; i++)
    (*A)->data[i] = val;
  (*A)->size = size;
}

void array_randomize(array ** A, uint32_t size) {
  if ((*A)->length < size) {
    (*A)->data = (uint32_t *) realloc((*A)->data, size * 2 * sizeof(uint32_t));
    (*A)->length = size * 2;
  }
  for (int i = 0; i < size; i++)
    (*A)->data[i] = rand() % 100;
  (*A)->size = size;
}

void array_sort_insertion(array * A) {
  for (int i = 1; i < A->size; i++) {
    int j = i - 1;
    while (j >= 0 && A->data[j] > A->data[j+1]) {
      array_swap(A->data, j, j+1);
      j--;
    }
  }
}

void array_copy(uint32_t * data_A, uint32_t * data_B, int start_A, int start_B, int num) {
  for (int i = 0; i < num; i++)
    data_B[start_B + i] = data_A[start_A + i];
}

int array_merge(array *A, array * B, array * C, int l) {
  int b = 0, c = 0, i = l;
  while (B->data[b] != (uint32_t) ((int32_t) -1) ||
         C->data[c] != (uint32_t) ((int32_t) -1)) {
    if (B->data[b] < C->data[c])
      A->data[i++] = B->data[b++];
    else
      A->data[i++] = C->data[c++];
  }
  return 0;
}

int array_sort_mergesort(array *A, array * B, array * C, int l, int r) {
  if (r - l > 0) {
    int mid = l + (r - l) / 2;
    array_sort_mergesort(A, B, C, l, mid);
    array_sort_mergesort(A, B, C, mid + 1, r);

    array_copy(A->data, B->data, l, 0, mid - l + 1);
    array_copy(A->data, C->data, mid + 1, 0, r - (mid + 1) + 1);

    B->data[mid - l + 1] = (uint32_t) ((int32_t) -1);
    C->data[r - (mid + 1) + 1] = (uint32_t) ((int32_t) -1);

    array_merge(A, B, C, l);
  }
  return 0;
}

int array_sort_quicksort_partition(array * A, int l, int r) {
  int head = l - 1;

  // Randomly choose a pivot
  array_swap(A->data, l + rand() % (r - l + 1), r);

  // Everything except the final swap
  for (int i = l; i < r; i++) {
    if (A->data[i] < A->data[r]) {
      array_swap(A->data, ++head, i);
    }
  }

  // Do the final swap
  array_swap(A->data, ++head, r);
  return head;
}

int array_sort_quicksort(array * A, int l, int r) {
  if (l < r) {
    int mid = array_sort_quicksort_partition(A, l, r);
    array_sort_quicksort(A, l, mid - 1);
    array_sort_quicksort(A, mid + 1, r);
  }
  return 0;
}

int array_test_sorted(array * A) {
  for (int i = 1; i < A->size; i++)
    if (A->data[i] < A->data[i-1]) return 1;
  return 0;
}
