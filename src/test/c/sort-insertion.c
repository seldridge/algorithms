#include "array.h"

int main(int argc, char * argv[]) {
  array * A;
  array_create(&A, 10);

  // Array initialization
  srand(100);
  array_randomize(A);
  array_print(A);

  // Insertion sort
  array_sort_insertion(A);

  // Print sorted array
  array_print(A);

  // Test that the array is in fact sorted
  int return_val = array_test_sorted(A);
  if (return_val)
    printf("[ERROR] Insertion sort failed\n");
  else
    printf("[INFO] Insertion sort passed\n");

  // Clean everything up and exit
  array_destroy(&A);
  return return_val;
}
