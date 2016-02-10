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
  void DepthFirstSearch(int depth);
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

template <class T> void GraphNode<T>::DepthFirstSearch(int depth) {
  std::cout << "[INFO] Visting node " << this->Get() << " (" <<
      this->GetColor() << ") at found depth " << this->GetDepth() <<
      " at current depth " << depth << std::endl;
  switch (this->GetColor()) {
    case kWhite:
      this->ChangeColor(kGray);
      this->SetDepth(depth);
      for (size_t i = 0; i < connections_.size(); ++i)
        connections_[i]->DepthFirstSearch(depth + 1);
      this->ChangeColor(kBlack);
      break;
    case kGray:
    case kBlack:
      if (this->GetDepth() > depth)
        this->SetDepth(depth);
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
  int DepthFirstSearch(T startNode);
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

template <class T> int Graph<T>::DepthFirstSearch(T startNode) {
  std::cout << "[INFO] Running DFS on node with value " << startNode <<
      std::endl;
  this->ResetColor();
  this->ResetDepth();
  GraphNode<T> * startNodePointer = this->SearchForNode(startNode);
  if (nullptr)
    return -1;
  startNodePointer->DepthFirstSearch(0);
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
