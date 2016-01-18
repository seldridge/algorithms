#include "array.h"
#include <time.h>

int main(int argc, char * argv[]) {
  array * A, * B, * C;
  array_create(&A, 100000);
  array_create(&B, A->length / 2 + 1);
  array_create(&C, A->length - (A->length / 2) + 1);

  // Array initialization
  srand(time(NULL));
  array_randomize(&A, A->length);
  array_set(&B, (uint32_t) ((int32_t) -1), B->length);
  array_set(&C, (uint32_t) ((int32_t) -1), C->length);

  // Merge sort
  array_sort_mergesort(A, B, C, 0, A->size - 1);

  // Test that the array is in fact sorted
  int return_val = array_test_sorted(A);
  if (return_val)
    printf("[ERROR] Merge sort failed\n");
  else
    printf("[INFO] Merge sort passed\n");

  // Clean everything up and exit
  array_destroy(&A);
  array_destroy(&B);
  array_destroy(&C);
  return return_val;
}
