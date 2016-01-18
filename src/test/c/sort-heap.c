#include "heap.h"
#include <time.h>

int main(int argc, char * argv[]) {
  array * H;
  heap_create(&H, 15);

  // Array initialization
  // srand(time(NULL));
  heap_randomize(H, 7);
  heap_print(H);

  printf("Is max heap? %d\n", heap_is_max_heap(H, 0));

  // Sort the heap
  heap_build_max_heap(H);
  heap_print(H);

  printf("Is now max heap? %d\n", heap_is_max_heap(H, 0));

  // Test that the sort worked
  int return_val = -1;

  // Clean everything up and exit
  heap_destroy(&H);
  return return_val;
}
