#include "s21_graph_algorithms.h"

TsmResult GraphAlgoritms::solveTravelingSalesmanProblem(Graph& graph) {
  S21Matrix feromone(graph.amount_of_vertices(), graph.amount_of_vertices());
  const int ant_count = graph.amount_of_vertices();
  const double alpha = 1;
  const double beta = 1;
  const int iteration = 10;
  const double start_feromone = 0.2;
  const int Q = 240;
  const double p = 0.64;

  for (int i = 0; i < graph.amount_of_vertices(); i++)
    for (int j = 0; j < graph.amount_of_vertices(); j++) {
      feromone(i, j) = start_feromone;
    }

  for (int i = 0; i < iteration; i++) {
    std::vector<TsmResult> ant_path(ant_count);

    for (int ant = 0; ant < ant_count; ant++) {

      for (int j = 0; j < graph.amount_of_vertices(); j++) {
      size_t city = ant;
        double atraction_sum = 0;

      }
    }
  }
}