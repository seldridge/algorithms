// Copyright 2016 Schuyler Eldridge

#include "src/main/cc/array.h"

bool TestInsertionSort() {
  algorithms::Array<int> a(10000);

  a.Randomize(0, 100);
  a.SortInsertion();
  return a.IsSorted();
}

int main() {
  std::cout << (TestInsertionSort() ? "[PASS]" : "[FAIL]") <<
    " InsertionSort" << std::endl;

  return 0;
}
