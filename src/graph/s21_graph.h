#ifndef SRC_GRAPH_S21_GRAPH_H_
#define SRC_GRAPH_S21_GRAPH_H_

#include <fstream>
#include <memory>
#include <string>

#include "../matrix/s21_matrix_oop.h"

namespace s21 {

class Graph {
 public:
  Graph();
  explicit Graph(std::size_t vertices);
  Graph(const Graph& other);
  Graph(Graph&& other);
  ~Graph() = default;

  Graph& operator=(const Graph& other);
  Graph& operator=(Graph&& other);
  int& operator()(std::size_t i, std::size_t j);
  const int& operator()(std::size_t i, std::size_t j) const;

  void Swap(Graph* other);

  std::size_t AmountOfVertices() const;

  void LoadGraphFromFile(const std::string& filename);
  void ExportGraphToDot(const std::string& filename);

 private:
  std::shared_ptr<Matrix> adj_matrix_;
};

}  // namespace s21

#endif  // SRC_GRAPH_S21_GRAPH_H_
