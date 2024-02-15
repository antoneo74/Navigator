#ifndef SIMPLE_NAVIGATOR_SOURCE_MODEL_S21_GRAPH_ALGORITHMS_H_
#define SIMPLE_NAVIGATOR_SOURCE_MODEL_S21_GRAPH_ALGORITHMS_H_

#include "s21_graph.h"
#include "traveling_salesman/common/path_structure.h"

namespace s21 {
class GraphAlgorithms {
 public:
  using MatrixAdjacency = std::vector<std::vector<size_t>>;

  GraphAlgorithms() = default;

  std::vector<size_t> DepthFirstSearch(Graph& graph, size_t start_vertex);
  std::vector<size_t> BreadthFirstSearch(Graph& graph, size_t start_vertex);
  size_t GetShortestPathBetweenVertices(Graph& graph, size_t vertex1,
                                        size_t vertex2);
  MatrixAdjacency GetShortestPathsBetweenAllVertices(Graph& graph);
  MatrixAdjacency GetLeastSpanningTree(const Graph& graph);
  TsmResult SolveTravelingSalesmanProblem(Graph& graph);
  TsmResult SolveTravelingSalesmanProblemGeneticAlgorithm(Graph& graph);
  TsmResult SolveTravelingSalesmanProblemSimulatedAnnealing(const Graph& graph);
};
}  // namespace s21

#endif  // SIMPLE_NAVIGATOR_SOURCE_MODEL_S21_GRAPH_ALGORITHMS_H_