#include "linked_list.h"

int main (int argc, char * argv[]) {
  linked_list * list;
  linked_list_create(&list);

  for (int i = 0; i < 10; i++)
    linked_list_insert(&list, i);

  linked_list_print(list);

  linked_list * ptr = linked_list_search(list, 2);
  printf("Found key %d at ptr 0x%08lx\n", 2, ptr);

  linked_list_delete(ptr);

  linked_list_print(list);

  linked_list_delete_all(list);

  return 0;
}
