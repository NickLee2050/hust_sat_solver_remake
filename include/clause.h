#include <memory>
#include <string>
#include <vector>

namespace dpll {
class clause {
public:
  clause(){};
  ~clause(){};

  std::vector<int> data;

  int add(int d) {
    this->data.push_back(d);
    return 0;
  }
};
class clauseSet {
public:
  clauseSet() = default;
  clauseSet(const std::string &path) {
    if (read_from_cnf(path)) {
      throw;
    };
  }
  ~clauseSet() = default;

  int cla_count, var_count;
  std::vector<clause> clause_vec;

  int read_from_cnf(const std::string &path);
};
} // namespace dpll
