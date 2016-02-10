// Copyright 2016 Schuyler Eldridge

#include "src/main/cc/tree.h"

template <class T> void print_vector(
    std::vector< algorithms::Node<T> *> * vector) {
  for (size_t i = 0; i < vector->size(); i++)
    std::cout << (*vector)[i]->Get() << std::endl;
}

int main() {
  algorithms::Tree<int> tree;
  std::vector< algorithms::Node<int>* > vector;

  for (int i = 0; i < 8; i++)
    tree.AddNode(i);

  std::cout << "Traverse post order" << std::endl;
  tree.TraversePostOrder(&vector);
  print_vector(&vector);

  vector.clear();
  std::cout << std::endl << "Traverse layer order" << std::endl;
  tree.TraverseLevelOrder(&vector);
  print_vector(&vector);

  return 0;
}
