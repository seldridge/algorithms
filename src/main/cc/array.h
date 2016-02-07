// Copyright 2016 Schuyler Eldridge

#ifndef SRC_MAIN_CC_ARRAY_H_
#define SRC_MAIN_CC_ARRAY_H_

#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <random>

namespace algorithms {

template <class T>
class Array {
  T * data_;
  size_t length_;  // length of the array

 public:
  Array<T>(size_t length);
  ~Array();

  void Print();
  int Set(unsigned int index, T data);
  size_t GetLength();
  T Get(unsigned int index);
  int CopyToOther(Array * arrayDestination, unsigned int startSource,
                  unsigned int startDestination, unsigned int numberToCopy);
  void Randomize(int low, int high);
  int Swap(unsigned int firstIndex, unsigned int secondIndex);
  bool IsSorted();

  void SortInsertion();
  void SortMerge(int startIndex, int stopIndex, Array * tmpArray = NULL);
  void SortHeap();
  void SortQuick();

 private:
  void Merge(int startLeft, int stopLeft, int startRight, int stopRight,
             Array * scratchArray);
};

template <class T>
Array<T>::Array(size_t length) {
  data_ = NULL;
  if (length)
    data_ = reinterpret_cast<T *>(malloc(length * sizeof(T)));
  length_ = length;
}

template <class T>
Array<T>::~Array() {
  if (data_ != NULL)
    free(data_);
}

template <class T>
void Array<T>::Print() {
  for (unsigned int i = 0; i < length_; ++i) {
    std::cout << i << ": " << data_[i] << std::endl;
  }
  std::cout << std::endl;
}

template <class T>
int Array<T>::Set(unsigned int index, T data) {
  int returnVal = 0;
  if (index >= length_) {
    if (data_ != NULL)
      data_ = reinterpret_cast<T *>(realloc(data_, index * 2 * sizeof(T)));
    else
      data_ = reinterpret_cast<T *>(malloc(index * 2 * sizeof(T)));
    length_ = index * 2;
    returnVal = 1;
  }

  data_[index] = data;
  return returnVal;
}

template <class T>
size_t Array<T>::GetLength() {
  return length_;
}

template <class T>
T Array<T>::Get(unsigned int index) {
  if (index >= length_)
    return 0;
  return data_[index];
}

template <class T>
int Array<T>::CopyToOther(Array * arrayDestination, unsigned int startSource,
                unsigned int startDestination, unsigned int numberToCopy) {
  // The source is THIS array
  if (startSource + numberToCopy > length_)
    return -1;

  for (unsigned int i = 0; i < numberToCopy; ++i)
    arrayDestination->Set(startDestination + i, data_[startSource + i]);
  return 0;
}

template <class T>
void Array<T>::Randomize(int low, int high) {
  unsigned int seed = time(NULL);
  for (unsigned int i = 0; i < length_; ++i)
    data_[i] = (rand_r(&seed) % (high - low)) + low;
}

template <class T>
int Array<T>::Swap(unsigned int firstIndex, unsigned int secondIndex) {
  if (firstIndex > length_ || secondIndex > length_)
    return -1;
  T tmp = data_[firstIndex];
  this->Set(firstIndex, data_[secondIndex]);
  this->Set(secondIndex, tmp);
  return 0;
}

template <class T>
bool Array<T>::IsSorted() {
  for (unsigned int i = 1; i < length_; i++) {
    if (data_[i] < data_[i-1])
      return false;
  }
  return true;
}

template <class T>
void Array<T>::SortInsertion() {
  for (unsigned int i = 1; i < length_; ++i) {
    int index_swap = i;
    while (index_swap > 0 &&
           this->Get(index_swap) < this->Get(index_swap - 1)) {
      this->Swap(index_swap, index_swap - 1);
      --index_swap;
    }
  }
}

template <class T>
void Array<T>::SortMerge(int startIndex, int stopIndex, Array * scratchArray) {
  // Deal with the case of an unallocated scratchArray
  if (scratchArray == NULL)
    scratchArray = new Array<T>(this->GetLength());

  if (stopIndex != startIndex) {
    int mid_point = (stopIndex - startIndex) / 2 + startIndex;
    this->SortMerge(startIndex, mid_point, scratchArray);
    this->SortMerge(mid_point + 1, stopIndex, scratchArray);
    this->Merge(startIndex, mid_point, mid_point + 1, stopIndex, scratchArray);
  }
}

template <class T>
void Array<T>::Merge(int startLeft, int stopLeft, int startRight, int stopRight,
                     Array * scratchArray) {
  int leftIndex = startLeft, rightIndex = startRight;
  for (int scratchIndex = startLeft; scratchIndex < stopRight + 1;
       ++scratchIndex) {
    if (leftIndex == stopLeft + 1)
      scratchArray->Set(scratchIndex, this->Get(rightIndex++));
    else if (rightIndex == stopRight + 1)
      scratchArray->Set(scratchIndex, this->Get(leftIndex++));
    else if (this->Get(leftIndex) < this->Get(rightIndex))
      scratchArray->Set(scratchIndex, this->Get(leftIndex++));
    else
      scratchArray->Set(scratchIndex, this->Get(rightIndex++));
  }
  scratchArray->CopyToOther(this, startLeft, startLeft, stopRight - startLeft + 1);
}

}  // namespace algorithms

#endif  // SRC_MAIN_CC_ARRAY_H_
