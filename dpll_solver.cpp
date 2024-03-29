#include "include/dpll_solver.h"
#include <iostream>
namespace dpll {

int dpllSolver::solve() {
  std::vector<dpll::var_stat> last_solve = results;
  int split_pos = 0;
  while (1) {
    auto [mark, last_single_ptr] = this->get_solve_stat();
    if (mark == solution_stat::kSolved) {
      return mark;
    }
    if (mark == solution_stat::kUnsolvable) {
      results = last_solve;
      return mark;
    }
    if (mark == solution_stat::kHasSingleCla) {
      for (auto d : last_single_ptr->data) {
        if (results[std::abs(d)] == var_stat::kUnknown) {
          results[std::abs(d)] = (d > 0) ? var_stat::kSat : var_stat::kUnsat;
          break;
        }
      }
    }
    if (mark == solution_stat::kNeedSplit) {
      split_pos = get_next_split();
      if (split_pos == 0) {
        break;
      }
      results[split_pos] = var_stat::kSat;
      mark = this->solve();
      if (mark == solution_stat::kSolved) {
        return mark;
      }
      results[split_pos] = var_stat::kUnsat;
      mark = this->solve();
      if (mark == solution_stat::kSolved) {
        return mark;
      }
      results = last_solve;
      results[split_pos] = var_stat::kUnknown;
      return solution_stat::kUnsolvable;
    }
  }
  return solution_stat::kUnsolvable;
}

int dpllSolver::read(std::string path) {
  this->cla_set = dpll::clauseSet(path);
  results.resize(this->cla_set.var_count + 1, var_stat::kUnknown);
  return 0;
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
    if (i % size == 0) {
      std::cout << std::endl;
    }
  }
  std::cout << std::endl;
  return;
}

std::tuple<int, const clause *> dpllSolver::get_solve_stat() {
  const clause *last_single_ptr = nullptr;
  int mark = solution_stat::kSolved;
  int res = 0;
  for (auto &cla : this->cla_set.clause_vec) {
    int valid_var = cla.data.size();
    for (auto item : cla.data) {
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
      return {solution_stat::kUnsolvable, nullptr};
    }
    if (valid_var == 1) {
      // current is single
      last_single_ptr = &cla;
      continue;
    }
    mark = solution_stat::kNeedSplit;
  }
  if (last_single_ptr) {
    return {solution_stat::kHasSingleCla, last_single_ptr};
  }
  return {mark, nullptr};
}

int dpllSolver::get_next_split() {
  for (size_t i = 1; i < this->results.size(); i++) {
    if (results[i] == var_stat::kUnknown) {
      return i;
    }
  }
  return 0;
}

} // namespace dpll