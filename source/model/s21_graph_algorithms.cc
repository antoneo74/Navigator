#include "s21_graph_algorithms.h"

#include "libs/s21_queue.h"
#include "libs/s21_stack.h"
#include "traveling_salesman/ant_colony_algorithm/ant_colony_solver.h"
#include "traveling_salesman/genetic_algorithm/crossover.h"
#include "traveling_salesman/genetic_algorithm/genetic_solver.h"
#include "traveling_salesman/genetic_algorithm/mutation.h"
#include "traveling_salesman/genetic_algorithm/selection.h"
#include "traveling_salesman/simulated_annealing/simulated_annealing.h"

namespace s21 {

std::vector<size_t> GraphAlgorithms::DepthFirstSearch(Graph& graph,
                                                      size_t start_vertex) {
  if (start_vertex < 1)
    throw std::invalid_argument("Index of vertex is incorrect");
  if (start_vertex > graph.GetSize())
    throw std::out_of_range("Index of vertex is out of range");
  std::vector<bool> visited(graph.GetSize());
  size_t start = static_cast<size_t>(start_vertex) - 1;
  visited[start] = true;
  Stack<size_t> stack;
  stack.Push(start);
  std::vector<size_t> result;
  result.push_back(start);
  while (!stack.Empty()) {
    size_t current = stack.Top();
    bool vertex_has_children = false;
    for (size_t i = 0; i < graph.GetSize(); ++i) {
      if (graph.GetData()[current][i] && !visited[i]) {
        visited[i] = true;
        vertex_has_children = true;
        stack.Push(i);
        result.push_back(i);
        current = i;
      }
    }
    if (!vertex_has_children) stack.Pop();
  }
  return result;
}

std::vector<size_t> GraphAlgorithms::BreadthFirstSearch(Graph& graph,
                                                        size_t start_vertex) {
  if (start_vertex < 1)
    throw std::invalid_argument("Index of vertex is incorrect");
  if (start_vertex > graph.GetSize())
    throw std::out_of_range("Index of vertex is out of range");
  std::vector<bool> visited(graph.GetSize());
  size_t start = static_cast<size_t>(start_vertex) - 1;
  visited[start] = true;
  Queue<size_t> queue;
  queue.Push(start);
  std::vector<size_t> result;
  result.push_back(start);
  while (!queue.Empty()) {
    size_t current = queue.Front();
    queue.Pop();
    for (size_t i = 0; i < graph.GetSize(); ++i) {
      if (graph.GetData()[current][i] && !visited[i]) {
        visited[i] = true;
        queue.Push(i);
        result.push_back(i);
      }
    }
  }
  return result;
}

size_t GraphAlgorithms::GetShortestPathBetweenVertices(Graph& graph,
                                                       size_t vertex1,
                                                       size_t vertex2) {
  if (vertex1 < 1 || vertex2 < 1)
    throw std::invalid_argument("Index of vertex is incorrect");
  if (vertex1 > graph.GetSize() || vertex2 > graph.GetSize())
    throw std::out_of_range("Index of vertex is out of range");
  std::vector<size_t> min_length(graph.GetSize(),
                                 std::numeric_limits<size_t>::max());
  size_t start = vertex1 - 1;
  size_t finish = vertex2 - 1;
  min_length[start] = 0;
  Queue<size_t> queue;
  queue.Push(start);
  while (!queue.Empty()) {
    size_t vertex = queue.Front();
    queue.Pop();
    for (size_t i = 0; i < graph.GetSize(); ++i) {
      size_t weight = graph.GetData()[vertex][i];
      if (i != vertex && weight &&
          min_length[vertex] + weight < min_length[i]) {
        min_length[i] = min_length[vertex] + weight;
        queue.Push(i);
      }
    }
  }
  return min_length[finish];
}

GraphAlgorithms::MatrixAdjacency
GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph& graph) {
  std::vector<std::vector<size_t>> result = graph.GetData();
  const size_t kMax = std::numeric_limits<size_t>::max();
  for (size_t i = 0; i < graph.GetSize(); ++i) {
    for (size_t j = 0; j < graph.GetSize(); ++j) {
      if (result[i][j] == 0) result[i][j] = i == j ? 0 : kMax;
    }
  }
  for (size_t current = 0; current != graph.GetSize(); ++current) {
    for (size_t i = 0; i != graph.GetSize(); ++i) {
      for (size_t j = 0; j != graph.GetSize(); ++j) {
        size_t weight = result[i][current] + result[current][j];
        if (result[i][current] != kMax && result[current][j] != kMax &&
            result[i][j] > weight)
          result[i][j] = weight;
      }
    }
  }
  return result;
}

GraphAlgorithms::MatrixAdjacency GraphAlgorithms::GetLeastSpanningTree(
    const Graph& graph) {
  size_t N = graph.GetSize();
  std::vector<std::vector<size_t>> spanning_tree(N, std::vector<size_t>(N, 0));
  std::set<size_t> visited;
  std::set<size_t> unvisited;

  for (size_t i = 0; i < N; ++i) {
    unvisited.insert(i);
  }

  auto first = unvisited.begin();
  visited.insert(*first);
  unvisited.erase(first);

  while (!unvisited.empty()) {
    std::pair<size_t, size_t> min_index = {0, 0};
    size_t min_weight = std::numeric_limits<size_t>::max();

    for (size_t curr : visited) {
      for (size_t i = 0; i < N; ++i) {
        size_t adj_weight = graph.GetValue(curr, i);
        if (adj_weight <= min_weight && adj_weight != 0 && unvisited.count(i)) {
          min_weight = adj_weight;
          min_index = {curr, i};
        }
      }
    }

    spanning_tree[min_index.first][min_index.second] = min_weight;
    spanning_tree[min_index.second][min_index.first] = min_weight;
    unvisited.erase(min_index.second);
    visited.insert(min_index.second);
  }

  return spanning_tree;
}

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(Graph& graph) {
  size_t count_colony = 1;
  size_t size_colony = 1000;

  AntColony ant_colony(graph, count_colony, size_colony);
  TsmResult path = ant_colony.Solve();

  return path;
}

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblemGeneticAlgorithm(
    Graph& graph) {
  size_t number_generations = 50;
  size_t population_size = 100;
  double possible_mutation = 0.01;
  double possible_crossover = 0.9;

  TournamentSelection selection;
  OrderedCrossover crossover;
  ExchangeMutation mutation;
  GeneticAlgorithmTsp genetic_algorithm(graph, selection, crossover, mutation);

  TsmResult path =
      genetic_algorithm.Solve(number_generations, population_size,
                              possible_mutation, possible_crossover);

  return path;
}

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblemSimulatedAnnealing(
    const Graph& graph) {
  SimulatedAnnealing simulated_annealing(graph, AnnealingParams{});

  return simulated_annealing.Solve();
}

}  // namespace s21
