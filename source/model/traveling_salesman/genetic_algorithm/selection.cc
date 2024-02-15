#include "selection.h"

#include <algorithm>

namespace s21 {

Population TournamentSelection::Execute(Population &population) {
  if (population.GetSize() == 0) {
    return Population{};
  }

  Population new_population;
  size_t number_participants =
      std::min(kParticipantCount, population.GetSize() - 1);

  while (new_population.GetSize() < population.GetSize()) {
    std::set<size_t> participant_indexes = GenerateUniqueRandomNumbers(
        0, population.GetSize() - 1, number_participants);
    Chromosome winner = GetWinnerChromosome(population, participant_indexes);
    new_population.AddChromosome(std::move(winner));
  }

  return new_population;
}

Chromosome TournamentSelection::GetWinnerChromosome(
    Population &population, const std::set<size_t> &participant_indexes) {
  auto winner =
      std::min_element(participant_indexes.begin(), participant_indexes.end(),
                       [&population](const size_t ind1, const size_t ind2) {
                         return population.GetChromosome(ind1).distance <
                                population.GetChromosome(ind2).distance;
                       });

  Chromosome &chromosome = population.GetChromosome(*winner);
  return Chromosome{chromosome.genes, chromosome.distance};
}

std::set<size_t> TournamentSelection::GenerateUniqueRandomNumbers(
    size_t start, size_t end, size_t count) {
  if (start > end) {
    throw std::invalid_argument("Start must be less than end");
  }

  std::set<size_t> numbers;
  std::uniform_int_distribution<size_t> dist(start, end);
  while (numbers.size() < count && numbers.size() < (end - start)) {
    size_t index = dist(gen_);
    numbers.insert(index);
  }

  return numbers;
}

}  // namespace s21
