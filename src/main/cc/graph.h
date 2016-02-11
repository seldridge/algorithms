// Copyright 2016 Schuyler Eldridge

#ifndef SRC_MAIN_CC_GRAPH_H_
#define SRC_MAIN_CC_GRAPH_H_

#include <iostream>
#include <vector>
#include <queue>

namespace algorithms {

typedef enum {
  kWhite,
  kGray,
  kBlack
} kColor;

template <class T> void print_vector(
    std::vector< T *> * vector) {
  for (size_t i = 0; i < vector->size(); i++)
    std::cout << (*vector)[i]->Get() << " ";
  std::cout << std::endl;
}

template <class T> class GraphNode {
  T value_;
  int depth_;
  kColor color_;
  std::vector< GraphNode<T> * > connections_;

 public:
  explicit GraphNode(T value);
  ~GraphNode();
  T Get();
  int AddConnection(GraphNode<T> * nodePointer);
  void Print();
  kColor ChangeColor(kColor newColor);
  int ResetDepth();
  int GetDepth();
  kColor GetColor();

  // Traversal
  void DepthFirstSearch(int depth, std::vector< GraphNode<T> * > * vector);
  void BreadthFirstSearch(std::vector< GraphNode<T> *> * vector,
                          std::queue< GraphNode<T> *> * queue);

 private:
  int SetDepth(int newDepth);
  bool HasConnection(GraphNode<T> * nodePointer);
  int Set(T value);
};

template <class T> GraphNode<T>::GraphNode(T value) {
  value_ = value;
  color_ = kWhite;
  depth_ = -1;
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
    case kWhite: std::cout << "(W, "; break;
    case kGray:  std::cout << "(G, "; break;
    case kBlack: std::cout << "(B, ";
  }
  std::cout << depth_ << ") ";

  for (size_t i = 0; i < connections_.size(); ++i)
    std::cout << connections_[i]->Get() << " ";
  std::cout << std::endl;
}

template <class T> kColor GraphNode<T>::ChangeColor(kColor newColor) {
  kColor oldColor = color_;
  color_ = newColor;
  return oldColor;
}

template <class T> int GraphNode<T>::ResetDepth() {
  return this->SetDepth(-1);
}

template <class T> int GraphNode<T>::GetDepth() {
  return depth_;
}

template <class T> kColor GraphNode<T>::GetColor() {
  return color_;
}

template <class T> void GraphNode<T>::DepthFirstSearch(
    int depth, std::vector< GraphNode<T> * > * dfsVector) {
  switch (this->GetColor()) {
    case kWhite:
      dfsVector->push_back(this);
      this->ChangeColor(kGray);
      this->SetDepth(depth);
      for (size_t i = 0; i < connections_.size(); ++i)
        connections_[i]->DepthFirstSearch(depth + 1, dfsVector);
      this->ChangeColor(kBlack);
      break;
    case kGray:
    case kBlack:
      if (this->GetDepth() > depth)
        this->SetDepth(depth);
  }
}

template <class T> void GraphNode<T>::BreadthFirstSearch(
    std::vector< GraphNode<T> * > * bfsVector,
    std::queue< GraphNode<T> * > * bfsQueue) {
  switch (this->GetColor()) {
    case kWhite:
      bfsVector->push_back(this);
      this->ChangeColor(kGray);
      for (size_t i = 0; i < connections_.size(); ++i)
        bfsQueue->push(connections_[i]);
      break;
    case kGray:
    case kBlack:
      break;
  }
}

template <class T> int GraphNode<T>::Set(T value) {
  int oldValue = value_;
  value_ = value;
  return oldValue;
}

template <class T> int GraphNode<T>::SetDepth(int newDepth) {
  int oldDepth = depth_;
  depth_ = newDepth;
  return oldDepth;
}

template <class T> class Graph {
  std::vector< GraphNode<T> * > adjacencyList_;

 public:
  Graph();
  ~Graph();
  GraphNode<T> * AddNode(T nodeValue);
  int AddConnection(T fromNode, T toNode);
  void Print();

  // Traversal
  int DepthFirstSearch(T startNode, std::vector< GraphNode<T> *> * dfsVector);
  int BreadthFirstSearch(T startNode, std::vector< GraphNode<T> *> * dfsVector);
 private:
  void ResetColor(kColor newColor = kWhite);
  void ResetDepth();
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
    adjacencyList_[i]->ChangeColor(newColor);
}

template <class T> void Graph<T>::ResetDepth() {
  for (size_t i = 0; i < adjacencyList_.size(); ++i)
    adjacencyList_[i]->ResetDepth();
}

template <class T> int Graph<T>::DepthFirstSearch(
    T startNode, std::vector< GraphNode<T> *> * dfsVector) {
  this->ResetColor();
  this->ResetDepth();
  GraphNode<T> * startNodePointer = this->SearchForNode(startNode);
  if (nullptr)
    return -1;
  startNodePointer->DepthFirstSearch(0, dfsVector);
  return 0;
}

template <class T> int Graph<T>::BreadthFirstSearch(
    T startNode, std::vector< GraphNode<T> *> * bfsVector) {
  GraphNode<T> * startNodePointer = this->SearchForNode(startNode);
  if (startNodePointer == nullptr)
    return -1;

  this->ResetColor();
  std::queue< GraphNode<T> * > queue;
  queue.push(startNodePointer);
  while (!queue.empty()) {
    queue.front()->BreadthFirstSearch(bfsVector, &queue);
    queue.pop();
  }

  return 0;
}

template <class T> GraphNode<T> * Graph<T>::SearchForNode(T nodeValue) {
  for (size_t i = 0; i < adjacencyList_.size(); ++i)
    if (adjacencyList_[i]->Get() == nodeValue)
      return adjacencyList_[i];
  return nullptr;
}

}  // namespace algorithms

#endif  // SRC_MAIN_CC_GRAPH_H_
