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

std::size_t Graph::AmountOfVertices() const { return adj_matrix_->GetRows(); }

void Graph::LoadGraphFromFile(const std::string& filename) {
  std::ifstream infile(filename);
  if (infile.is_open() == false) {
    throw std::runtime_error("Could not open file");
  }
  std::size_t amount_of_vertices;
  infile >> amount_of_vertices;
  adj_matrix_ =
      std::make_shared<Matrix>(amount_of_vertices, amount_of_vertices);
  for (std::size_t i = 0; i < amount_of_vertices; i++) {
    for (std::size_t j = 0; j < amount_of_vertices; j++) {
      infile >> adj_matrix_->operator()(i, j);
    }
  }
  infile.close();
}

void Graph::ExportGraphToDot(const std::string& filename) {
  std::ofstream outfile(filename);
  if (outfile.is_open() == false) {
    throw std::runtime_error("Could not open file");
  }
  std::string edge_type = " -- ";
  for (size_t i = 0; i < AmountOfVertices(); i++) {
    for (size_t j = i; j < AmountOfVertices(); j++) {
      if (adj_matrix_->operator()(i, j) != adj_matrix_->operator()(j, i)) {
        edge_type = " -> ";
        break;
      }
    }
  }
  outfile << "graph graphname {\n";
  for (size_t i = 0; i < AmountOfVertices(); i++) {
    size_t j = (edge_type == " -- ") ? i : 0;
    for (; j < AmountOfVertices(); j++) {
      if (adj_matrix_->operator()(i, j) != 0) {
        outfile << "\tv" << i + 1 << edge_type << "v" << j + 1 << ";\n";
      }
    }
  }
  outfile << "}\n";
  outfile.close();
}

}  // namespace s21
