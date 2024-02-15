#include "mutation.h"

namespace s21 {

void ExchangeMutation::Execute(Population &population,
                               double probability_mutation) {
  std::uniform_real_distribution<double> dist(0.0, 1.0);

  for (size_t i = 0; i < population.GetSize(); i += 1) {
    if (dist(gen_) < probability_mutation) {
      Chromosome &chromosome = population.GetChromosome(i);
      Mutation(chromosome);
    }
  }
}

void ExchangeMutation::Mutation(Chromosome &chromosome) {
  std::uniform_int_distribution<int> dist(0, chromosome.genes.size() - 2);

  size_t point1 = dist(gen_);
  size_t point2 = dist(gen_);

  if (point1 != point2) {
    std::swap(chromosome.genes[point1], chromosome.genes[point2]);
  }

  if (chromosome.genes.front() != chromosome.genes.back()) {
    chromosome.genes.back() = chromosome.genes.front();
  }
}

}  // namespace s21
