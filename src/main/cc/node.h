// Copyright 2016 Schuyler Eldridge

#ifndef SRC_MAIN_CC_NODE_H_
#define SRC_MAIN_CC_NODE_H_

#include <vector>
#include <queue>
#include <iostream>

namespace algorithms {

template <class T> class Node {
 public:
  explicit Node(T value, unsigned int aryness = 2);
  Node(T value, Node<T> * parent, unsigned int aryness = 2);
  ~Node();
  T Get();
  T Set(T valueNew);
  int AppendChild(T valueChild);
  size_t NumberOfChildren();

  // Traversal Algorithms
  void TraverseInOrder(std::vector< Node<T> * > * vector);
  void TraversePreOrder(std::vector< Node<T> * > * vector);
  void TraversePostOrder(std::vector< Node<T> * > * vector);
  void TraverseLevelOrder(std::queue< Node<T>* > * queue,
                          std::vector< Node<T>* > * vector);

 private:
  unsigned int aryness_;
  T value_;
  Node<T> * parent_;
  std::vector< Node<T> * > children_;
};

template <class T> Node<T>::Node(T value, unsigned int aryness) {
  aryness_ = aryness;
  value_ = value;
  parent_ = nullptr;
}

template <class T> Node<T>::Node(T value, Node<T> * parent,
                                 unsigned int aryness) {
  aryness_ = aryness;
  value_ = value;
  parent_ = parent;
}

template <class T> Node<T>::~Node() {
  for (unsigned int i = 0; i < children_.size(); ++i)
    delete(children_[i]);
}

template <class T> T Node<T>::Get() {
  return value_;
}

template <class T> T Node<T>::Set(T valueNew) {
  T valueOld = value_;
  value_ = valueNew;
  return valueOld;
}

template <class T> int Node<T>::AppendChild(T valueChild) {
  if (children_.size() < aryness_) {
    children_.push_back(new Node<T>(valueChild));
  } else {
    size_t i = 0;
    while (!children_[i++]->AppendChild(valueChild)) {}
  }
  return 1;
}

template <class T> void Node<T>::TraversePreOrder(
    std::vector< Node<T> * > * vector) {
  vector->push_back(this);
  for (size_t i = 0; i < children_.size(); ++i)
    children_[i]->TraversePreOrder(vector);
}

template <class T> void Node<T>::TraverseInOrder(
    std::vector< Node<T> * > * vector) {
  if (aryness_ != 2) {
    this->TraversePreOrder();
  } else {
    size_t size = children_.size();
    if (size > 0) children_[2]->TraverseInOrder(vector);
    vector->push_back(this);
    if (size > 1) children_[1]->TraverseInOrder(vector);
  }
}

template <class T> void Node<T>::TraversePostOrder(
    std::vector< Node<T> * > * vector) {
  for (size_t i = 0; i < children_.size(); ++i)
    children_[i]->TraversePostOrder(vector);
  vector->push_back(this);
}

template <class T> void Node<T>::TraverseLevelOrder(
    std::queue< Node<T>* > * queue, std::vector< Node<T>* > * vector) {
  vector->push_back(this);
  for (size_t i = 0; i < children_.size(); ++i)
    queue->push(children_[i]);
}

template <class T> size_t Node<T>::NumberOfChildren() {
  return children_.size();
}

}  // namespace algorithms

#endif  // SRC_MAIN_CC_NODE_H_
