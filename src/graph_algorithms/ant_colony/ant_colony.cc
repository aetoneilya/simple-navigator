#include "ant_colony.h"

#include <iostream>

namespace s21 {

namespace tsm {

TsmResult AntColony::FindOptimalPath(const Graph& graph) {
  const int number_of_cities = (int)graph.AmountOfVertices();
  std::vector<std::vector<double>> pheromone(number_of_cities);

  for (int i = 0; i < number_of_cities; i++)
    for (int j = 0; j < number_of_cities; j++) {
      pheromone[i].push_back(start_pheromone);
    }

  TsmResult best_path;
  best_path.distance = INFINITY;

  Ant regular_ant((int)number_of_cities);

  for (int i = 0; i < iteration; i++) {
    std::vector<Ant> ant_colony(number_of_cities, regular_ant);
    SimulateAnts(graph, ant_colony, pheromone);
    UpdatePheromone(ant_colony, pheromone);
    UpdateBestPath(ant_colony, best_path);
  }

  return best_path;
}

void AntColony::SimulateAnts(
    const Graph& graph, std::vector<Ant>& ant_colony,
    const std::vector<std::vector<double>>& pheromone) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);

  const int number_of_cities = (int)graph.AmountOfVertices();
  int ant_num = 0;

  for (Ant& ant : ant_colony) {
    std::vector<bool> visited(number_of_cities, false);
    int current_city = ant_num % number_of_cities;
    ant.path[0] = current_city;

    for (int step = 1; step <= number_of_cities; step++) {
      visited[current_city] = true;
      double atraction_sum = 0;
      std::vector<double> cities_attraction(number_of_cities);

      // build attraction map
      for (int city_to = 0; city_to < number_of_cities; city_to++) {
        //! very dangerous part of algorithm undefined behaviour
        cities_attraction[city_to] =
            !visited[city_to]
                ? Antraction(graph, pheromone, current_city, city_to)
                : 0;
        // SAFE variant
        // cities_attraction[city_to] =
        //     graph.has_edge(current_city, city_to) != 0 && !visited[city_to]
        //         ? antraction(graph, pheromone, current_city, city_to)
        //         : 0;

        atraction_sum += cities_attraction[city_to];
      }

      //   std::cout << "visited: ";
      //   for (auto a : visited) {
      //     std::cout << a << ' ';
      //   }
      //   std::cout << "\t";

      //   std::cout << "atrcn og: ";
      //   for (auto a : cities_attraction) {
      //     std::cout << a << ' ';
      //   }
      //   std::cout << "\t";

      cities_attraction[0] = cities_attraction[0] / atraction_sum;
      for (int c = 1; c < number_of_cities; c++)
        cities_attraction[c] =
            cities_attraction[c - 1] + cities_attraction[c] / atraction_sum;

      double ant_choise = dis(rd);
      int city_to = 0;
      while (ant_choise > cities_attraction[city_to]) city_to++;

      //   std::cout << "atrcn ";
      //   for (auto a : cities_attraction) {
      //     std::cout << a << ' ';
      //   }
      //   std::cout << std::endl;

      ant.distance += graph(current_city, city_to);

      ant.path[step] = city_to;
      current_city = city_to;
    }
    ant.distance += graph(ant.path.back(), ant.path.front());
    ant_num++;

    // PrintAnt(ant);
  }
}

void AntColony::UpdatePheromone(const std::vector<Ant>& ant_colony,
                                std::vector<std::vector<double>>& pheromone) {
  for (size_t i = 0; i < pheromone.size(); i++)
    for (size_t j = 0; j < pheromone[i].size(); j++)
      pheromone[i][j] = (1 - p) * pheromone[i][j];

  for (Ant ant : ant_colony) {
    double pheromone_add = Q / ant.distance;

    for (size_t city = 1; city < ant.path.size(); city++) {
      int to = ant.path[city];
      int from = ant.path[city - 1];
      pheromone[from][to] = pheromone_add;
      pheromone[to][from] = pheromone[from][to];
    }
  }
}

void AntColony::UpdateBestPath(const std::vector<Ant>& ant_colony,
                               TsmResult& best_path) {
  for (Ant ant : ant_colony)
    if (ant.distance < best_path.distance) {
      best_path.vertices = ant.path;
      best_path.distance = ant.distance;
      //   PrintAnt(ant);
    }
}

double AntColony::Antraction(const Graph& graph,
                             const std::vector<std::vector<double>>& pheromone,
                             int from, int to) {
  double proximity = 1.0 / (double)graph(from, to);
  return ((pow(pheromone[from][to], alpha) * pow((proximity), beta)));
}

}  // namespace tsm

}  // namespace s21
