#include "crossover.h"

#include <algorithm>
#include <unordered_set>

#include "chromosome.h"

namespace s21 {

void OrderedCrossover::Execute(Population &population,
                               double probability_crossing) {
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  std::uniform_int_distribution<size_t> dist_int(1, population.GetSize() - 1);
  size_t offset = dist_int(gen_);

  for (size_t i = 0; i < population.GetSize(); i += 1) {
    if (dist(gen_) < probability_crossing) {
      Chromosome &parent1 = population.GetChromosome(i);
      Chromosome &parent2 =
          population.GetChromosome((i + offset) % population.GetSize());
      Cross(parent1.genes, parent2.genes);
    }
  }
}

void OrderedCrossover::Cross(std::vector<size_t> &genes1,
                             std::vector<size_t> &genes2) {
  Range range = GenerateRandomRange(genes1.size());
  if (range.left == range.right) {
    return;
  }

  std::vector<size_t> old_genes1(genes1);
  std::vector<size_t> old_genes2(genes2);

  ExchangeGenes(genes1, genes2, range);
  InheritGenes(genes1, old_genes1, range);
  InheritGenes(genes2, old_genes2, range);
}

void OrderedCrossover::ExchangeGenes(std::vector<size_t> &genes1,
                                     std::vector<size_t> &genes2,
                                     const Range &range) {
  if (genes1.size() != genes2.size()) {
    return;
  }

  std::swap_ranges(genes1.begin() + range.left, genes1.begin() + range.right,
                   genes2.begin() + range.left);
}

Range OrderedCrossover::GenerateRandomRange(size_t max_size) {
  if (max_size == 0) {
    return Range{0, 0};
  }

  std::uniform_int_distribution<size_t> dist(0, max_size - 1);
  size_t point1 = dist(gen_);
  size_t point2 = dist(gen_);

  return Range{std::min(point1, point2), std::max(point1, point2)};
}

void OrderedCrossover::InheritGenes(std::vector<size_t> &new_genes,
                                    std::vector<size_t> &old_genes,
                                    const Range &range) {
  size_t ind_dst = 0;

  for (size_t i = 0; i < old_genes.size() - 1; ++i) {
    size_t ind_src = (range.right + i) % (old_genes.size() - 1);
    auto it = std::find(new_genes.begin() + range.left,
                        new_genes.begin() + range.right, old_genes[ind_src]);

    if (it == new_genes.begin() + range.right) {
      new_genes[(ind_dst + range.right) % (new_genes.size() - 1)] =
          old_genes[ind_src];
      ind_dst += 1;
    }
  }

  if (new_genes.front() != new_genes.back()) {
    new_genes.back() = new_genes.front();
  }
}

}  // namespace s21
