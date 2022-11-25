#include "s21_graph_algorithms.h"

#include <iostream>

tsm::TsmResult GraphAlgoritms::solveTravelingSalesmanProblem(Graph& graph) {
  tsm::AntColony ac;
  return ac.FindOptimalPath(graph);
}

tsm::TsmResult GraphAlgoritms::naiveSolveTravelingSalesmanProblem(
    Graph& graph) {
  size_t number_of_cities = graph.amount_of_vertices();

  tsm::TsmResult best_result;
  best_result.distance = INFINITY;

  tsm::TsmResult temp;
  for (size_t i = 0; i < number_of_cities; i++) {
    temp.vertices.push_back(i);
  }

  do {
    temp.distance = 0;
    for (size_t i = 0; i < number_of_cities; i++)
      temp.distance += graph.has_edge(
          temp.vertices[i], temp.vertices[(i + 1) % number_of_cities]);

    if (temp.distance < best_result.distance) best_result = temp;

  } while (std::next_permutation(temp.vertices.begin(), temp.vertices.end()));

  return best_result;
}

tsm::TsmResult nearestNeighborSolveTravelingSalesmanProblem(Graph& graph) {
  tsm::TsmResult best_result;
  best_result.distance = INFINITY;

  size_t number_of_cities = graph.amount_of_vertices();

  for (int i = 0; i < number_of_cities; i++) {
    tsm::TsmResult temp;
    temp.vertices.resize(number_of_cities);
    temp.vertices[0] = i;

    std::vector<int> visited(number_of_cities);

    for (int j = 1; j < number_of_cities; j++) {
      int nearest = -1;  // find nearest city to graph[j-1]
      temp.vertices[j] = nearest;
      temp.distance += graph.has_edge(temp.vertices[j - 1], temp.vertices[j]);
    }

    temp.distance +=
        graph.has_edge(temp.vertices.front(), temp.vertices.back());

    if (temp.distance < best_result.distance) best_result = temp;
  }

  return best_result;
}