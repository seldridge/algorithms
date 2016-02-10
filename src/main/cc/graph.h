// Copyright 2016 Schuyler Eldridge

#ifndef SRC_MAIN_CC_GRAPH_H_
#define SRC_MAIN_CC_GRAPH_H_

#include <iostream>
#include <vector>
#include <unordered_map>

namespace algorithms {

template <class T> class GraphNode {
  T value_;
  std::vector<T> connections_;

 public:
  explicit GraphNode(T value);
  ~GraphNode();
  T Get();
  bool HasConnection(T value);
  int AddConnection(T value);
  void PrintConnections();
 private:
  void Set(T value);
};

template <class T> GraphNode<T>::GraphNode(T value) {
  value_ = value;
}

template <class T> GraphNode<T>::~GraphNode() {
}

template <class T> T GraphNode<T>::Get() {
  return value_;
}

template <class T> bool GraphNode<T>::HasConnection(T value) {
  for (size_t i = 0; i < connections_.size(); ++i)
    if (connections_[i] == value)
      return true;
  return false;
}

template <class T> int GraphNode<T>::AddConnection(T value) {
  if (this->HasConnection(value))
    return -2;
  connections_.push_back(value);
  return 0;
}

template <class T> void GraphNode<T>::PrintConnections() {
  for (size_t i = 0; i < connections_.size(); ++i)
    std::cout << connections_[i] << " ";
  std::cout << std::endl;
}

template <class T> void GraphNode<T>::Set(T value) {
  value_ = value;
}

template <class T> class Graph {
  std::vector< GraphNode<T> * > adjacencyList_;

  typedef enum {
    kWhite,
    kGray,
    kBlack
  } color;

 public:
  Graph();
  ~Graph();
  int AddNode(T nodeValue);
  int AddConnection(T fromNode, T toNode);
  void Print();

  // Traversal
  void DepthFirstSearch(T startNode, std::vector<T> * bfsVector);
 private:
  GraphNode<T> * SearchForNode(T nodeValue);
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
  GraphNode<T> * newNode = new GraphNode<T>(nodeValue);
  adjacencyList_.push_back(newNode);
  return 0;
}

template <class T> int Graph<T>::AddConnection(T fromNode, T toNode) {
  GraphNode<T> * fromNodePointer = this->SearchForNode(fromNode);
  if (fromNodePointer == nullptr)
    return -1;
  return fromNodePointer->AddConnection(toNode);
}

template <class T> void Graph<T>::Print() {
  for (size_t i = 0; i < adjacencyList_.size(); ++i) {
    std::cout << adjacencyList_[i]->Get() << ": ";
    adjacencyList_[i]->PrintConnections();
  }
}

template <class T> void Graph<T>::DepthFirstSearch(T startNode,
                                                   std::vector<T> * bfsVector) {
  bfsVector->pushBack(startNode);
  GraphNode<T> * currentNode = this->SearchForNode(startNode);
}

template <class T> GraphNode<T> * Graph<T>::SearchForNode(T nodeValue) {
  for (size_t i = 0; i < adjacencyList_.size(); ++i)
    if (adjacencyList_[i]->Get() == nodeValue)
      return adjacencyList_[i];
  return nullptr;
}

}  // namespace algorithms

#endif  // SRC_MAIN_CC_GRAPH_H_
