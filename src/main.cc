#include <iostream>

#include "graph_algorithms/s21_graph_algorithms.h"

int main() {
  s21::Graph my_graph;
  my_graph.LoadGraphFromFile("graph.txt");
  //   my_graph.add_edge(0, 0, 11);
  my_graph.Draw();
  s21::GraphAlgoritms ga;
  //   tsm::TsmResult res = ga.solveTravelingSalesmanProblem(my_graph);
  s21::tsm::TsmResult res = ga.naiveSolveTravelingSalesmanProblem(my_graph);

  std::cout << "distance: " << res.distance << std::endl;
  for (auto city : res.vertices) std::cout << city << ' ';
  std::cout << std::endl;

  return 0;
}
