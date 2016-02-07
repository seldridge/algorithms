#include "linked_list.h"

void linked_list_create(linked_list ** list) {
  (*list) = (linked_list *) malloc(sizeof(linked_list));
  (*list)->next = (*list);
  (*list)->prev = (*list);
  (*list)->key = SENTINEL;
}

void linked_list_destroy(linked_list * element) {
  while (element->next != element)
    linked_list_delete(element->next);
  linked_list_delete(element);
}

void linked_list_insert(linked_list ** list, uint32_t key) {
  linked_list * ptr = (*list)->next;
  (*list)->next = (linked_list *) malloc(sizeof(linked_list));
  (*list)->next->prev = *list;
  (*list)->next->next = ptr;
  ptr->prev = (*list)->next;
  (*list)->next->key = key;
  if ((*list)->prev == *list)
    (*list)->prev = (*list)->next;
}

void linked_list_delete(linked_list * element) {
  element->prev->next = element->next;
  element->next->prev = element->prev;
  free(element);
}

void linked_list_print(linked_list * list) {
  linked_list * ptr = list->next;
  printf("0x%08lx: 0x%08lx <- (%4d) -> 0x%08lx\n",
         (uint64_t) list, (uint64_t) list->prev, list->key, (uint64_t) list->next);
  while (ptr->key != SENTINEL) {
    printf("0x%08lx: 0x%08lx <- (%4d) -> 0x%08lx\n",
           (uint64_t) ptr, (uint64_t) ptr->prev, ptr->key, (uint64_t) ptr->next);
    ptr = ptr->next;
  }
}

linked_list * linked_list_search(linked_list * list, uint32_t key) {
  linked_list * ptr = list->next;
  while (ptr->key != SENTINEL && ptr->key != key) {
    ptr = ptr->next;
  }
  return ptr;
}
