#ifndef SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_COMMON_PATH_STRUCTURE_H_
#define SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_COMMON_PATH_STRUCTURE_H_

#include <cstddef>
#include <vector>

namespace s21 {

struct TsmResult {
  std::vector<size_t> vertices;
  double distance;
};

}  // namespace s21

#endif  // SIMPLE_NAVIGATOR_SOURCE_MODEL_TRAVELING_SALESMAN_COMMON_PATH_STRUCTURE_H_