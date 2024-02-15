#include "genetic_solver.h"

#include <algorithm>
#include <vector>

namespace s21 {

GeneticAlgorithmTsp::GeneticAlgorithmTsp(Graph &distances,
                                         SelectionStrategy &selection,
                                         CrossoverStrategy &crossover,
                                         MutationStrategy &mutation)
    : distances_(distances),
      selection_(selection),
      crossover_(crossover),
      mutation_(mutation) {}

TsmResult GeneticAlgorithmTsp::Solve(size_t number_generations,
                                     size_t population_size,
                                     double possible_mutation,
                                     double possible_crossover) {
  TsmResult min_path;
  min_path.distance = std::numeric_limits<double>::infinity();
  if (distances_.GetSize() == 0) {
    return min_path;
  }

  Population population = CreatePopulation(population_size);

  for (size_t i = 0; i < number_generations; ++i) {
    population.ComputeFitness(distances_);

    const Chromosome &chromosome = population.GetBestChromosome();
    if (chromosome.genes.size() == (distances_.GetSize() + 1) &&
        chromosome.distance < min_path.distance) {
      min_path.vertices = chromosome.genes;
      min_path.distance = chromosome.distance;
    }
    population = selection_.Execute(population);
    crossover_.Execute(population, possible_crossover);
    mutation_.Execute(population, possible_mutation);
  }

  return min_path;
}

Population GeneticAlgorithmTsp::CreatePopulation(size_t population_size) const {
  std::vector<size_t> vertices(distances_.GetSize());
  std::generate(vertices.begin(), vertices.end(),
                [n = 0]() mutable { return n++; });
  return Population{vertices, population_size};
}

}  // namespace s21
