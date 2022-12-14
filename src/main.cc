#include <iostream>

#include "graph_algorithms/s21_graph_algorithms.h"

int main() {
  s21::Graph my_graph;
  my_graph.LoadGraphFromFile("test_graph.txt");
  //   my_graph.add_edge(0, 0, 11);
  my_graph.Draw();
  std::cout << std::endl;
  s21::GraphAlgoritms ga;
  //   tsm::TsmResult res = ga.SolveTravelingSalesmanProblem(my_graph);
  // std::vector<int> res = ga.depthFirstSearch(my_graph, 1);
  // for (auto vertice : res) std::cout << vertice << ' ';
  // std::cout << std::endl;

  // res = ga.breadthFirstSearch(my_graph, 1);
  // for (auto vertice : res) std::cout << vertice << ' ';
  // std::cout << std::endl;
  int result = ga.getShortestPathBetweenVertices(my_graph, 1, 4);
  std::cout << result << "\n";

  return 0;
}
