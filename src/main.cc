#include <iostream>

#include "graph_algorithms/s21_graph_algorithms.h"

int main() {
  s21::Matrix matrix;
  s21::Graph my_graph;
  my_graph.LoadGraphFromFile("test_graph.txt");
  my_graph.AddEdge(0, 0, 11);
  my_graph.Draw();
  return 0;
}
