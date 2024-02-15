#ifndef SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_GENETIC_ALGORITHM_GENETIC_SOLVER_H_
#define SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_GENETIC_ALGORITHM_GENETIC_SOLVER_H_

#include "crossover.h"
#include "model/s21_graph.h"
#include "model/traveling_salesman/common/path_structure.h"
#include "mutation.h"
#include "population.h"
#include "selection.h"

namespace s21 {

class GeneticAlgorithmTsp {
 public:
  GeneticAlgorithmTsp(Graph &distances, SelectionStrategy &selection,
                      CrossoverStrategy &crossover, MutationStrategy &mutation);
  TsmResult Solve(size_t number_generations = 10, size_t population_size = 200,
                  double possible_mutation = 0.01,
                  double possible_crossover = 0.9);

 private:
  Graph &distances_;
  SelectionStrategy &selection_;
  CrossoverStrategy &crossover_;
  MutationStrategy &mutation_;

  Population CreatePopulation(size_t population_size) const;
};

}  // namespace s21

#endif  // SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_GENETIC_ALGORITHM_GENETIC_SOLVER_H_