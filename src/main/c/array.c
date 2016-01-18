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

void array_set(array * A, uint32_t val) {
  for (int i = 0; i < A->size; i++)
    A->data[i] = val;
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

void array_copy(array * A, array * B, int start_A, int start_B, int num) {
  for (int i = 0; i < num; i++)
    B->data[start_B + i] = A->data[start_A + i];
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

}

int array_sort_mergesort(array *A, array * B, array * C, int l, int r) {
  if (r - l > 0) {
    int mid = l + (r - l) / 2;
    array_sort_mergesort(A, B, C, l, mid);
    array_sort_mergesort(A, B, C, mid + 1, r);

    array_copy(A, B, l, 0, mid - l + 1);
    array_copy(A, C, mid + 1, 0, r - (mid + 1) + 1);

    B->data[mid - l + 1] = (uint32_t) ((int32_t) -1);
    C->data[r - (mid + 1) + 1] = (uint32_t) ((int32_t) -1);

    array_merge(A, B, C, l);
  }
}

int array_sort_quicksort_partition(array * A, int l, int r) {
  int head = l - 1;

  // Randomly choose a pivot
  array_swap(A, l + rand() % (r - l + 1), r);

  // Everything except the final swap
  for (int i = l; i < r; i++) {
    if (A->data[i] < A->data[r]) {
      array_swap(A, ++head, i);
    }
  }

  // Do the final swap
  array_swap(A, ++head, r);
  return head;
}

int array_sort_quicksort(array * A, int l, int r) {
  if (l < r) {
    int mid = array_sort_quicksort_partition(A, l, r);
    array_sort_quicksort(A, l, mid - 1);
    array_sort_quicksort(A, mid + 1, r);
  }
}

int array_test_sorted(array * A) {
  for (int i = 1; i < A->size; i++)
    if (A->data[i] < A->data[i-1]) return 1;
  return 0;
}
