#include "include/dpll_solver.h"
#include <iostream>

int main(int argc, char *argv[]) {
  auto solver = dpll::dpllSolver("./cnf_examples/sat/M/"
                                 "sud00861.cnf");
  if (solver.solve() == dpll::solution_stat::kSolved) {
    std::cout << "solved!" << std::endl;
    solver.show_res(30);
  } else {
    std::cout << "unsolvable!" << std::endl;
  }
  return 0;
}