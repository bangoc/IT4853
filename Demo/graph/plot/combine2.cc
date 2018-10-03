#include "matplotlibcpp.h"

#include <vector>

namespace plt = matplotlibcpp;

int main() {
  int n = 50;
  std::vector<double> x, y_avg, y_min, y_max, y_f;
  for (int i = 0; i < n; ++i) {
    x.push_back(1.0 / (double)n * i);
    y_avg.push_back((0.7 + x[i]) / 2);
    y_min.push_back(std::min(0.7, x[i]));
    y_max.push_back(std::max(0.7, x[i]));
    y_f.push_back(2.0 * 0.7 * x[i] / (0.7 + x[i]));
  }
  plt::named_plot("avg", x, y_avg, "g.--");
  plt::named_plot("min", x, y_min, "y<--");
  plt::named_plot("max", x, y_max, "c>:");
  plt::named_plot("F", x, y_f, "b+-");

  plt::title("P/R combiners");
  plt::legend();
  plt::show();
}