#ifndef SRC_S21_GRAPH_AGORITHMS_H_
#define SRC_S21_GRAPH_AGORITHMS_H_

#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "../graph/s21_graph.h"
#include "tsm/ant_colony.h"

class GraphAlgoritms {
 public:
  tsm::TsmResult solveTravelingSalesmanProblem(Graph& graph);
  tsm::TsmResult naiveSolveTravelingSalesmanProblem(Graph& graph);
  tsm::TsmResult nearestNeighborSolveTravelingSalesmanProblem(Graph& graph);

 private:
  //   tsm::TsmResult naiveRecursion(Graph& graph, size_t visited_mask, int
  //   current_city, int start_city);
};

#endif  // SRC_S21_GRAPH_AGORITHMS_H_