#include "array.h"
#include <time.h>

int main(int argc, char * argv[]) {
  array * A;
  array_create(&A, 100000);

  // Array initialization
  srand(time(NULL));
  array_randomize(A, A->length);

  // Insertion sort
  array_sort_insertion(A);

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
