#include "common_tests.h"
#include "model/s21_graph.h"
#include "model/s21_graph_algorithms.h"

namespace s21 {

TEST(SpanningTree, SingleVertexGraph) {
  Graph graph;
  graph.LoadGraphFromFile(kAssetsDir + "graph_1x1.txt");
  GraphAlgorithms algorithms;

  std::vector<std::vector<size_t>> spanning_tree =
      algorithms.GetLeastSpanningTree(graph);

  ASSERT_EQ(spanning_tree.size(), graph.GetSize());
  ASSERT_EQ(graph.GetData(), spanning_tree);
}

TEST(SpanningTree, TwoVertexGraph) {
  Graph graph;
  graph.LoadGraphFromFile(kAssetsDir + "graph_2x2.txt");
  GraphAlgorithms algorithms;

  std::vector<std::vector<size_t>> spanning_tree =
      algorithms.GetLeastSpanningTree(graph);

  ASSERT_EQ(spanning_tree.size(), graph.GetSize());
  ASSERT_EQ(graph.GetData(), spanning_tree);
}

TEST(SpanningTree, LargeGraph) {
  Graph graph;
  graph.LoadGraphFromFile(kAssetsDir + "graph_example.txt");
  GraphAlgorithms algorithms;

  std::vector<std::vector<size_t>> spanning_tree =
      algorithms.GetLeastSpanningTree(graph);

  size_t size = 0;
  for (size_t i = 0; i < spanning_tree.size(); ++i) {
    for (size_t j = 0; j < spanning_tree[i].size(); ++j) {
      size += spanning_tree[i][j];
    }
  }
  size /= 2;

  ASSERT_EQ(spanning_tree.size(), graph.GetSize());
  ASSERT_EQ(size, 150);
}

}  // namespace s21