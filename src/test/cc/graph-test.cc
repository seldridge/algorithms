// Copyright 2016 Schuyler Eldridge

#include "src/main/cc/graph.h"

int main() {
  algorithms::Graph<int> graph;

  // graph.AddNode(0);
  // graph.AddNode(1);
  // graph.AddNode(2);

  graph.AddConnection(0, 1);
  graph.AddConnection(0, 2);
  graph.AddConnection(1, 2);
  graph.AddConnection(2, 0);

  graph.Print();

  return 0;
}
