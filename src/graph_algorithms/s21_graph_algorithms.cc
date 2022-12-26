#include "s21_graph_algorithms.h"

#include <iostream>

namespace s21 {

tsm::TsmResult GraphAlgoritms::SolveTravelingSalesmanProblem(Graph& graph) {
  tsm::AntColony ac;
  return ac.FindOptimalPath(graph);
}

tsm::TsmResult GraphAlgoritms::NaiveSolveTravelingSalesmanProblem(
    Graph& graph) {
  size_t number_of_cities = graph.AmountOfVertices();

  tsm::TsmResult best_result;
  best_result.distance = INFINITY;

  tsm::TsmResult temp;
  for (size_t i = 0; i < number_of_cities; i++) {
    temp.vertices.push_back((int)i);
  }

  do {
    temp.distance = 0;
    for (size_t i = 0; i < number_of_cities; i++)
      temp.distance +=
          graph(temp.vertices[i], temp.vertices[(i + 1) % number_of_cities]);

    if (temp.distance < best_result.distance) best_result = temp;
  } while (std::next_permutation(temp.vertices.begin(), temp.vertices.end()));

  return best_result;
}

tsm::TsmResult GraphAlgoritms::NearestNeighborSolveTravelingSalesmanProblem(
    Graph& graph) {
  tsm::TsmResult best_result;
  best_result.distance = INFINITY;

  size_t number_of_cities = graph.AmountOfVertices();

  for (size_t i = 0; i < number_of_cities; i++) {
    tsm::TsmResult temp;
    temp.vertices.resize(number_of_cities);
    temp.vertices[0] = (int)i;

    std::vector<int> visited(number_of_cities);

    for (size_t j = 1; j < number_of_cities; j++) {
      int nearestness = graph(j - 1, 0);
      int nearest = 0;  // find nearest city to graph[jkUndefined]

      for (size_t k = 0; k < number_of_cities; k++) {
        if (graph(j - 1, k) < nearestness && !visited[k]) {
          nearestness = graph(j - 1, k);
          nearest = (int)k;
        }
      }

      temp.vertices[j] = nearest;
      temp.distance += graph(temp.vertices[j - 1], temp.vertices[j]);
    }

    temp.distance += graph(temp.vertices.front(), temp.vertices.back());

    if (temp.distance < best_result.distance) best_result = temp;
  }

  return best_result;
}

std::vector<int> GraphAlgoritms::depthFirstSearch(Graph& graph,
                                                  int startVertex) {
  std::vector<int> result(0);
  s21::stack<int> vertices;
  std::vector<bool> vertices_used(graph.AmountOfVertices(), false);

  vertices.push(startVertex);
  vertices_used[startVertex - 1] = 1;

  while (vertices.empty() == false) {
    int cur_vertice = vertices.top() - 1;
    result.push_back(vertices.top());
    vertices.pop();

    for (size_t i = 0; i < graph.AmountOfVertices(); i++) {
      if (graph(cur_vertice, i) != 0 && vertices_used[i] == false) {
        vertices.push((int)i + 1);
        vertices_used[i] = true;
      }
    }
  }

  return result;
}
std::vector<int> GraphAlgoritms::breadthFirstSearch(Graph& graph,
                                                    int startVertex) {
  std::vector<int> result(0);
  s21::queue<int> vertices;
  std::vector<bool> vertices_used(graph.AmountOfVertices(), false);

  vertices.push(startVertex);
  vertices_used[startVertex - 1] = 1;

  while (vertices.empty() == false) {
    int cur_vertice = vertices.front() - 1;
    result.push_back(vertices.front());
    vertices.pop();

    for (size_t i = 0; i < graph.AmountOfVertices(); i++) {
      if (graph(cur_vertice, i) != 0 && vertices_used[i] == false) {
        vertices.push((int)i + 1);
        vertices_used[i] = true;
      }
    }
  }

  return result;
}

int GraphAlgoritms::getShortestPathBetweenVertices(Graph& graph, int vertex1,
                                                   int vertex2) {
  std::vector<int> shotrestPathsToVert(graph.AmountOfVertices(), kUndefined);
  std::vector<bool> verticeVisited(graph.AmountOfVertices(), false);

  int curVertex = vertex1 - 1;
  shotrestPathsToVert[curVertex] = 0;

  while (curVertex != kUndefined && curVertex != vertex2 - 1) {
    verticeVisited[curVertex] = true;
    for (size_t i = 0; i < graph.AmountOfVertices(); i++) {
      if (verticeVisited[i] == true || graph(curVertex, i) == 0) {
        continue;
      }

      int newPathLen = shotrestPathsToVert[curVertex] + graph(curVertex, i);

      if (shotrestPathsToVert[i] == kUndefined) {
        shotrestPathsToVert[i] = newPathLen;
      } else {
        shotrestPathsToVert[i] = std::min(shotrestPathsToVert[i], newPathLen);
      }
    }
    curVertex = kUndefined;
    for (size_t i = 0; i < graph.AmountOfVertices(); i++) {
      if (verticeVisited[i] == true || shotrestPathsToVert[i] == kUndefined) {
        continue;
      }
      if (curVertex == kUndefined ||
          shotrestPathsToVert[i] < shotrestPathsToVert[curVertex]) {
        curVertex = (int)i;
      }
    }
  }

  return shotrestPathsToVert[vertex2 - 1];
}

Matrix GraphAlgoritms::getShortestPathsBetweenAllVertices(Graph& graph) {
  Matrix result(graph.AmountOfVertices(), graph.AmountOfVertices());

  for (size_t i = 0; i < graph.AmountOfVertices(); i++) {
    for (size_t j = 0; j < graph.AmountOfVertices(); j++) {
      if (graph(i, j) == 0 && i != j) {
        result(i, j) = kUndefined;
      } else {
        result(i, j) = graph(i, j);
      }
    }
  }

  for (size_t k = 0; k < graph.AmountOfVertices(); k++) {
    for (size_t i = 0; i < graph.AmountOfVertices(); i++) {
      for (size_t j = 0; j < graph.AmountOfVertices(); j++) {
        if (result(i, k) != kUndefined && result(k, j) != kUndefined) {
          if (result(i, j) != kUndefined) {
            result(i, j) = std::min(result(i, j), result(i, k) + result(k, j));
          } else {
            result(i, j) = result(i, k) + result(k, j);
          }
        }
      }
    }
  }

  return result;
}

Matrix GraphAlgoritms::getLeastSpanningTree(Graph& graph) {
  Matrix adjacency_matrix(graph.AmountOfVertices(), graph.AmountOfVertices());

  std::vector<bool> used_vertices(graph.AmountOfVertices(), false);

  used_vertices[0] = true;
  std::pair<std::size_t, std::size_t> coord;
  for (std::size_t edge = 0; edge < graph.AmountOfVertices() - 1; ++edge) {
    std::size_t min = std::numeric_limits<std::size_t>::max();
    coord = {0, 0};

    for (std::size_t i = 0; i < graph.AmountOfVertices(); ++i) {
      if (used_vertices[i]) {
        for (std::size_t j = 0; j < graph.AmountOfVertices(); ++j) {
          std::size_t edge_cost = graph.HasEdge(i, j);
          if (!used_vertices[j] && edge_cost != 0) {
            if (min > edge_cost) {
              min = edge_cost;
              coord = {i, j};
            }
          }
        }
      }
    }
    adjacency_matrix(coord.first, coord.second) = static_cast<int>(min);
    adjacency_matrix(coord.second, coord.first) = static_cast<int>(min);
    used_vertices[coord.second] = true;
  }

  return adjacency_matrix;
}

}  // namespace s21
