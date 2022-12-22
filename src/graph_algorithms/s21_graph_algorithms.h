#ifndef SRC_GRAPH_ALGORITHMS_S21_GRAPH_ALGORITHMS_H_
#define SRC_GRAPH_ALGORITHMS_S21_GRAPH_ALGORITHMS_H_

#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "../containers/s21_containers.h"
#include "../graph/s21_graph.h"
#include "ant_colony/ant_colony.h"

namespace s21 {

class GraphAlgoritms {
 public:
  tsm::TsmResult SolveTravelingSalesmanProblem(Graph& graph);
  tsm::TsmResult NaiveSolveTravelingSalesmanProblem(Graph& graph);
  tsm::TsmResult NearestNeighborSolveTravelingSalesmanProblem(Graph& graph);

  std::vector<int> depthFirstSearch(Graph& graph, int startVertex);
  std::vector<int> breadthFirstSearch(Graph& graph, int startVertex);
  int getShortestPathBetweenVertices(Graph& graph, int vertex1, int vertex2);

  Matrix getLeastSpanningTree(Graph& graph);

 private:
  const int kUndefined = -1;
  //   tsm::TsmResult naiveRecursion(Graph& graph, size_t visited_mask, int
  //   current_city, int start_city);
};

}  // namespace s21

#endif  // SRC_GRAPH_ALGORITHMS_S21_GRAPH_ALGORITHMS_H_
