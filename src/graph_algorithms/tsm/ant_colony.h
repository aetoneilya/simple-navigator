#ifndef SRC_S21_GRAPH_AGORITHMS_TSM_ANT_COLONY_H_
#define SRC_S21_GRAPH_AGORITHMS_TSM_ANT_COLONY_H_

#include <cmath>
#include <random>
#include <vector>

#include "../../graph/s21_graph.h"

namespace tsm {
struct TsmResult {
  std::vector<int> vertices;
  double distance = 0;
};

class AntColony {
 public:
  TsmResult FindOptimalPath(Graph& graph);

 private:
  struct Ant {
    std::vector<int> path;
    double distance;

    Ant(int number_of_cities) : path(number_of_cities, -1), distance(0) {}
  };

  void PrintAnt(Ant ant) {
    std::cout << "ant distance:  " << ant.distance << "\tpath: ";
    for (auto ax : ant.path) std::cout << ax << ' ';
    std::cout << std::endl;
  }

  const double alpha = 1;
  const double beta = 1.;
  const double start_pheromone = 0.2;
  const int Q = 240;
  const double p = 0.64;

  const int iteration = 10;

  double antraction(Graph& graph,
                    const std::vector<std::vector<double>>& pheromone, int from,
                    int to) {
    double proximity = 1.0 / (double)graph.has_edge(from, to);
    return ((pow(pheromone[from][to], alpha) * pow((proximity), beta)));
  }

  void simulateAnts(Graph& graph, std::vector<Ant>& ant_colony,
                    const std::vector<std::vector<double>>& pheromone);
  void updatePheromone(std::vector<Ant>& ant_colony,
                       std::vector<std::vector<double>>& pheromone);
  void updateBestPath(std::vector<Ant>& ant_colony, TsmResult& best_path);
};

}  // namespace tsm

#endif  // SRC_S21_GRAPH_AGORITHMS_TSM_ANT_COLONY_H_