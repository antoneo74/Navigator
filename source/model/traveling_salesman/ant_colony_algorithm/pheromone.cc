#include "pheromone.h"

#include <iomanip>

namespace s21 {

Pheromones::Pheromones(size_t size, double initial_level,
                       double evaporation_rate)
    : pheromones_(std::vector<std::vector<double>>(
          size, std::vector<double>(size, initial_level))),
      evaporation_rate_(evaporation_rate) {
  for (size_t i = 0; i < pheromones_.size(); ++i) {
    pheromones_[i][i] = 0;
  }
}

double Pheromones::GetValue(size_t from, size_t to) const {
  return pheromones_[from][to];
}

void Pheromones::Update(const TsmResult &path, double pheromoneQuantiy) {
  double pheromonAverage = pheromoneQuantiy / path.distance;
  Lay(path.vertices, pheromonAverage);
  Evapration();
}

void Pheromones::Lay(std::vector<size_t> path, double pheromonAverage) {
  for (size_t i = 0; i < path.size() - 1; ++i) {
    size_t index_left = path[i];
    size_t index_right = path[i + 1];
    pheromones_[index_left][index_right] += pheromonAverage;
    pheromones_[index_right][index_left] += pheromonAverage;
  }
}

void Pheromones::Evapration() {
  for (size_t i = 0; i < pheromones_.size(); ++i) {
    for (size_t j = 0; j < pheromones_.size(); ++j) {
      pheromones_[i][j] *= (1 - evaporation_rate_);
    }
  }
}

}  // namespace s21
