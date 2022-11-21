#include "s21_graph.h"

#include <fstream>

Graph::Graph(size_t amount_of_vertices)
    : adj_matrix(S21Matrix(amount_of_vertices, amount_of_vertices)) {}
Graph::Graph(const Graph& other) : adj_matrix(other.adj_matrix) {}
Graph::Graph(Graph&& other) : adj_matrix(std::move(other.adj_matrix)) {}

Graph& Graph::operator=(const Graph& other) {
  adj_matrix = other.adj_matrix;
  return *this;
}

double& Graph::operator()(size_t i, size_t j) const { return adj_matrix(i, j); }

void Graph::add_edge(size_t i, size_t j) {
  adj_matrix(i, j) = 1;
  adj_matrix(j, i) = 1;
}

void Graph::add_edge(size_t from, size_t to, size_t weight) {
  adj_matrix(from, to) = weight;
}

void Graph::rm_edge(size_t i, size_t j) {
  adj_matrix(i, j) = 0;
  adj_matrix(j, i) = 0;
}

void Graph::rm_one_way_edge(size_t from, size_t to) {
  adj_matrix(from, to) = 0;
}

size_t Graph::has_edge(size_t from, size_t to) { return adj_matrix(from, to); }

size_t Graph::amount_of_vertices() { return adj_matrix.get_rows(); }

void Graph::loadGraphFromFile(std::string filename) {
  std::ifstream infile(filename);
  size_t amount_of_vertices;
  infile >> amount_of_vertices;
  adj_matrix = S21Matrix(amount_of_vertices, amount_of_vertices);
  for (size_t i = 0; i < amount_of_vertices; i++) {
    for (size_t j = 0; j < amount_of_vertices; j++) {
      infile >> adj_matrix(i, j);
    }
  }
}
void exportGraphToDot(std::string filename);

void Graph::draw() {
  std::cout << adj_matrix.get_rows() << "\n";
  for (size_t i = 0; i < (size_t)adj_matrix.get_rows(); i++) {
    for (size_t j = 0; j < (size_t)adj_matrix.get_cols(); j++) {
      std::cout << adj_matrix(i, j) << " ";
    }
    std::cout << "\n";
  }
}