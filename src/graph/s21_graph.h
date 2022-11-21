#ifndef SRC_S21_GRAPH_H_
#define SRC_S21_GRAPH_H_

#include <iostream>
#include <string>

#include "../matrix/s21_matrix_oop.h"

class Graph {
 public:
  Graph() = default;
  Graph(size_t amount_of_vertices);
  Graph(const Graph& other);
  Graph(Graph&& other);
  ~Graph() = default;

  Graph& operator=(const Graph& other);
  double& operator()(size_t i, size_t j) const;

  void add_edge(size_t i, size_t j);
  void rm_edge(size_t i, size_t j);
  void add_edge(size_t from, size_t to, size_t weight);
  void rm_one_way_edge(size_t from, size_t to);

  size_t has_edge(size_t from, size_t to);

  size_t amount_of_vertices();

  void loadGraphFromFile(std::string filename);
  void exportGraphToDot(std::string filename);

  void draw();

 private:
  S21Matrix adj_matrix;
};

#endif  // SRC_S21_GRAPH_H_