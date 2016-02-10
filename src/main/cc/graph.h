// Copyright 2016 Schuyler Eldridge

#ifndef SRC_MAIN_CC_GRAPH_H_
#define SRC_MAIN_CC_GRAPH_H_

#include <iostream>
#include <vector>
#include <unordered_map>

namespace algorithms {

typedef enum {
  kWhite,
  kGray,
  kBlack
} kColor;

template <class T> class GraphNode {
  T value_;
  kColor color_;
  std::vector< GraphNode<T> * > connections_;

 public:
  explicit GraphNode(T value);
  ~GraphNode();
  T Get();
  int AddConnection(GraphNode<T> * nodePointer);
  void Print();
  void ChangeColor(kColor newColor);
 private:
  bool HasConnection(GraphNode<T> * nodePointer);
  void Set(T value);
};

template <class T> GraphNode<T>::GraphNode(T value) {
  value_ = value;
  color_ = kWhite;
}

template <class T> GraphNode<T>::~GraphNode() {
}

template <class T> T GraphNode<T>::Get() {
  return value_;
}

template <class T> bool GraphNode<T>::HasConnection(
    GraphNode<T> * nodePointer) {
  for (size_t i = 0; i < connections_.size(); ++i)
    if (connections_[i] == nodePointer)
      return true;
  return false;
}

template <class T> int GraphNode<T>::AddConnection(GraphNode<T> * nodePointer) {
  if (this->HasConnection(nodePointer))
    return -2;
  connections_.push_back(nodePointer);
  return 0;
}

template <class T> void GraphNode<T>::Print() {
  switch (color_) {
    case kWhite: std::cout << "(W) "; break;
    case kGray:  std::cout << "(G) "; break;
    case kBlack: std::cout << "(B) ";
  }

  for (size_t i = 0; i < connections_.size(); ++i)
    std::cout << connections_[i]->Get() << " ";
  std::cout << std::endl;
}

template <class T> void GraphNode<T>::ChangeColor(kColor newColor) {
  color_ = newColor;
}

template <class T> void GraphNode<T>::Set(T value) {
  value_ = value;
}

template <class T> class Graph {
  std::vector< GraphNode<T> * > adjacencyList_;

 public:
  Graph();
  ~Graph();
  GraphNode<T> * AddNode(T nodeValue);
  int AddConnection(T fromNode, T toNode);
  void Print();
  void ResetColor(kColor newColor = kWhite);

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

template <class T> GraphNode<T> * Graph<T>::AddNode(T nodeValue) {
  GraphNode<T> * newNode = this->SearchForNode(nodeValue);
  if (this->SearchForNode(nodeValue) == nullptr) {
    newNode = new GraphNode<T>(nodeValue);
    adjacencyList_.push_back(newNode);
  }
  return newNode;
}

template <class T> int Graph<T>::AddConnection(T fromNode, T toNode) {
  GraphNode<T> * fromNodePointer = this->SearchForNode(fromNode);
  GraphNode<T> * toNodePointer = this->SearchForNode(toNode);
  if (fromNodePointer == nullptr)
    fromNodePointer = this->AddNode(fromNode);
  if (toNodePointer == nullptr)
    toNodePointer = this->AddNode(toNode);
  return fromNodePointer->AddConnection(toNodePointer);
}

template <class T> void Graph<T>::Print() {
  for (size_t i = 0; i < adjacencyList_.size(); ++i) {
    std::cout << adjacencyList_[i]->Get() << ": ";
    adjacencyList_[i]->Print();
  }
}

template <class T> void Graph<T>::ResetColor(kColor newColor) {
  for (size_t i = 0; i < adjacencyList_.size(); ++i)
    adjacencyList_[i]->SetColor(newColor);
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
