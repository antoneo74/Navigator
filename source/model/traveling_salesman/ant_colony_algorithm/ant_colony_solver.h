#ifndef SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_ANT_COLONY_ALGORITHM_ANT_COLONY_SOLVER_H_
#define SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_ANT_COLONY_ALGORITHM_ANT_COLONY_SOLVER_H_

#include <vector>

#include "ant.h"
#include "model/s21_graph.h"
#include "model/traveling_salesman/common/path_structure.h"

namespace s21 {

class AntColony {
 public:
  const double kPheromoneQuantiy = 15.0;
  const double kPheromoneEvaporationRate = 0.1;
  const double kPheromonInitialLevel = 1;

  AntColony(Graph &graph, size_t count_colony, size_t size_colony);
  TsmResult Solve();

 private:
  Graph &graph_;
  size_t count_colony_;
  size_t size_colony_;
  std::vector<Ant> ant_colony{};
  std::random_device rd_{};
  std::mt19937 gen_{rd_()};

  void CreateAntColony();
};

}  // namespace s21

#endif  // SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_ANT_COLONY_ALGORITHM_ANT_COLONY_SOLVER_H_