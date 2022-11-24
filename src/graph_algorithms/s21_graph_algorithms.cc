#include "s21_graph_algorithms.h"

#include <iostream>

tsm::TsmResult GraphAlgoritms::solveTravelingSalesmanProblem(Graph& graph) {
  tsm::AntColony ac;
  return ac.FindOptimalPath(graph);
}