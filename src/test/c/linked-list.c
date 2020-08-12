#include "linked_list.h"

uint32_t addOne(uint32_t a) {
  return a + 1;
}

uint32_t add(uint32_t a, uint32_t b) {
  return a + b;
}

int main (int argc, char * argv[]) {
  linked_list * list;
  linked_list_create(&list);

  for (int i = 0; i < 10; i++)
    linked_list_insert(&list, i);

  linked_list_print(list);

  linked_list * ptr = linked_list_search(list, 2);
  printf("Found key %d at ptr 0x%8p\n", 2, ptr);

  linked_list_delete(ptr);

  linked_list_print(list->next);

  printf("Mapping all values by +1\n");
  linked_list_map(list->next, addOne);
  linked_list_print(list->next);

  printf("Accumulating all values via a fold\n");
  uint32_t acc = linked_list_fold(list->next, 0, add);
  printf("  Accumulated value: %d\n", acc);

  linked_list_destroy(list);

  return 0;
}
