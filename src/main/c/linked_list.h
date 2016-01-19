#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct linked_list linked_list;

typedef struct linked_list{
  linked_list * prev;
  linked_list * next;
  uint32_t key;
} linked_list;

void linked_list_create(linked_list ** list);

void linked_list_insert(linked_list ** list, uint32_t key);
void linked_list_print(linked_list * list);
linked_list * linked_list_search(linked_list * list, uint32_t key);
void linked_list_delete(linked_list * element);
void linked_list_delete_all(linked_list * element);

#endif
