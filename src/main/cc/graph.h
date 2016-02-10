// Copyright 2016 Schuyler Eldridge

#ifndef SRC_MAIN_CC_GRAPH_H_
#define SRC_MAIN_CC_GRAPH_H_

#include <iostream>
#include <vector>

namespace algorithms {

template <class T> class Graph {
  std::vector< std::vector<T> *> adjacencyList;

 public:
  Graph();
  ~Graph();
  int AddNode();
};

template <class T> Graph<T>::Graph() {
}

template <class T> Graph<T>::~Graph() {
  for (size_t i = 0; i < adjacencyList.size(); ++i)
    delete(adjacencyList[i]);
}

}  // namespace algorithms

#endif  // SRC_MAIN_CC_GRAPH_H_
