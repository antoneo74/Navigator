#ifndef SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_GENETIC_ALGORITHM_SELECTION_H_
#define SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_GENETIC_ALGORITHM_SELECTION_H_

#include <random>
#include <set>

#include "model/s21_graph.h"
#include "population.h"

namespace s21 {

class SelectionStrategy {
 public:
  virtual Population Execute(Population &population) = 0;
};

class TournamentSelection : public SelectionStrategy {
 public:
  const size_t kParticipantCount = 3;

  Population Execute(Population &population) override;

 private:
  std::random_device rd_{};
  std::mt19937 gen_{rd_()};

  std::set<size_t> GenerateUniqueRandomNumbers(size_t start, size_t end,
                                               size_t count);
  Chromosome GetWinnerChromosome(Population &population,
                                 const std::set<size_t> &participant_indexes);
};

}  // namespace s21

#endif  // SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_GENETIC_ALGORITHM_SELECTION_H_