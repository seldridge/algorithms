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
  printf("0x%8p: 0x%8p <- (%4d) -> 0x%8p\n",
         list, list->prev, list->key, list->next);
  while (ptr->key != SENTINEL) {
    printf("0x%8p: 0x%8p <- (%4d) -> 0x%8p\n",
           ptr, ptr->prev, ptr->key, ptr->next);
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

void linked_list_map(linked_list * list, uint32_t (*function)(uint32_t)) {
  if (list->key == SENTINEL)
    return;
  list->key = function(list->key);
  return linked_list_map(list->next, function);
}

uint32_t linked_list_fold(linked_list * list, uint32_t acc, uint32_t (*function)(uint32_t, uint32_t)) {
  if (list->key == SENTINEL)
    return acc;
  return linked_list_fold(list->next, function(acc, list->key), function);
}
