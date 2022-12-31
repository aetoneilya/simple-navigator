#include <gtest/gtest.h>

#include "../graph_algorithms/s21_graph_algorithms.h"

void validate_path(const s21::tsm::TsmResult& res, const s21::Graph& graph) {
  size_t number_of_cities = graph.AmountOfVertices();

  double total_distance = 0;
  for (size_t i = 0; i < graph.AmountOfVertices(); i++) {
    double distance =
        graph(res.vertices[i], res.vertices[(i + 1) % number_of_cities]);

    total_distance += distance;
    EXPECT_FALSE(distance == 0);
  }

  EXPECT_DOUBLE_EQ(res.distance, total_distance);
}

TEST(getLeastSpanningTree, test_1) {
  s21::Graph g;
  g.LoadGraphFromFile("tests/test_graph_2.txt");
  s21::GraphAlgoritms ga;
  auto matrix = ga.getLeastSpanningTree(g);

  int result[6][6] = {{0, 0, 1, 0, 0, 0}, {0, 0, 5, 0, 3, 0},
                      {1, 5, 0, 0, 0, 4}, {0, 0, 0, 0, 0, 2},
                      {0, 3, 0, 0, 0, 0}, {0, 0, 4, 2, 0, 0}};

  for (std::size_t i = 0; i < g.AmountOfVertices(); ++i) {
    for (std::size_t j = 0; j < g.AmountOfVertices(); ++j) {
      EXPECT_EQ(matrix(i, j), result[i][j]);
    }
  }
}

TEST(travelingSalesmanProblem, naiveSolve) {
  s21::Graph my_graph;
  my_graph.LoadGraphFromFile("tests/test_graph_2.txt");
  s21::GraphAlgoritms ga;
  s21::tsm::TsmResult res = ga.NaiveSolveTravelingSalesmanProblem(my_graph);

  EXPECT_DOUBLE_EQ(res.distance, 22.);
  validate_path(res, my_graph);
}

TEST(travelingSalesmanProblem, nearestNeighbor) {
  s21::Graph my_graph;
  my_graph.LoadGraphFromFile("tests/test_graph_2.txt");
  s21::GraphAlgoritms ga;
  s21::tsm::TsmResult res =
      ga.NearestNeighborSolveTravelingSalesmanProblem(my_graph);

  EXPECT_DOUBLE_EQ(res.distance, 22.);
  validate_path(res, my_graph);
}

TEST(travelingSalesmanProblem, antColony) {
  s21::Graph my_graph;
  my_graph.LoadGraphFromFile("tests/test_graph_2.txt");
  s21::GraphAlgoritms ga;
  s21::tsm::TsmResult res = ga.SolveTravelingSalesmanProblem(my_graph);

  validate_path(res, my_graph);
}

TEST(travelingSalesmanProblem, naiveSolve_nopath) {
  s21::Graph my_graph;
  my_graph.LoadGraphFromFile("tests/empty_graph.txt");
  s21::GraphAlgoritms ga;
  s21::tsm::TsmResult res = ga.NaiveSolveTravelingSalesmanProblem(my_graph);

  EXPECT_DOUBLE_EQ(res.distance, INFINITY);
}

TEST(travelingSalesmanProblem, nearestNeighbor_nopath) {
  s21::Graph my_graph;
  my_graph.LoadGraphFromFile("tests/empty_graph.txt");
  s21::GraphAlgoritms ga;
  s21::tsm::TsmResult res =
      ga.NearestNeighborSolveTravelingSalesmanProblem(my_graph);

  EXPECT_DOUBLE_EQ(res.distance, INFINITY);
}

TEST(travelingSalesmanProblem, antColony_nopath) {
  s21::Graph my_graph;
  my_graph.LoadGraphFromFile("tests/empty_graph.txt");
  s21::GraphAlgoritms ga;
  s21::tsm::TsmResult res = ga.SolveTravelingSalesmanProblem(my_graph);

  EXPECT_DOUBLE_EQ(res.distance, INFINITY);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
