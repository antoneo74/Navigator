#ifndef SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_GENETIC_ALGORITHM_CROSSOVER_H_
#define SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_GENETIC_ALGORITHM_CROSSOVER_H_

#include <random>
#include <vector>

#include "population.h"

namespace s21 {

struct Range {
  size_t left;
  size_t right;
};

class CrossoverStrategy {
 public:
  virtual void Execute(Population &population, double probability_crossing) = 0;
};

class OrderedCrossover : public CrossoverStrategy {
 public:
  void Execute(Population &population, double probability_crossing = 0.9);

 private:
  std::random_device rd_{};
  std::mt19937 gen_{rd_()};

  void Cross(std::vector<size_t> &genes1, std::vector<size_t> &genes2);
  void ExchangeGenes(std::vector<size_t> &genes1, std::vector<size_t> &genes2,
                     const Range &range);
  Range GenerateRandomRange(size_t max_size);
  void InheritGenes(std::vector<size_t> &new_genes,
                    std::vector<size_t> &old_genes, const Range &range);
};

}  // namespace s21

#endif  // SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_GENETIC_ALGORITHM_CROSSOVER_H_