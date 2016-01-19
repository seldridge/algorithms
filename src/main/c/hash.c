#include "hash.h"

void hash_create(hash ** h, uint32_t length) {
  (*h) = (hash *) malloc(sizeof(hash));
  (*h)->slot = (linked_list **) malloc(length * sizeof(linked_list));
  (*h)->length = length;
  for (int i = 0; i < (*h)->length; i++)
    linked_list_create(&(*h)->slot[i]);
}

void hash_destroy(hash ** h) {
  for (int i = 0; i < (*h)->length; i++)
    linked_list_destroy((*h)->slot[i]);
  free((*h)->slot);
  free(*h);
}

void hash_insert(hash ** h, uint32_t key) {
  uint32_t index = key % (*h)->length;
  linked_list_insert(&((*h)->slot[index]), key);
}

void hash_delete(hash ** h, uint32_t key) {
  uint32_t index = key % (*h)->length;
  linked_list * ptr = linked_list_search((*h)->slot[index], key);
  if (ptr->key != SENTINEL)
    linked_list_delete(ptr);
}

void hash_search(hash *h, uint32_t key) {

}

void hash_print(hash *h) {
  for (int i = 0; i < h->length; i++) {
    printf("hash index %d: ", i);
    linked_list_print(h->slot[i]);
  }
}
