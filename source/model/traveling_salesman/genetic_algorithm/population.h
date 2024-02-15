#ifndef SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_GENETIC_ALGORITHM_POPULATION_H_
#define SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_GENETIC_ALGORITHM_POPULATION_H_

#include <vector>

#include "chromosome.h"
#include "model/s21_graph.h"

namespace s21 {

class Population {
 public:
  Population();
  Population(const std::vector<size_t>& vertices, size_t size_population);
  Population(const Population& other);
  Population(const Population&& other);

  Population& operator=(const Population& other);
  Population& operator=(const Population&& other);

  void AddChromosome(Chromosome&& chromosome);
  const Chromosome& GetBestChromosome() const;
  Chromosome& GetChromosome(size_t index);
  size_t GetSize() const;
  void Clear();
  void ComputeFitness(const Graph& dictances);

 private:
  std::vector<Chromosome> populations_;

  void CreatePopulation(const std::vector<size_t>& vertices,
                        size_t size_population);
};

}  // namespace s21

#endif  // SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_GENETIC_ALGORITHM_POPULATION_H_