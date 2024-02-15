#ifndef SIMPLE_NAVIGATOR_SOURCE_VIEW_VIEW_H_
#define SIMPLE_NAVIGATOR_SOURCE_VIEW_VIEW_H_

#include <chrono>
#include <cstddef>

#include "controller/controller.h"

namespace s21 {
class View {
 public:
  enum class AlgoritmSolveTSM { kAntColony, kGenetic, kSimulatedAnnealing };
  enum class MatrixFunctionsType { kShortestPaths, kLeastSpanningTree };
  enum class FirstSearchType { kBreadth, kDepth };

  explicit View(Controller& controller) : controller_(controller) {}
  void Start();

 private:
  Controller controller_;
  void LoadGraphFromFile();
  void FirstSearch(FirstSearchType type);
  void GetShortestPathBetweenVertices();
  void MatrixFunctions(MatrixFunctionsType type);
  void SolveTravelingSalesmanProblem(AlgoritmSolveTSM type);
  void CompareMethodsSolvingTravelingSalesmanProblem();
  void Menu();
  void PrintVector(const std::vector<size_t>& vector);
  void PrintMatrix(const std::vector<std::vector<size_t>>& matrix);
  bool CheckGraph();
  size_t InputNumber();
  std::chrono::milliseconds MeasureTime(AlgoritmSolveTSM algorithm,
                                        size_t number);
};

}  // namespace s21

#endif  // SIMPLE_NAVIGATOR_SOURCE_VIEW_VIEW_H_