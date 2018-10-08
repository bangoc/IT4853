#include "matplotlibcpp.h"

#include <cmath>
#include <vector>

namespace plt = matplotlibcpp;

int main(int argc, char* argv[]) {
  std::vector<double> x1;
  std::vector<double> hp;
  for (int i = 0; i < 100; ++i) {
    double point = 1e-2 * i;
    x1.push_back(point);
    double x2 = 1 - point;
    hp.push_back(-(point * std::log(point) / std::log(2.0) + x2 * std::log(x2) / std::log(2.0)));
  }

  plt::plot(x1, hp);
  plt::title("X={x1, x2}");
  plt::xlabel("P(x1)");
  plt::ylabel("H(P)");
  plt::show();
}