#include <include/clause.h>
namespace dpll {
int clauseSet::read_from_cnf(std::string path) {
  std::ifstream ifs(path);
  if (!ifs) {
    return -1;
  }
  char mode;
  std::string line;
  line.reserve(1024);
  while (!ifs.eof()) {
    ifs >> mode;
    if (mode == 'p') {
      ifs >> line >> this->var_count >> this->cla_count;
      this->clause_vec.resize(this->cla_count, nullptr);
      break;
    }
    std::getline(ifs, line);
  }
  for (int i = 0; i < this->cla_count && !ifs.eof(); i++) {
    this->clause_vec[i] = std::make_shared<clause>();
    auto &cur_cla = *(this->clause_vec[i]);
    std::stringstream line_stream;
    int d = 0;
    std::getline(ifs, line);
    line_stream << line;
    while (line_stream >> d, !d) {
      cur_cla.add(d);
    }
  }
  return 0;
}

} // namespace dpll