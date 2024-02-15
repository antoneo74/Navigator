#include "simulated_annealing.h"

#include <algorithm>

namespace s21 {

SimulatedAnnealing::SimulatedAnnealing(const Graph &graph,
                                       const AnnealingParams &params)
    : graph_(graph), params_(params) {}

TsmResult SimulatedAnnealing::Solve() const {
  if (graph_.GraphIsEmpty()) {
    return TsmResult();
  }

  TsmResult best_solution = GenInitalPath();
  for (size_t i = 0; i < params_.algorithm_reloads; ++i) {
    TsmResult current_solution = GenInitalPath();
    double temperature = params_.start_temperature;

    size_t t = 2;
    while (temperature > params_.min_temperature) {
      TsmResult new_solution = RandomSwap(current_solution);

      double delta_cost = new_solution.distance - current_solution.distance;

      if (AcceptSolution(delta_cost, temperature)) {
        current_solution = new_solution;
        if (current_solution.distance < best_solution.distance) {
          best_solution = current_solution;
        }
      }

      temperature = params_.calculate_new_temperature(temperature, t);
      ++t;
    }
  }

  return best_solution;
}

TsmResult SimulatedAnnealing::GenInitalPath() const {
  std::vector<size_t> path;
  for (size_t i = 0; i < graph_.GetSize(); ++i) {
    path.push_back(i);
  }

  std::shuffle(path.begin(), path.end(), random_generator_);
  path.push_back(*path.begin());

  return {path, CalculateTotalDistance(path)};
}

double SimulatedAnnealing::CalculateTotalDistance(
    const std::vector<size_t> &path) const {
  double distance = 0;

  for (size_t i = 0; i < path.size() - 1; i++) {
    size_t currentVertex = path[i];
    size_t nextVertex = path[i + 1];
    if (graph_.GetValue(currentVertex, nextVertex) == 0 &&
        currentVertex != nextVertex) {
      distance = std::numeric_limits<double>::infinity();
      break;
    }
    distance += graph_.GetValue(currentVertex, nextVertex);
  }

  return distance;
}

bool SimulatedAnnealing::AcceptSolution(double delta_cost,
                                        double temperature) const {
  if (delta_cost < 0) {
    return true;
  } else {
    double probability =
        params_.calculate_transition_probability(delta_cost, temperature);
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(random_generator_) < probability;
  }
}

TsmResult SimulatedAnnealing::RandomSwap(const TsmResult &solution) const {
  TsmResult new_solution = solution;

  if (new_solution.vertices.size() > 2) {
    std::uniform_int_distribution<size_t> distribution(
        1, new_solution.vertices.size() - 2);
    size_t index1 = distribution(random_generator_);
    size_t index2 = distribution(random_generator_);

    std::swap(new_solution.vertices[index1], new_solution.vertices[index2]);
  }

  new_solution.distance = CalculateTotalDistance(new_solution.vertices);

  return new_solution;
}
}  // namespace s21