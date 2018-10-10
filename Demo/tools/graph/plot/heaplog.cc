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
    T.push_back(log(point));
    M.push_back(std::log(k) + b * log(point));
  }
  plt::plot(T, M);
  plt::title("log(M) = log(60) + 0.5*log(T)");
  plt::xlabel("log(T)");
  plt::ylabel("log(M)");
  plt::show();
}