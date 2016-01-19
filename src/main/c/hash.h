#ifndef __HASH_H__
#define __HASH_H__

#include "linked_list.h"

typedef struct {
  linked_list ** slot;
  uint32_t length;
} hash;

void hash_create(hash ** h, uint32_t length);
void hash_destroy(hash ** h);

void hash_insert(hash ** h, uint32_t key);
void hash_delete(hash ** h, uint32_t key);

void hash_print(hash * h);

#endif
