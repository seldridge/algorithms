// Copyright 2016 Schuyler Eldridge

#include "src/main/cc/graph.h"

int main() {
  algorithms::Graph<int> graph;

  graph.AddConnection(0, 1);
  graph.AddConnection(0, 2);
  graph.AddConnection(1, 2);
  graph.AddConnection(1, 0);

  graph.Print();

  std::vector< algorithms::GraphNode<int> *> searchVector;
  graph.DepthFirstSearch(1, &searchVector);

  std::cout << "DFS: ";
  print_vector(&searchVector);
  graph.Print();


  searchVector.clear();
  graph.BreadthFirstSearch(1, &searchVector);
  std::cout << "BFS: ";
  print_vector(&searchVector);
  graph.Print();

  return 0;
}
