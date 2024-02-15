#ifndef SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_SIMULATED_ANNEALING_ANNEALING_PARAMS_H_
#define SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_SIMULATED_ANNEALING_ANNEALING_PARAMS_H_

#include <cmath>
#include <cstddef>
#include <functional>

namespace s21 {
struct AnnealingParams {
  const double start_temperature{100};
  const double min_temperature{std::numeric_limits<double>::min()};
  const size_t algorithm_reloads{100};

  const std::function<double(double, size_t)> calculate_new_temperature{
      [](double temperature, size_t t) { return temperature / log10(t); }};

  const std::function<double(double, double)> calculate_transition_probability{
      [](double delta_cost, double temperature) {
        return exp(-delta_cost / temperature);
      }};
};

}  // namespace s21

#endif  // SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_SIMULATED_ANNEALING_ANNEALING_PARAMS_H_