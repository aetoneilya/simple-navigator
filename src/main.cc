#include <iostream>

#include "graph_algorithms/s21_graph_algorithms.h"

int main() {
  Graph my_graph;
  my_graph.loadGraphFromFile("test_graph.txt");
  my_graph.add_edge(0, 0, 11);
  my_graph.draw();
  return 0;
}