#include <gtest/gtest.h>

#include "graph_algorithms/s21_graph_algorithms.h"

TEST(getLeastSpanningTree, test_1) {
  s21::Graph g;
  g.LoadGraphFromFile("test_graph_2.txt");
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

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
