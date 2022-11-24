#ifndef SRC_S21_GRAPH_AGORITHMS_H_
#define SRC_S21_GRAPH_AGORITHMS_H_


#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "../graph/s21_graph.h"
#include "tsm/ant_colony.h"

class GraphAlgoritms {
 public:
  tsm::TsmResult solveTravelingSalesmanProblem(Graph& graph);

 private:
};

#endif  // SRC_S21_GRAPH_AGORITHMS_H_