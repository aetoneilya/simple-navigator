#include <iostream>

#include "graph_algorithms/s21_graph_algorithms.h"

int main() {
  Graph my_graph;
  my_graph.loadGraphFromFile("graph.txt");
  //   my_graph.add_edge(0, 0, 11);
  my_graph.draw();
  GraphAlgoritms ga;
  tsm::TsmResult res = ga.solveTravelingSalesmanProblem(my_graph);

  std::cout << "distance: " << res.distance << std::endl;
  for (auto city : res.vertices) std::cout << city << ' ';
  std::cout << std::endl;

  return 0;
}