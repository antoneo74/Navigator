#include <iostream>

#include "controller/controller.h"
#include "model/s21_graph.h"
#include "view/view.h"

int main() {
  s21::Graph model;
  s21::Controller controller(model);
  s21::View view(controller);
  view.Start();
  return 0;
}
