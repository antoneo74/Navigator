#ifndef SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_ANT_COLONY_ALGORITHM_PHEROMONE_H_
#define SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_ANT_COLONY_ALGORITHM_PHEROMONE_H_

#include <cstddef>
#include <vector>

#include "model/traveling_salesman/common/path_structure.h"

namespace s21 {

class Pheromones {
 public:
  Pheromones(size_t size, double initial_level, double evaporation_rate);
  double GetValue(size_t from, size_t to) const;
  void Update(const TsmResult &path, double pheromoneQuantiy);

 private:
  std::vector<std::vector<double>> pheromones_;
  double evaporation_rate_;

  void Evapration();
  void Lay(std::vector<size_t> path, double pheromonAverage);
};

}  // namespace s21

#endif  // SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_ANT_COLONY_ALGORITHM_PHEROMONE_H_