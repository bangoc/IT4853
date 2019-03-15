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

void PlotPR(const std::string& relevance,
            const std::string& result,
            const std::string& mark1,
            const std::string& mark2) {
  std::vector<double> pi {0}, ri {0};
  std::vector<double> r_interp;
  std::vector<double> p_interp;
  std::set<int> rel;
  std::vector<int> res;
  {
    std::stringstream ss{relevance};
    int tmp = 0;
    while (ss >> tmp) {
      rel.insert(tmp);
    }
  }
  {
    std::stringstream ss{result};
    int tmp = 0;
    while (ss >> tmp) {
      res.push_back(tmp);
    }
  }
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
  for (; SameOrGreater(1.0, r_norm); r_norm += 0.1) {
    r_interp.push_back(r_norm);
    p_interp.push_back(Interp(pi, ri, r_norm));
  }
  plt::plot(ri, pi, mark1);
  plt::plot(r_interp, p_interp, mark2);
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cout << "Usage: ./pr \"1 2\" \"1 3 2 5 6\"" << std::endl;
    std::cout << "./pr \"1 2\" \"1 3 2 5 6\" \"1 2\" \"3 2 1 5 6\"" << std::endl;
    return 1;
  }
  if (argc >= 3) {
    PlotPR(argv[1], argv[2], "bo-", "go-");
  }
  if (argc >= 5) {
    PlotPR(argv[3], argv[4], "mx-", "rx-");
  }
  std::vector<double> xnorms;
  for (double v = 0.0; SameOrGreater(1.0, v); v += 0.1) {
    xnorms.push_back(v);
  }
  plt::title("P/R");
  plt::xlabel("R");
  plt::xticks(xnorms);
  plt::ylabel("P");
  plt::show();
}