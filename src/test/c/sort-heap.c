#include "heap.h"
#include <time.h>

int main(int argc, char * argv[]) {
  array * H;
  array_create(&H, 1);

  // Array initialization
  srand(time(NULL));
  array_randomize(&H, 100000);

  // Sort the heap
  heap_sort(H);

  // Test that the sort worked
  int return_val = array_test_sorted(H);
  if (return_val)
    printf("[ERROR] Heap sort failed\n");
  else
    printf("[INFO] Heap sort passed\n");

  // Clean everything up and exit
  array_destroy(&H);
  return return_val;
}
