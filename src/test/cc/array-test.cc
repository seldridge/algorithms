// Copyright 2016 Schuyler Eldridge

#include "src/main/cc/array.h"

bool TestInsertionSort() {
  algorithms::Array<int> a(10000);
  a.Randomize(0, 100);
  a.SortInsertion();
  return a.IsSorted();
}

int main() {
  bool passed_all_tests = true;

  bool passed_insertion_sort = TestInsertionSort();
  passed_all_tests &= passed_insertion_sort;
  std::cout << (passed_insertion_sort ? "[PASS]" : "[FAIL]") <<
    " InsertionSort" << std::endl;

  return !passed_all_tests;
}
