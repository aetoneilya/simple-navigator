#include "s21_graph.h"

namespace s21 {

Graph::Graph() : adj_matrix_(std::make_shared<Matrix>()) {}

Graph::Graph(std::size_t vertices)
    : adj_matrix_(std::make_shared<Matrix>(vertices, vertices)) {}

Graph::Graph(const Graph& other) : adj_matrix_(other.adj_matrix_) {}

Graph::Graph(Graph&& other) { Swap(&other); }

Graph& Graph::operator=(const Graph& other) {
  if (this != &other) {
    Graph(other).Swap(this);
  }
  return *this;
}

Graph& Graph::operator=(Graph&& other) {
  if (this != &other) {
    Graph(other).Swap(this);
  }
  return *this;
}
int& Graph::operator()(std::size_t i, std::size_t j) {
  return const_cast<int&>(const_cast<const Graph*>(this)->operator()(i, j));
}

const int& Graph::operator()(std::size_t i, std::size_t j) const {
  return adj_matrix_->operator()(i, j);
}

void Graph::Swap(Graph* other) { std::swap(adj_matrix_, other->adj_matrix_); }

void Graph::AddEdge(std::size_t i, std::size_t j) {
  adj_matrix_->operator()(i, j) = 1;
  adj_matrix_->operator()(j, i) = 1;
}

void Graph::AddEdge(std::size_t from, std::size_t to, int weight) {
  adj_matrix_->operator()(from, to) = weight;
}

void Graph::RemoveEdge(std::size_t i, std::size_t j) {
  adj_matrix_->operator()(i, j) = 0;
  adj_matrix_->operator()(j, i) = 0;
}

void Graph::RemoveOneWayEdge(std::size_t from, std::size_t to) {
  adj_matrix_->operator()(from, to) = 0;
}

std::size_t Graph::HasEdge(std::size_t from, std::size_t to) {
  return adj_matrix_->operator()(from, to);
}

std::size_t Graph::AmountOfVertices() { return adj_matrix_->GetRows(); }

void Graph::LoadGraphFromFile(const std::string& filename) {
  std::ifstream infile(filename);
  std::size_t amount_of_vertices;
  infile >> amount_of_vertices;
  adj_matrix_ =
      std::make_shared<Matrix>(amount_of_vertices, amount_of_vertices);
  for (std::size_t i = 0; i < amount_of_vertices; i++) {
    for (std::size_t j = 0; j < amount_of_vertices; j++) {
      infile >> adj_matrix_->operator()(i, j);
    }
  }
}

void Graph::ExportGraphToDot(const std::string& filename) {
  static_cast<void>(filename);
}

void Graph::Draw() {
  std::cout << adj_matrix_->GetRows() << "\n";
  for (std::size_t i = 0; i < adj_matrix_->GetRows(); i++) {
    for (std::size_t j = 0; j < adj_matrix_->GetColumns(); j++) {
      std::cout << adj_matrix_->operator()(i, j) << " ";
    }
    std::cout << "\n";
  }
}

}  // namespace s21
