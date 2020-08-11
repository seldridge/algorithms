#include <stdio.h>

#include "tree.h"

void print_node(node * tree) {
  printf("%d\n", tree->data);
};

int main(int argc, char ** argv) {

  node * one;
  node * two;
  node * three;
  node * four;
  node * five;

  tree_create(&one, 1);
  tree_create(&two, 2);
  tree_create(&three, 3);
  tree_create(&four, 4);
  tree_create(&five, 5);

  tree_insert(two, one);
  tree_insert(two, three);
  tree_insert(two, four);
  tree_insert(two, five);

  printf("In-order traversal:\n");
  traverse_in_order(two, print_node);

  printf("Pre-order traversal:\n");
  traverse_pre_order(two, print_node);

  printf("Post-order traversal:\n");
  traverse_post_order(two, print_node);

  tree_destroy(&two);

  return 0;

};
