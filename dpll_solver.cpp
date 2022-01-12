#include "include/dpll_solver.h"
namespace dpll {

int dpllSolver::read(std::string path) {
  this->cla_set_ptr = std::make_shared<clauseSet>(path);
  if (!this->cla_set_ptr) {
    return -1;
  }
  results.resize(this->cla_set_ptr->var_count + 1, var_stat::kUnknown);
  return 0;
}

int dpllSolver::get_cla_unknown_var(clausePtr cla_ptr) {
  if (!cla_ptr) {
    return 0;
  }
  for (auto &item : cla_ptr->data) {
    if (this->results[std::abs(item)] == kUnknown) {
      return item;
    }
  }
  return 0;
}

int dpllSolver::get_solve_stat() {
  int mark = solution_stat::kSolved;
  int res = 0;
  clausePtr last_single_cla = nullptr;
  for (auto &cla_ptr : this->cla_set_ptr->clause_vec) {
    size_t valid_var = cla_ptr->data.size();
    for (auto &item : cla_ptr->data) {
      res = item * results[abs(item)];
      if (res > 0) {
        valid_var = -1;
        break;
      } else if (res < 0) {
        valid_var--;
      }
    }
    // change solve status by current clause
    if (valid_var == -1) {
      // current satisfied
      continue;
    }
    if (valid_var == 0) {
      // current empty
      return solution_stat::kUnsolvable;
    }
    if (valid_var == 1) {
      // current is single
      last_single_cla = cla_ptr;
      continue;
    }
    mark = solution_stat::kNeedSplit;
  }
  if (last_single_cla) {
    return solution_stat::kHasSingleCla;
  }
  return mark;
}

void dpllSolver::show_res(size_t size) {
  for (size_t i = 1; i < results.size(); i++) {
    const auto &cur_res = results[i];
    if (cur_res == var_stat::kSat) {
      std::cout << "y ";
    } else if (cur_res == var_stat::kUnsat) {
      std::cout << "n ";
    } else if (cur_res == var_stat::kUnknown) {
      std::cout << "_ ";
    }
    if ((i - 1) % size == 0) {
      std::cout << std::endl;
    }
  }
  return;
}

} // namespace dpll