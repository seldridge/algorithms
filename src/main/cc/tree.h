// Copyright 2016 Schuyler Eldridge

#ifndef SRC_MAIN_CC_TREE_H_
#define SRC_MAIN_CC_TREE_H_

#include <iostream>
#include <queue>
#include <vector>

#include "src/main/cc/node.h"

namespace algorithms {

template <class T> class Tree {
 public:
  explicit Tree(unsigned int aryness = 2);
  ~Tree();
  void AddNode(T value);

  // Traversal Algorithms
  void TraversePreOrder(std::vector< Node<T> * > * vector);
  void TraverseInOrder(std::vector< Node<T> * > * vector);
  void TraversePostOrder(std::vector< Node<T> * > * vector);
  void TraverseLevelOrder(std::vector< Node<T> * > * vector);

 private:
  unsigned int aryness_;
  Node<T> * root_;
};

template <class T> Tree<T>::Tree(unsigned int aryness) {
  aryness_ = aryness;
  root_ = nullptr;
}

template <class T> Tree<T>::~Tree() {
  if (root_)
    delete(root_);
}

template <class T> void Tree<T>::AddNode(T nodeValue) {
  if (root_) {
    root_->AppendChild(nodeValue);
    return;
  }
  std::queue< Node<T> * > queue;
  queue.push(root_);

  root_ = new Node<T>(nodeValue);
}

template <class T> void Tree<T>::TraversePreOrder(
    std::vector< Node<T> * > * vector) {
  if (root_) root_->TraversePreOrder(vector);
}

template <class T> void Tree<T>::TraverseInOrder(
    std::vector< Node<T> * > * vector) {
  if (root_) root_->TraversePreOrder(vector);
}

template <class T> void Tree<T>::TraversePostOrder(
    std::vector< Node<T> * > * vector) {
  if (root_) root_->TraversePostOrder(vector);
}

template <class T> void Tree<T>::TraverseLevelOrder(
    std::vector< Node<T> * > * vector) {
  if (!root_) return;
  std::queue< Node<T>* > queue;
  queue.push(root_);
  while (!queue.empty()) {
    queue.front()->TraverseLevelOrder(&queue, vector);
    queue.pop();
  }
}

}  // namespace algorithms

#endif  // SRC_MAIN_CC_TREE_H_
