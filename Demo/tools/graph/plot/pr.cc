#include "matplotlibcpp.h"

#include <cmath>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

namespace plt = matplotlibcpp;

bool SameValue(double v1, double v2) {
  static const double eps = 1e-10;
  return std::fabs(v1 - v2) < eps;
}

bool SameOrGreater(double v1, double v2) {
  static const double eps = 1e-10;
  return SameValue(v1, v2) || v1 > v2;
}

double Interp(const std::vector<double>& pi,
              const std::vector<double>& ri,
              double r) {
  double max = 0;
  for (auto i = 0; i < ri.size(); ++i) {
    if (SameOrGreater(ri[i], r) && pi[i] > max) {
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
  double r_norm = 0.0;
  std::vector<double> r_interp;
  std::vector<double> p_interp;
  for (; SameOrGreater(1.0, r_norm); r_norm += 0.1) {
    r_interp.push_back(r_norm);
    p_interp.push_back(Interp(pi, ri, r_norm));
  }
  plt::plot(ri, pi, "b.-");
  plt::plot(r_interp, p_interp, "go-");
  plt::title("P/R");
  plt::xlabel("R");
  plt::xticks(r_interp);
  plt::ylabel("P");
  plt::show();
}