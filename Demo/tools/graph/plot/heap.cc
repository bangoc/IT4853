#include "matplotlibcpp.h"

#include <vector>

namespace plt = matplotlibcpp;

int main(int argc, char* argv[]) {
  double k = 60;
  double b = 0.5;
  std::vector<double> T;
  std::vector<double> M;
  for (int i = 1; i < 100; ++i) {
    double point = i * 100.0;
    T.push_back(point);
    M.push_back(k * std::pow(point, b));
  }
  plt::plot(T, M);
  plt::title("M = 60 * T^0.5");
  plt::xlabel("T");
  plt::ylabel("M");
  plt::show();
}