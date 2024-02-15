#include "view.h"

#include <cmath>
#include <iostream>

namespace s21 {

void View::Start() {
  bool quit_not_activated = true;
  while (quit_not_activated) {
    Menu();
    try {
      int action = InputNumber();
      switch (action) {
        case 1:
          LoadGraphFromFile();
          break;
        case 2:
          FirstSearch(FirstSearchType::kBreadth);
          break;
        case 3:
          FirstSearch(FirstSearchType::kDepth);
          break;
        case 4:
          GetShortestPathBetweenVertices();
          break;
        case 5:
          MatrixFunctions(MatrixFunctionsType::kShortestPaths);
          break;
        case 6:
          MatrixFunctions(MatrixFunctionsType::kLeastSpanningTree);
          break;
        case 7:
          SolveTravelingSalesmanProblem(AlgoritmSolveTSM::kAntColony);
          break;
        case 8:
          SolveTravelingSalesmanProblem(AlgoritmSolveTSM::kGenetic);
          break;
        case 9:
          SolveTravelingSalesmanProblem(AlgoritmSolveTSM::kSimulatedAnnealing);
          break;
        case 10:
          CompareMethodsSolvingTravelingSalesmanProblem();
          break;
        case 11:
          quit_not_activated = false;
          break;
        default:
          std::cout << "Incorrect input! Try again!\n";
          break;
      }
    } catch (const std::exception &ex) {
      std::cout << ex.what() << std::endl;
    }
  }
}

void View::LoadGraphFromFile() {
  std::cout << "Input file path\n";
  std::string path;
  std::cin >> path;
  controller_.LoadGraphFromFile(path);
}

void View::FirstSearch(FirstSearchType type) {
  if (CheckGraph()) {
    std::cout << "First load graph!\n";
    return;
  }

  std::cout << "Input start vertex\n";
  try {
    size_t start = InputNumber();
    std::vector<size_t> result = type == FirstSearchType::kBreadth
                                     ? controller_.BreadthFirstSearch(start)
                                     : controller_.DepthFirstSearch(start);
    PrintVector(result);
  } catch (const std::exception &ex) {
    std::cout << "Incorrect number of vertex! Try again!\n";
  }
}

void View::GetShortestPathBetweenVertices() {
  if (CheckGraph()) {
    std::cout << "First load graph!\n";
    return;
  }

  try {
    std::cout << "Input start vertex\n";
    size_t start_vertex = InputNumber();
    std::cout << "Input finish vertex\n";
    size_t finish_vertex = InputNumber();

    size_t result =
        controller_.GetShortestPathBetweenVertices(start_vertex, finish_vertex);
    std::cout << result << std::endl;
  } catch (const std::exception &ex) {
    std::cout << "Incorrect number of vertex! Try again!\n";
  }
}

void View::MatrixFunctions(MatrixFunctionsType type) {
  if (CheckGraph()) {
    std::cout << "First load graph!\n";
    return;
  }

  std::vector<std::vector<size_t>> result =
      type == MatrixFunctionsType::kShortestPaths
          ? controller_.GetShortestPathsBetweenAllVertices()
          : controller_.GetLeastSpanningTree();
  PrintMatrix(result);
}

void View::SolveTravelingSalesmanProblem(AlgoritmSolveTSM type) {
  if (CheckGraph()) {
    std::cout << "First load graph!\n";
    return;
  }

  TsmResult result;
  switch (type) {
    case AlgoritmSolveTSM::kAntColony:
      result = controller_.SolveTravelingSalesmanProblem();
      break;
    case AlgoritmSolveTSM::kGenetic:
      result = controller_.SolveTravelingSalesmanProblemGeneticAlgorithm();
      break;
    case AlgoritmSolveTSM::kSimulatedAnnealing:
      result = controller_.SolveTravelingSalesmanProblemSimulatedAnnealing();
      break;
  }

  if (std::isinf(result.distance)) {
    std::cout << "No solution to the traveling salesman problem found"
              << std::endl;
  } else {
    std::cout << "Path: ";
    PrintVector(result.vertices);
    std::cout << "Distance: " << result.distance << std::endl;
  }
}

void View::CompareMethodsSolvingTravelingSalesmanProblem() {
  if (CheckGraph()) {
    std::cout << "First load graph!\n";
    return;
  }

  std::cout << "Enter the number of reruns for each algorithm for solving "
               "the traveling salesman problem:\n";
  try {
    size_t number = InputNumber();
    std::chrono::milliseconds time_ant_colony =
        MeasureTime(AlgoritmSolveTSM::kAntColony, number);
    std::chrono::milliseconds time_genetic =
        MeasureTime(AlgoritmSolveTSM::kGenetic, number);
    std::chrono::milliseconds time_simulated_annealing =
        MeasureTime(AlgoritmSolveTSM::kSimulatedAnnealing, number);

    std::cout << "Running time algorithms: " << std::endl;
    std::cout << "Ant colony: " << time_ant_colony.count() << " ms"
              << std::endl;
    std::cout << "Genetic:    " << time_genetic.count() << " ms" << std::endl;
    std::cout << "Simulated annealing:    " << time_simulated_annealing.count()
              << " ms" << std::endl;
  } catch (const std::exception &ex) {
    std::cout << ex.what() << std::endl;
  }
}

void View::Menu() {
  std::cout << "\nSelect action" << std::endl;
  std::cout << "_____________________________________________\n";
  std::cout << "1) Load graph from file" << std::endl;
  std::cout << "2) Breadth first search" << std::endl;
  std::cout << "3) Depth first search" << std::endl;
  std::cout << "4) Get shortest path between two vertices" << std::endl;
  std::cout << "5) Get shortest paths between all vertices" << std::endl;
  std::cout << "6) Get least spanning tree" << std::endl;
  std::cout << "7) Solve traveling salesman problem using an ant algorithm"
            << std::endl;
  std::cout << "8) Solve traveling salesman problem using a genetic algorithm"
            << std::endl;
  std::cout << "9) Solve traveling salesman problem using a simulated "
               "annealing algorithm"
            << std::endl;
  std::cout << "10) Compare methods for solving the traveling salesman problem"
            << std::endl;
  std::cout << "11) Quit" << std::endl;
  std::cout << "_____________________________________________\n";
}

void View::PrintVector(const std::vector<size_t> &vector) {
  for (size_t i = 0; i < vector.size(); ++i) {
    std::cout << vector[i] + 1 << " ";
  }
  std::cout << std::endl;
}

void View::PrintMatrix(const std::vector<std::vector<size_t>> &matrix) {
  for (size_t i = 0; i < matrix.size(); ++i) {
    for (size_t j = 0; j < matrix.size(); ++j) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

bool View::CheckGraph() { return controller_.GraphIsEmpty(); }

size_t View::InputNumber() {
  size_t number;
  std::cin >> number;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    throw std::invalid_argument("Not a number entered");
  }
  return number;
}

std::chrono::milliseconds View::MeasureTime(AlgoritmSolveTSM algorithm,
                                            size_t number) {
  auto begin = std::chrono::steady_clock::now();
  for (size_t i = 0; i < number; ++i) {
    switch (algorithm) {
      case AlgoritmSolveTSM::kAntColony:
        controller_.SolveTravelingSalesmanProblem();
        break;
      case AlgoritmSolveTSM::kGenetic:
        controller_.SolveTravelingSalesmanProblemGeneticAlgorithm();
        break;
      case AlgoritmSolveTSM::kSimulatedAnnealing:
        controller_.SolveTravelingSalesmanProblemSimulatedAnnealing();
        break;
      default:
        break;
    }
  }

  auto end = std::chrono::steady_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
}

}  // namespace s21
