#include "matplotlibcpp.h"

#include <iostream>
#include <set>
#include <sstream>
#include <vector>

namespace plt = matplotlibcpp;

double Interp(const std::vector<double>& pi,
              const std::vector<double>& ri,
              double r) {
  double max = 0;
  for (auto i = 0; i < ri.size(); ++i) {
    if (ri[i] >= r && pi[i] > max) {
      max = pi[i];
    }
  }
  return max;
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << "Usage: ./pr \"1 2\" \"1 3 2 5 6\"" << std::endl;
    return 1;
  }
  std::set<int> rel;
  std::vector<int> res;
  {
    std::stringstream ss{argv[1]};
    int tmp = 0;
    while (ss >> tmp) {
      rel.insert(tmp);
    }
  }
  {
    std::stringstream ss{argv[2]};
    int tmp = 0;
    while (ss >> tmp) {
      res.push_back(tmp);
    }
  }
  std::vector<double> pi {0}, ri {0};
  double rq = static_cast<double>(rel.size());
  double cc = 0;
  for (auto i = 0; i < res.size(); ++i) {
    if (rel.find(res[i]) != rel.end()) {
      ++cc;
    }
    pi.push_back(cc / (i + 1));
    ri.push_back(cc / rq);
  }
  std::vector<double> r_interp {0.0};
  std::vector<double> p_interp {Interp(pi, ri, 0.0)};
  for (int i = 0; i < 10; ++i) {
    r_interp.push_back(r_interp[i] + 0.1);
    p_interp.push_back(Interp(pi, ri, r_interp[i + 1]));
  }
  plt::plot(ri, pi, "b.-");
  plt::plot(r_interp, p_interp, "go-");
  plt::title("P/R");
  plt::xlabel("R");
  plt::xticks(r_interp);
  plt::ylabel("P");
  plt::show();
}