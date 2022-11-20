#ifndef SRC_S21_GRAPH_AGORITHMS_H_
#define SRC_S21_GRAPH_AGORITHMS_H_

#include <iostream>
#include <string>
#include <vector>

#include "../graph/s21_graph.h"

struct TsmResult {
  std::vector<int> vertices;  // an array with the route you are looking for
  double distance;            // the length of this route
};

class GraphAlgoritms {
 public:
  TsmResult solveTravelingSalesmanProblem(Graph& graph);

 private:
};

#endif  // SRC_S21_GRAPH_AGORITHMS_H_