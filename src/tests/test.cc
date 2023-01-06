#include <gtest/gtest.h>

#include "../graph_algorithms/s21_graph_algorithms.h"

void validate_path(const s21::tsm::TsmResult& res, const s21::Graph& graph) {
  size_t number_of_cities = graph.AmountOfVertices();

  double total_distance = 0;
  for (size_t i = 0; i < graph.AmountOfVertices(); i++) {
    double distance =
        graph(res.vertices[i], res.vertices[(i + 1) % number_of_cities]);

    total_distance += distance;
    EXPECT_NE(distance, 0);
  }

  EXPECT_DOUBLE_EQ(res.distance, total_distance);
}

bool findSubstringInFile(const std::string& substr,
                         const std::string& fileName) {
  bool result = false;
  std::ifstream file_text(fileName);
  std::string x;

  if (file_text.is_open()) {
    while (getline(file_text, x)) {
      if (x.find(substr) != std::string::npos) {
        result = true;
        break;
      }
    }
    file_text.close();
  }
  return result;
}

TEST(graphClass, stdConstructor) {
  s21::Graph my_graph;
  EXPECT_THROW(my_graph(0, 0), std::out_of_range);
}

TEST(graphClass, paramConstructor) {
  s21::Graph my_graph_1(5);
  for (size_t i = 0; i < 5; i++) {
    for (size_t j = 0; j < 5; j++) {
      EXPECT_EQ(my_graph_1(i, j), 0);
    }
  }
  EXPECT_THROW(my_graph_1(5, 4), std::out_of_range);
  EXPECT_THROW(my_graph_1(4, 5), std::out_of_range);
}

TEST(graphClass, copyConstructor) {
  s21::Graph my_graph_1(5);
  s21::Graph my_graph_2(my_graph_1);
  for (size_t i = 0; i < 5; i++) {
    for (size_t j = 0; j < 5; j++) {
      EXPECT_EQ(my_graph_2(i, j), 0);
    }
  }
  EXPECT_THROW(my_graph_2(5, 4), std::out_of_range);
  EXPECT_THROW(my_graph_2(4, 5), std::out_of_range);
}

TEST(graphClass, moveConstructor) {
  s21::Graph my_graph_1(5);
  s21::Graph my_graph_2(std::move(my_graph_1));
  for (size_t i = 0; i < 5; i++) {
    for (size_t j = 0; j < 5; j++) {
      EXPECT_EQ(my_graph_2(i, j), 0);
    }
  }
  EXPECT_THROW(my_graph_2(5, 4), std::out_of_range);
  EXPECT_THROW(my_graph_2(4, 5), std::out_of_range);
}

TEST(graphClass, copyOperator) {
  s21::Graph my_graph_1(5);
  s21::Graph my_graph_2 = my_graph_1;
  for (size_t i = 0; i < 5; i++) {
    for (size_t j = 0; j < 5; j++) {
      EXPECT_EQ(my_graph_2(i, j), 0);
    }
  }
  EXPECT_THROW(my_graph_2(5, 4), std::out_of_range);
  EXPECT_THROW(my_graph_2(4, 5), std::out_of_range);
}

TEST(graphClass, moveOperator) {
  s21::Graph my_graph_1(5);
  s21::Graph my_graph_2 = std::move(my_graph_1);
  for (size_t i = 0; i < 5; i++) {
    for (size_t j = 0; j < 5; j++) {
      EXPECT_EQ(my_graph_2(i, j), 0);
    }
  }
  EXPECT_THROW(my_graph_2(5, 4), std::out_of_range);
  EXPECT_THROW(my_graph_2(4, 5), std::out_of_range);
}

TEST(graphClass, amountOfVertices0) {
  s21::Graph my_graph_1;
  EXPECT_EQ(my_graph_1.AmountOfVertices(), 0);
}

TEST(graphClass, amountOfVertices1) {
  s21::Graph my_graph_1(5);
  EXPECT_EQ(my_graph_1.AmountOfVertices(), 5);
}

TEST(graphClass, loadFromFile) {
  s21::Graph g;
  g.LoadGraphFromFile("tests/test_graph_2.txt");

  EXPECT_EQ(g.AmountOfVertices(), 6);

  int result[6][6] = {{0, 6, 1, 5, 0, 0}, {6, 0, 5, 0, 3, 0},
                      {1, 5, 0, 5, 6, 4}, {5, 0, 5, 0, 0, 2},
                      {0, 3, 6, 0, 0, 6}, {0, 0, 4, 2, 6, 0}};

  for (std::size_t i = 0; i < g.AmountOfVertices(); ++i) {
    for (std::size_t j = 0; j < g.AmountOfVertices(); ++j) {
      EXPECT_EQ(g(i, j), result[i][j]);
    }
  }
}

TEST(graphClass, exportToDot0) {
  s21::Graph g;
  g.LoadGraphFromFile("tests/test_graph_2.txt");
  g.ExportGraphToDot("test_dot.dot");

  for (std::size_t i = 0; i < g.AmountOfVertices(); ++i) {
    for (std::size_t j = i; j < g.AmountOfVertices(); ++j) {
      std::string substr =
          "v" + std::to_string(i + 1) + " -- v" + std::to_string(j + 1) + ";";
      bool res = findSubstringInFile(substr, "test_dot.dot");
      EXPECT_EQ(res, g(i, j) != 0);
    }
  }
}

TEST(graphClass, exportToDot1) {
  s21::Graph g;
  g.LoadGraphFromFile("tests/test_graph_4.txt");
  g.ExportGraphToDot("test_dot.dot");

  for (std::size_t i = 0; i < g.AmountOfVertices(); ++i) {
    for (std::size_t j = 0; j < g.AmountOfVertices(); ++j) {
      std::string substr =
          "v" + std::to_string(i + 1) + " -> v" + std::to_string(j + 1) + ";";
      bool res = findSubstringInFile(substr, "test_dot.dot");
      EXPECT_EQ(res, g(i, j) != 0);
    }
  }
}

TEST(searchAlgs, breadthFirst) {
  s21::Graph g;
  g.LoadGraphFromFile("tests/test_graph_2.txt");
  s21::GraphAlgoritms ga;
  auto res_vec = ga.breadthFirstSearch(g, 1);
  std::vector<int> result = {1, 2, 3, 4, 5, 6};

  for (std::size_t i = 0; i < g.AmountOfVertices(); ++i) {
    EXPECT_EQ(res_vec[i], result[i]);
  }
}

TEST(searchAlgs, depthFirst) {
  s21::Graph g;
  g.LoadGraphFromFile("tests/test_graph_2.txt");
  s21::GraphAlgoritms ga;
  auto res_vec = ga.depthFirstSearch(g, 1);
  std::vector<int> result = {1, 4, 6, 5, 3, 2};

  for (std::size_t i = 0; i < g.AmountOfVertices(); ++i) {
    EXPECT_EQ(res_vec[i], result[i]);
  }
}

TEST(searchAlgs, shortestPathBetweenVertices) {
  s21::Graph g;
  g.LoadGraphFromFile("tests/test_graph_2.txt");
  s21::GraphAlgoritms ga;
  int res;
  res = ga.getShortestPathBetweenVertices(g, 1, 6);
  EXPECT_EQ(res, 5);
  res = ga.getShortestPathBetweenVertices(g, 6, 1);
  EXPECT_EQ(res, 5);
  res = ga.getShortestPathBetweenVertices(g, 2, 4);
  EXPECT_EQ(res, 10);
}

TEST(searchAlgs, shortestPathsBetweenAllVertices) {
  s21::Graph g;
  g.LoadGraphFromFile("tests/test_graph_2.txt");
  s21::GraphAlgoritms ga;
  auto matrix = ga.getShortestPathsBetweenAllVertices(g);

  int result[6][6] = {{0, 6, 1, 5, 7, 5}, {6, 0, 5, 10, 3, 9},
                      {1, 5, 0, 5, 6, 4}, {5, 10, 5, 0, 8, 2},
                      {7, 3, 6, 8, 0, 6}, {5, 9, 4, 2, 6, 0}};

  for (std::size_t i = 0; i < g.AmountOfVertices(); ++i) {
    for (std::size_t j = 0; j < g.AmountOfVertices(); ++j) {
      EXPECT_EQ(matrix(i, j), result[i][j]);
    }
  }
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
