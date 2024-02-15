#include "controller.h"

namespace s21 {

void Controller::LoadGraphFromFile(std::string filename) {
  graph_.LoadGraphFromFile(filename);
}

std::vector<size_t> Controller::BreadthFirstSearch(size_t start_vertex) {
  return algorithms_.BreadthFirstSearch(graph_, start_vertex);
}

std::vector<size_t> Controller::DepthFirstSearch(size_t start_vertex) {
  return algorithms_.DepthFirstSearch(graph_, start_vertex);
}

size_t Controller::GetShortestPathBetweenVertices(size_t vertex1,
                                                  size_t vertex2) {
  return algorithms_.GetShortestPathBetweenVertices(graph_, vertex1, vertex2);
}

std::vector<std::vector<size_t>>
Controller::GetShortestPathsBetweenAllVertices() {
  return algorithms_.GetShortestPathsBetweenAllVertices(graph_);
}

std::vector<std::vector<size_t>> Controller::GetLeastSpanningTree() {
  return algorithms_.GetLeastSpanningTree(graph_);
}

TsmResult Controller::SolveTravelingSalesmanProblem() {
  return algorithms_.SolveTravelingSalesmanProblem(graph_);
}

TsmResult Controller::SolveTravelingSalesmanProblemGeneticAlgorithm() {
  return algorithms_.SolveTravelingSalesmanProblemGeneticAlgorithm(graph_);
}

TsmResult s21::Controller::SolveTravelingSalesmanProblemSimulatedAnnealing() {
  return algorithms_.SolveTravelingSalesmanProblemSimulatedAnnealing(graph_);
}

bool Controller::GraphIsEmpty() { return graph_.GraphIsEmpty(); }
}  // namespace s21
