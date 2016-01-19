#include "hash.h"

int main(int argv, char * argc[]) {
  hash * h;

  hash_create(&h, 10);

  hash_insert(&h, 100);
  hash_insert(&h, 200);
  hash_print(h);

  hash_delete(&h, 100);
  hash_print(h);

  hash_destroy(&h);

  return 0;
}
