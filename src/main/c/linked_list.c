#include "linked_list.h"

#define SENTINEL (uint32_t) (int32_t) -1

void linked_list_create(linked_list_element ** list) {
  (*list) = (linked_list_element *) malloc(sizeof(linked_list_element));
  (*list)->next = (*list);
  (*list)->prev = (*list);
  (*list)->key = SENTINEL;
}

void linked_list_insert(linked_list_element ** list, uint32_t key) {
  linked_list_element * ptr = (*list)->next;
  (*list)->next = (linked_list_element *) malloc(sizeof(linked_list_element));
  (*list)->next->prev = *list;
  (*list)->next->next = ptr;
  ptr->prev = (*list)->next;
  (*list)->next->key = key;
  if ((*list)->prev == *list)
    (*list)->prev = (*list)->next;
}

void linked_list_delete(linked_list_element * element) {
  element->prev->next = element->next;
  element->next->prev = element->prev;
  free(element);
}

void linked_list_delete_all(linked_list_element * element) {
  while (element->next != element)
    linked_list_delete(element->next);
  linked_list_delete(element);
}

void linked_list_print(linked_list_element * list) {
  linked_list_element * ptr = list->next;
  printf("0x%08lx: 0x%08lx <- (%4d) -> 0x%08lx\n", list, list->prev, list->key, list->next);
  while (ptr->key != SENTINEL) {
    printf("0x%08lx: 0x%08lx <- (%4d) -> 0x%08lx\n", ptr, ptr->prev, ptr->key, ptr->next);
    ptr = ptr->next;
  }
}

linked_list_element * linked_list_search(linked_list_element * list, uint32_t key) {
  linked_list_element * ptr = list->next;
  while (ptr != NULL && ptr->key != key) {
    ptr = ptr->next;
  }
  return ptr;
}
