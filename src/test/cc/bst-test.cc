// Copyright 2016 Schuyler Eldridge

#include "src/main/cc/tree.h"

int main() {
  algorithms::BinarySearchTree<int> bst;

  for (int i = 0; i < 8; i++)
    bst.AddNode(i);

  return 0;
}
