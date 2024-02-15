
#include "common_tests.h"
#include "model/s21_graph.h"
#include "model/s21_graph_algorithms.h"

namespace s21 {

class TestDepthFirstSearch : public ::testing::Test {
protected:
  void SetUp() { graph.LoadGraphFromFile(kAssetsDir + "example2.txt"); }

  Graph graph;
  GraphAlgorithms algorithms;
  std::vector<size_t> expected_result{3, 1, 2,  5,  6,  7, 8,
                                      9, 4, 10, 11, 12, 13};
};

TEST_F(TestDepthFirstSearch, test1Throw) {
  size_t vertex = 0;
  ASSERT_THROW(algorithms.DepthFirstSearch(graph, vertex),
               std::invalid_argument);
}

TEST_F(TestDepthFirstSearch, test2Throw) {
  size_t vertex = 15;
  ASSERT_THROW(algorithms.DepthFirstSearch(graph, vertex);, std::out_of_range);
}

TEST_F(TestDepthFirstSearch, test3) {
  size_t vertex = 3;
  std::vector<size_t> result = algorithms.DepthFirstSearch(graph, vertex);
  ASSERT_EQ(result.size(), expected_result.size());
}

TEST_F(TestDepthFirstSearch, test4) {
  size_t vertex = 3;
  std::vector<size_t> result = algorithms.DepthFirstSearch(graph, vertex);
  for (size_t i = 0; i < result.size(); ++i) {
    ASSERT_EQ(result[i], expected_result[i] - 1);
  }
}

class TestBreadthFirstSearch : public ::testing::Test {
protected:
  void SetUp() { graph.LoadGraphFromFile(kAssetsDir + "example2.txt"); }

  Graph graph;
  GraphAlgorithms algorithms;
  std::vector<size_t> expected_result{1, 2, 3,  4,  5, 10, 13,
                                      6, 9, 11, 12, 7, 8};
};

TEST_F(TestBreadthFirstSearch, test1Throw) {
  size_t vertex = 0;
  ASSERT_THROW(algorithms.BreadthFirstSearch(graph, vertex),
               std::invalid_argument);
}

TEST_F(TestBreadthFirstSearch, test2Throw) {
  size_t vertex = 15;
  ASSERT_THROW(algorithms.BreadthFirstSearch(graph, vertex);
               , std::out_of_range);
}

TEST_F(TestBreadthFirstSearch, test3) {
  size_t vertex = 1;
  std::vector<size_t> result = algorithms.BreadthFirstSearch(graph, vertex);
  ASSERT_EQ(result.size(), expected_result.size());
}

TEST_F(TestBreadthFirstSearch, test4) {
  size_t vertex = 1;
  std::vector<size_t> result = algorithms.BreadthFirstSearch(graph, vertex);
  for (size_t i = 0; i < result.size(); ++i) {
    ASSERT_EQ(result[i], expected_result[i] - 1);
  }
}

class TestGetShortestPathBetweenVertices : public ::testing::Test {
protected:
  void SetUp() { graph.LoadGraphFromFile(kAssetsDir + "example3.txt"); }

  Graph graph;
  GraphAlgorithms algorithms;
};

TEST_F(TestGetShortestPathBetweenVertices, test1Throw) {
  size_t vertex1 = 0;
  size_t vertex2 = 8;
  ASSERT_THROW(
      algorithms.GetShortestPathBetweenVertices(graph, vertex1, vertex2),
      std::invalid_argument);
}

TEST_F(TestGetShortestPathBetweenVertices, test2Throw) {
  size_t vertex1 = 1;
  size_t vertex2 = 10;
  ASSERT_THROW(
      algorithms.GetShortestPathBetweenVertices(graph, vertex1, vertex2);
      , std::out_of_range);
}

TEST_F(TestGetShortestPathBetweenVertices, test3) {
  size_t vertex1 = 1;
  size_t vertex2 = 8;
  size_t result =
      algorithms.GetShortestPathBetweenVertices(graph, vertex1, vertex2);
  ASSERT_EQ(result, 11);
}

class TestGetShortestPathsBetweenAllVertices : public ::testing::Test {
protected:
  void SetUp() { graph.LoadGraphFromFile(kAssetsDir + "example3.txt"); }

  Graph graph;
  GraphAlgorithms algorithms;

  size_t expected_result[9][9] = {
      {0, 2, 6, 5, 10, 6, 3, 11, 10},  {2, 0, 8, 3, 8, 4, 5, 9, 8},
      {6, 8, 0, 7, 12, 12, 9, 17, 16}, {5, 3, 7, 0, 5, 5, 8, 10, 9},
      {10, 8, 12, 5, 0, 10, 8, 9, 10}, {6, 4, 12, 5, 10, 0, 9, 5, 4},
      {3, 5, 9, 8, 8, 9, 0, 14, 13},   {11, 9, 17, 10, 9, 5, 14, 0, 1},
      {10, 8, 16, 9, 10, 4, 13, 1, 0}};
};

TEST_F(TestGetShortestPathsBetweenAllVertices, test1) {
  std::vector<std::vector<size_t>> result =
      algorithms.GetShortestPathsBetweenAllVertices(graph);

  for (size_t i = 0; i < result.size(); ++i) {
    for (size_t j = 0; j < result.size(); ++j) {
      ASSERT_EQ(result[i][j], expected_result[i][j]);
    }
  }
}

} // namespace s21
