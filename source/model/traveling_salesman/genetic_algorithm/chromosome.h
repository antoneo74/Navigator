#ifndef SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_GENETIC_ALGORITHM_CHROMOSOME_H_
#define SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_GENETIC_ALGORITHM_CHROMOSOME_H_

#include <cstddef>
#include <limits>
#include <stdexcept>
#include <vector>

#include "model/s21_graph.h"

namespace s21 {

struct Chromosome {
  std::vector<size_t> genes;
  double distance;

  void UpdateDistance(const Graph &distances) {
    if (genes.size() < 2) {
      throw std::invalid_argument("Chromosome size < 2");
    }

    distance = 0;

    for (size_t i = 0; i < genes.size() - 1; ++i) {
      if (genes[i] != genes[i + 1] &&
          distances.GetValue(genes[i], genes[i + 1]) == 0) {
        distance = std::numeric_limits<double>::infinity();
        break;
      };
      distance += distances.GetValue(genes[i], genes[i + 1]);
    }
  }
};

}  // namespace s21

#endif  // SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_GENETIC_ALGORITHM_CHROMOSOME_H_