#include "common_tests.h"
#include "model/s21_graph.h"
#include "model/s21_graph_algorithms.h"

namespace s21 {

TEST(AntColonyTest, ThrowEmptyGraph) {
  Graph graph;
  ASSERT_THROW(graph.LoadGraphFromFile(kAssetsDir + "graph_0x0.txt"),
               std::invalid_argument);
  GraphAlgorithms algorithms;
  ASSERT_EQ(algorithms.SolveTravelingSalesmanProblem(graph).distance,
            std::numeric_limits<double>::infinity());
}

TEST(AntColonyTest, SingleVertexGraph) {
  Graph graph;
  graph.LoadGraphFromFile(kAssetsDir + "graph_1x1.txt");
  GraphAlgorithms algorithms;
  TsmResult result = algorithms.SolveTravelingSalesmanProblem(graph);

  ASSERT_EQ(result.vertices.size(), graph.GetSize() + 1);
  ASSERT_EQ(result.distance, 0);
}

TEST(AntColonyTest, TwoVertexGraph) {
  Graph graph;
  graph.LoadGraphFromFile(kAssetsDir + "graph_2x2.txt");
  GraphAlgorithms algorithms;
  TsmResult result = algorithms.SolveTravelingSalesmanProblem(graph);

  ASSERT_EQ(result.vertices.size(), graph.GetSize() + 1);
  ASSERT_EQ(result.distance, 4);
}

TEST(AntColonyTest, NoSolutionGraph) {
  Graph graph;
  graph.LoadGraphFromFile(kAssetsDir + "graph_no_solution.txt");
  GraphAlgorithms algorithms;
  ASSERT_EQ(algorithms.SolveTravelingSalesmanProblem(graph).distance,
            std::numeric_limits<double>::infinity());
}

TEST(AntColonyTest, LargeGraph) {
  Graph graph;
  graph.LoadGraphFromFile(kAssetsDir + "graph_example.txt");
  GraphAlgorithms algorithms;
  TsmResult result = algorithms.SolveTravelingSalesmanProblem(graph);

  ASSERT_EQ(result.vertices.size(), graph.GetSize() + 1);
  ASSERT_LT(result.distance, 270);
  ASSERT_GT(result.distance, 250);
}

TEST(AntColonyTest, MultipleRunsGraphNoCheckLeaks) {
  Graph graph;
  graph.LoadGraphFromFile(kAssetsDir + "graph_example.txt");
  GraphAlgorithms algorithms;

  for (size_t i = 0; i < 50; ++i) {
    TsmResult result = algorithms.SolveTravelingSalesmanProblem(graph);
    ASSERT_EQ(result.vertices.size(), graph.GetSize() + 1);
    ASSERT_LT(result.distance, 270);
    ASSERT_GT(result.distance, 250);
  }
}

} // namespace s21
