#include "clause.h"

namespace dpll {
enum var_stat : int8_t { kUnsat = -1, kUnknown = 0, kSat = 1 };
enum solution_stat : int8_t {
  kUnsolvable = -1,
  kSolved = 0,
  kNeedSplit = 1,
  kHasSingleCla = 2
};

class dpllSolver {
public:
  dpllSolver(){};
  dpllSolver(std::string path) {
    if (read(path)) {
      throw;
    }
  }
  ~dpllSolver(){};

  int solve();
  void show_res(size_t size);

private:
  clauseSet cla_set;
  std::vector<dpll::var_stat> results;

  int read(std::string path);
  std::tuple<int, const clause *> get_solve_stat();
  int get_next_split();
};
} // namespace dpll
