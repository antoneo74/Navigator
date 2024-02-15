#include "common_tests.h"
#include "model/s21_graph.h"
#include "model/s21_graph_algorithms.h"

namespace s21 {

TEST(Graph, ConstructorWithSize) {
  size_t size = 7;
  Graph graph(size);

  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      size_t value = graph.GetData()[i][j];
      ASSERT_EQ(0, value);
    }
  }
}

TEST(Graph, ConstructorInitValue) {
  size_t size = 7;
  size_t init_value = 13;
  Graph graph(size, init_value);

  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      size_t value = graph.GetData()[i][j];
      ASSERT_EQ(init_value, value);
    }
  }
}

TEST(Graph, SetValueThrow) {
  size_t size = 7;
  Graph graph(size);
  size_t row = 7;
  size_t col = 3;
  size_t value = 13;
  ASSERT_THROW(graph.SetValue(row, col, value), std::out_of_range);

  row = 4;
  graph.SetValue(row, col, value);
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      size_t graph_value = graph.GetData()[i][j];
      if (i == row && j == col) {
        ASSERT_EQ(value, graph_value);
      } else {
        ASSERT_EQ(0, graph_value);
      }
    }
  }
}

TEST(Graph, GetValueThrow) {
  Graph graph;
  graph.LoadGraphFromFile(kAssetsDir + "example3.txt");
  size_t row = 9;
  size_t col = 3;

  ASSERT_THROW(graph.GetValue(row, col), std::out_of_range);

  row = 4;
  size_t value = graph.GetValue(row, col);
  ASSERT_EQ(5, value);
}

TEST(Graph, NeighborsThrow) {
  Graph graph;
  graph.LoadGraphFromFile(kAssetsDir + "example3.txt");
  size_t from = 10;
  ASSERT_THROW(graph.GetNeighbors(from), std::out_of_range);
  from = 1;
  std::vector<size_t> row = graph.GetNeighbors(from);
  std::vector<size_t> expected_result{2, 9, 3, 4, 9};

  ASSERT_EQ(row.size(), expected_result.size());
  for (size_t i = 0; i < row.size(); i++) {
    ASSERT_EQ(row[i], expected_result[i]);
  }
}

TEST(Graph, LoadFromFileThrow) {
  Graph graph;
  ASSERT_THROW(graph.LoadGraphFromFile(kAssetsDir + "file_not_exists"),
               std::runtime_error);
  ASSERT_THROW(graph.LoadGraphFromFile(kAssetsDir + "invalid_matrix.txt"),
               std::length_error);
}

TEST(Graph, GraphIsEmpty) {
  Graph graph(0);
  ASSERT_EQ(graph.GraphIsEmpty(), true);

  graph.LoadGraphFromFile(kAssetsDir + "example3.txt");
  ASSERT_EQ(graph.GraphIsEmpty(), false);
}

TEST(Graph, ParseLineThrow) {
  Graph graph;
  ASSERT_THROW(graph.LoadGraphFromFile(kAssetsDir + "invalid_matrix2.txt"),
               std::length_error);
}

TEST(Graph, ExportToDotThrow) {
  Graph graph;
  graph.LoadGraphFromFile(kAssetsDir + "example2.txt");
  EXPECT_NO_THROW(graph.ExportGraphToDot("filename"));
}

TEST(Graph, ResetThrow) {
  Graph graph;
  EXPECT_NO_THROW(graph.LoadGraphFromFile(kAssetsDir + "example1.txt"));
  EXPECT_NO_THROW(graph.LoadGraphFromFile(kAssetsDir + "example2.txt"));
  EXPECT_NO_THROW(graph.LoadGraphFromFile(kAssetsDir + "example3.txt"));
}

}  // namespace s21