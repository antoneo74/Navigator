#include "ant.h"

#include <cmath>

namespace s21 {

Ant::Ant(Graph &distances, std::mt19937 &gen, double pheromon_quantiy)
    : distances_(distances),
      gen_(gen),
      pheromon_quantiy_(pheromon_quantiy),
      used_vertex_(std::vector<bool>(distances.GetSize(), false)) {
  std::uniform_int_distribution<size_t> dist_{0, distances.GetSize() - 1};
  size_t start_vertex = dist_(gen_);
  path_.vertices.push_back(start_vertex);
  used_vertex_[start_vertex] = true;
  path_.distance = 0;
}

bool Ant::Move(const Pheromones &pheromones) {
  std::vector<size_t> neighbors = GetVerticesPossibleNeighbors();
  if (neighbors.empty() && path_.vertices.size() == distances_.GetSize()) {
    path_.distance +=
        GetDistanceBetweenVertices(GetLastVertex(), GetFirstVertex());
    path_.vertices.push_back(GetFirstVertex());
  }

  if (neighbors.empty()) {
    return false;
  }

  std::vector<double> probabilities = GetProbabilities(pheromones, neighbors);
  double probability = GetRandomProbability();

  for (size_t i = 0; i < probabilities.size(); ++i) {
    if (probability <= probabilities[i]) {
      size_t next_vertex = neighbors[i];
      path_.distance +=
          GetDistanceBetweenVertices(GetLastVertex(), next_vertex);
      path_.vertices.push_back(next_vertex);
      used_vertex_[next_vertex] = true;
      break;
    }
  }

  return true;
}

const TsmResult &Ant::GetPath() const { return path_; }

double Ant::GetPheromonQuantiy() const { return pheromon_quantiy_; }

double Ant::GetDistanceBetweenVertices(size_t from, size_t to) const {
  size_t distance = distances_.GetValue(from, to);
  if (distance == 0 && from != to) {
    return std::numeric_limits<double>::infinity();
  }

  return static_cast<double>(distance);
}

size_t Ant::GetFirstVertex() { return path_.vertices.front(); }

size_t Ant::GetLastVertex() { return path_.vertices.back(); }

std::vector<double> Ant::GetProbabilities(const Pheromones &pheromones,
                                          std::vector<size_t> &neighbors) {
  std::vector<double> probabilities;
  probabilities.reserve(neighbors.size());

  double summaryWeight = CalcSummaryWeight(pheromones, neighbors);

  size_t current_vertex = GetLastVertex();
  for (auto &neighbor : neighbors) {
    double probability =
        pow(kDistance / distances_.GetValue(current_vertex, neighbor), kBetta) *
        pow(pheromones.GetValue(current_vertex, neighbor), kAlpha) /
        summaryWeight;
    if (probabilities.empty()) {
      probabilities.push_back(probability);
    } else {
      probabilities.push_back(probabilities.back() + probability);
    }
  }

  return probabilities;
}

double Ant::GetRandomProbability() {
  std::uniform_real_distribution<double> dist_{0.0, 1.0};
  double probability = dist_(gen_);
  return probability;
}

std::vector<size_t> Ant::GetVerticesPossibleNeighbors() {
  size_t current_vertex = GetLastVertex();
  std::vector<size_t> neighbors;

  for (size_t to_vertex = 0; to_vertex < distances_.GetSize(); ++to_vertex) {
    if (to_vertex != current_vertex && !used_vertex_[to_vertex] &&
        distances_.GetValue(current_vertex, to_vertex) != 0) {
      neighbors.push_back(to_vertex);
    }
  }

  return neighbors;
}

double Ant::CalcSummaryWeight(const Pheromones &pheromones,
                              std::vector<size_t> &neighbors) {
  size_t current_vertex = GetLastVertex();

  double summaryWeight = std::accumulate(
      neighbors.begin(), neighbors.end(), 0.0,
      [&](double acc, const auto &neighbor) {
        return acc +
               pow(kDistance / distances_.GetValue(current_vertex, neighbor),
                   kBetta) *
                   pow(pheromones.GetValue(current_vertex, neighbor), kAlpha);
      });

  return summaryWeight;
}

}  // namespace s21
