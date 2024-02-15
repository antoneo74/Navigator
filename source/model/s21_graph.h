#ifndef SIMPLE_NAVIGATOR_SOURCE_MODEL_S21_GRAPH_H_
#define SIMPLE_NAVIGATOR_SOURCE_MODEL_S21_GRAPH_H_

#include <cstddef>
#include <string>
#include <vector>

namespace s21 {

class Graph {
 public:
  using MatrixAdjacency = std::vector<std::vector<size_t>>;

  Graph() = default;
  explicit Graph(size_t size);
  Graph(size_t size, size_t init_value);

  void SetValue(size_t row, size_t column, size_t value);
  MatrixAdjacency &GetData();
  size_t GetValue(size_t row, size_t column) const;
  size_t GetSize() const;
  std::vector<size_t> GetNeighbors(size_t from) const;
  void LoadGraphFromFile(std::string filename);
  void ExportGraphToDot(std::string filename) const;
  bool GraphIsEmpty() const;

 private:
  MatrixAdjacency matrix_;
  size_t size_ = 0;
  void ParseSize(std::string line);
  void ParseLine(std::string line, size_t row);
  void Reset();
};

}  // namespace s21

#endif  // SIMPLE_NAVIGATOR_SOURCE_MODEL_S21_GRAPH_H_