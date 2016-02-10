// Copyright 2016 Schuyler Eldridge

#ifndef SRC_MAIN_CC_GRAPH_H_
#define SRC_MAIN_CC_GRAPH_H_

#include <iostream>
#include <vector>

namespace algorithms {

template <class T> class Graph {
  std::vector< std::vector<T> *> adjacencyList_;

 public:
  Graph();
  ~Graph();
  int AddNode(T nodeValue);
  int AddConnection(T fromNode, T toNode);
  void Print();
 private:
  std::vector<T> * SearchForNode(T nodeValue);
};

template <class T> Graph<T>::Graph() {
}

template <class T> Graph<T>::~Graph() {
  for (size_t i = 0; i < adjacencyList_.size(); ++i)
    delete(adjacencyList_[i]);
}

template <class T> int Graph<T>::AddNode(T nodeValue) {
  if (this->SearchForNode(nodeValue) != nullptr)
    return 1;
  std::vector<T> * newNode = new std::vector<T>;
  newNode->push_back(nodeValue);
  adjacencyList_.push_back(newNode);
  return 0;
}

template <class T> int Graph<T>::AddConnection(T fromNode, T toNode) {
  std::vector<T> * fromNodePointer = this->SearchForNode(fromNode);
  if (fromNodePointer == nullptr)
    return 1;
  for (size_t i = 0; i < fromNodePointer->size(); ++i) {
    if ((*fromNodePointer)[i] == toNode)
      return 2;
  }
  fromNodePointer->push_back(toNode);
  return 0;
}

template <class T> std::vector<T> * Graph<T>::SearchForNode(T nodeValue) {
  for (size_t i = 0; i < adjacencyList_.size(); ++i)
    if ((*adjacencyList_[i])[0] == nodeValue)
      return adjacencyList_[i];
  return nullptr;
}

template <class T> void Graph<T>::Print() {
  for (size_t i = 0; i < adjacencyList_.size(); ++i) {
    std::cout << (*adjacencyList_[i])[0] << ": ";
    for (size_t j = 1; j < adjacencyList_[i]->size(); ++j) {
      std::cout << (*adjacencyList_[i])[j] << " ";
    }
    std::cout << std::endl;
  }
}

}  // namespace algorithms

#endif  // SRC_MAIN_CC_GRAPH_H_
