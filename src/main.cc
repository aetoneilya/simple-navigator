#include <chrono>  // NOLINT [build/c++11]
#include <iostream>
#include <string>

#include "graph_algorithms/s21_graph_algorithms.h"

namespace s21 {

enum Mode {
  kLoadGraphFromFile = 1,
  kBFS,
  kDFS,
  kShortestPathBetweenTwoArbitraryVertices,
  kShortestPathsBetweenAllPairsOfVertices,
  kMinimumSpanningTree,
  kTravelingSalesmanProblem,
  kTSPAnalyze,
  kExit
};

}  // namespace s21

int main() {
  s21::Mode mode;
  s21::Graph graph;
  s21::GraphAlgoritms algs;
  std::vector<int> vector;
  std::string filename;
  s21::Matrix matrix;
  std::size_t vertex1, vertex2, n;
  int integer;
  s21::tsm::TsmResult tsm_result;
  std::chrono::time_point<std::chrono::high_resolution_clock> start_timestamp,
      end_timestamp;
  std::chrono::duration<double> tsp1, tsp2, tsp3;

  do {
    std::cout
        << "\n1) Load graph from file\n"
           "2) Breadth First Search (BFS)\n"
           "3) Depth First Search (DFS)\n"
           "4) Shortest path between two arbitrary vertices\n"
           "5) Shortest paths between all pairs of vertices\n"
           "6) Minimum spanning tree\n"
           "7) Traveling salesman problem\n"
           "8) Analyze different solutions of traveling salesman problem\n"
           "9) Exit\n"
           "\nSelect mode (enter number only): ";
    int selected_mode;
    std::cin >> selected_mode;

    mode = static_cast<s21::Mode>(selected_mode);
    switch (mode) {
      case s21::Mode::kLoadGraphFromFile:
        std::cout << "\nEnter graph filename: ";
        std::cin >> filename;
        try {
          graph.LoadGraphFromFile(filename);
        } catch (const std::exception& e) {
          std::cout
              << "\nPlease, select mode again and enter correct filename!\n";
        }
        break;
      case s21::Mode::kBFS:
        if (graph.AmountOfVertices()) {
          std::cout << "Enter start vertex (from 1 to "
                    << graph.AmountOfVertices() << "): ";
          std::cin >> vertex1;
          if (vertex1 >= 1 && vertex1 <= graph.AmountOfVertices()) {
            vector = algs.breadthFirstSearch(graph, static_cast<int>(vertex1));
            for (std::size_t i = 0; i < vector.size() - 1; ++i)
              std::cout << vector[i] << " ";
            std::cout << vector.back() << "\n";
          } else {
            std::cout << "\nSelect the correct vertex!\n";
          }
        } else {
          std::cout << "\nFirstly load the correct graph!\n";
        }
        break;
      case s21::Mode::kDFS:
        if (graph.AmountOfVertices()) {
          std::cout << "Enter start vertex (from 1 to "
                    << graph.AmountOfVertices() << "): ";
          std::cin >> vertex1;
          if (vertex1 >= 1 && vertex1 <= graph.AmountOfVertices()) {
            vector = algs.depthFirstSearch(graph, static_cast<int>(vertex1));
            for (std::size_t i = 0; i < vector.size() - 1; ++i)
              std::cout << vector[i] << " ";
            std::cout << vector.back() << "\n";
          } else {
            std::cout << "\nSelect the correct vertex!\n";
          }
        } else {
          std::cout << "\nFirstly load the correct graph!\n";
        }
        break;
      case s21::Mode::kShortestPathBetweenTwoArbitraryVertices:
        if (graph.AmountOfVertices()) {
          std::cout << "Enter first vertex (from 1 to "
                    << graph.AmountOfVertices() << "): ";
          std::cin >> vertex1;
          std::cout << "Enter second vertex (from 1 to "
                    << graph.AmountOfVertices() << "): ";
          std::cin >> vertex2;

          if (vertex1 >= 1 && vertex1 <= graph.AmountOfVertices() &&
              vertex2 >= 1 && vertex2 <= graph.AmountOfVertices()) {
            integer = algs.getShortestPathBetweenVertices(
                graph, static_cast<int>(vertex1), static_cast<int>(vertex2));
            std::cout << integer << "\n";
          } else {
            std::cout << "\nSelect the correct vertices!\n";
          }
        } else {
          std::cout << "\nFirstly load the correct graph!\n";
        }
        break;
      case s21::Mode::kShortestPathsBetweenAllPairsOfVertices:
        matrix = algs.getShortestPathsBetweenAllVertices(graph);
        for (std::size_t i = 0; i < matrix.GetRows(); i++) {
          for (std::size_t j = 0; j < matrix.GetColumns() - 1; j++) {
            std::cout << matrix.operator()(i, j) << " ";
          }
          std::cout << matrix.operator()(i, matrix.GetColumns() - 1) << "\n";
        }
        break;
      case s21::Mode::kMinimumSpanningTree:
        matrix = algs.getLeastSpanningTree(graph);
        for (std::size_t i = 0; i < matrix.GetRows(); i++) {
          for (std::size_t j = 0; j < matrix.GetColumns() - 1; j++) {
            std::cout << matrix.operator()(i, j) << " ";
          }
          std::cout << matrix.operator()(i, matrix.GetColumns() - 1) << "\n";
        }
        break;
      case s21::Mode::kTravelingSalesmanProblem:
        if (graph.AmountOfVertices()) {
          tsm_result = algs.SolveTravelingSalesmanProblem(graph);
          std::cout << "Distance: " << tsm_result.distance << "\n";
          std::cout << "Route: ";
          for (std::size_t i = 0; i < tsm_result.vertices.size() - 1; ++i)
            std::cout << tsm_result.vertices[i] << " ";
          std::cout << tsm_result.vertices.back() << "\n";
        } else {
          std::cout << "\nFirstly load the correct graph!\n";
        }
        break;
      case s21::Mode::kTSPAnalyze:
        if (graph.AmountOfVertices()) {
          std::cout << "Enter N (from 1 to 1000): ";
          std::cin >> n;
          if (n >= 1 && n <= 1000) {
            start_timestamp = std::chrono::high_resolution_clock::now();
            for (std::size_t i = 0; i < n; ++i) {
              algs.SolveTravelingSalesmanProblem(graph);
            }
            end_timestamp = std::chrono::high_resolution_clock::now();
            tsp1 = end_timestamp - start_timestamp;

            start_timestamp = std::chrono::high_resolution_clock::now();
            for (std::size_t i = 0; i < n; ++i) {
              algs.NaiveSolveTravelingSalesmanProblem(graph);
            }
            end_timestamp = std::chrono::high_resolution_clock::now();
            tsp2 = end_timestamp - start_timestamp;

            start_timestamp = std::chrono::high_resolution_clock::now();
            for (std::size_t i = 0; i < n; ++i) {
              algs.NearestNeighborSolveTravelingSalesmanProblem(graph);
            }
            end_timestamp = std::chrono::high_resolution_clock::now();
            tsp3 = end_timestamp - start_timestamp;

            std::cout << "Result:\n"
                         "SolveTravelingSalesmanProblem: "
                      << tsp1.count()
                      << " s\n"
                         "NaiveSolveTravelingSalesmanProblem: "
                      << tsp2.count()
                      << " s\n"
                         "NearestNeighborSolveTravelingSalesmanProblem: "
                      << tsp3.count() << " s\n";
          } else {
            std::cout << "\nN must be from 1 to 1000!\n";
          }
        } else {
          std::cout << "\nFirstly load the correct graph!\n";
        }
        break;
      default:
        break;
    }
  } while (mode != s21::Mode::kExit);

  return 0;
}
