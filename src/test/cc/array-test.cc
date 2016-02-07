// Copyright 2016 Schuyler Eldridge

#include "src/main/cc/array.h"


bool TestInsertionSort() {
  algorithms::Array<int> a(10000);
  a.Randomize(0, 100);
  a.SortInsertion();
  return a.IsSorted();
}

bool TestMergeSort() {
  algorithms::Array<int> a(100000);
  a.Randomize(0, 100);
  a.SortMerge(0, a.GetLength() - 1);
  return a.IsSorted();
}

int main() {
  bool passed_all_tests = true;

  bool passed_test = TestInsertionSort();
  passed_all_tests &= passed_test;
  std::cout << (passed_test ? "[PASS]" : "[FAIL]") <<
    " InsertionSort" << std::endl;

  passed_test = TestMergeSort();
  passed_all_tests &= passed_test;
  std::cout << (passed_test ? "[PASS]" : "[FAIL]") <<
    " MergeSort" << std::endl;

  return !passed_all_tests;
}
