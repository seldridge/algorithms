#include "heap.h"
#include <time.h>

int main(int argc, char * argv[]) {
  array * H;
  array_create(&H, 1);

  // Array initialization
  srand(time(NULL));
  // array_randomize(H, 7);
  for (int i = 0; i < 7; i++) {
    heap_insert(&H, i);
  }

  // Sort the heap
  heap_build_max_heap(H);
  heap_print(H);

  printf("Is now max heap? %d\n", heap_is_max_heap(H, 0));

  // Test that the sort worked
  int return_val = -1;

  // Clean everything up and exit
  array_destroy(&H);
  return return_val;
}
