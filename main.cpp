#include "include/dpll_solver.h"
#include <iostream>
// #include "include/dpll_solver.h"
// #include "GenBoard.h"
// #include "ConvertBoard.h"
int main() {
  auto solver = std::make_shared<dpll::dpllSolver>("./test.txt");
  if (solver->solve() == dpll::solution_stat::kSolved) {
    std::cout << "solved!" << std::endl;
    solver->show_res(30);
  } else {
    std::cout << "unsolvable!" << std::endl;
  }
  return 0;
}