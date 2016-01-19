#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct linked_list_element linked_list_element;

typedef struct linked_list_element{
  linked_list_element * prev;
  linked_list_element * next;
  uint32_t key;
} linked_list_element;

void linked_list_create(linked_list_element ** list);

void linked_list_insert(linked_list_element ** list, uint32_t key);
void linked_list_print(linked_list_element * list);
linked_list_element * linked_list_search(linked_list_element * list, uint32_t key);
void linked_list_delete(linked_list_element * element);
void linked_list_delete_all(linked_list_element * element);

#endif
