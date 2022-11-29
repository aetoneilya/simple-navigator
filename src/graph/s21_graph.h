#ifndef SRC_GRAPH_S21_GRAPH_H_
#define SRC_GRAPH_S21_GRAPH_H_

#include <fstream>
// TODO(ppoutine) Remove in prod
#include <iostream>
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

  void AddEdge(std::size_t i, std::size_t j);
  void AddEdge(std::size_t from, std::size_t to, int weight);
  void RemoveEdge(std::size_t i, std::size_t j);
  void RemoveOneWayEdge(std::size_t from, std::size_t to);

  std::size_t HasEdge(std::size_t from, std::size_t to);

  std::size_t AmountOfVertices();

  void LoadGraphFromFile(const std::string& filename);
  void ExportGraphToDot(const std::string& filename);

  void Draw();

 private:
  std::shared_ptr<Matrix> adj_matrix_;
};

}  // namespace s21

#endif  // SRC_GRAPH_S21_GRAPH_H_
