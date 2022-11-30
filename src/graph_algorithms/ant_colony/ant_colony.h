#ifndef SRC_GRAPH_ALGORITHMS_ANT_COLONY_ANT_COLONY_H_
#define SRC_GRAPH_ALGORITHMS_ANT_COLONY_ANT_COLONY_H_

#include <cmath>
#include <random>
#include <vector>

#include "../../graph/s21_graph.h"

namespace s21 {

namespace tsm {

struct TsmResult {
  std::vector<int> vertices;
  double distance = 0;
};

class AntColony {
 public:
  TsmResult FindOptimalPath(const Graph& graph);

 private:
  struct Ant {
    std::vector<int> path;
    double distance;

    explicit Ant(int number_of_cities)
        : path(number_of_cities, -1), distance(0) {}
  };

  const double alpha = 1;
  const double beta = 1.;
  const double start_pheromone = 0.2;
  const int Q = 240;
  const double p = 0.64;

  const int iteration = 10;

  double Antraction(const Graph& graph,
                    const std::vector<std::vector<double>>& pheromone, int from,
                    int to);

  void SimulateAnts(const Graph& graph, std::vector<Ant>& ant_colony,
                    const std::vector<std::vector<double>>& pheromone);
  void UpdatePheromone(const std::vector<Ant>& ant_colony,
                       std::vector<std::vector<double>>& pheromone);
  void UpdateBestPath(const std::vector<Ant>& ant_colony, TsmResult& best_path);
};

}  // namespace tsm

}  // namespace s21

#endif  // SRC_GRAPH_ALGORITHMS_ANT_COLONY_ANT_COLONY_H_
