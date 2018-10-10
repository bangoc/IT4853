#include "matplotlibcpp.h"

#include <iostream>
#include <sstream>
#include <vector>

namespace plt = matplotlibcpp;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << "Usage: ./zipf 10000 100" << std::endl;
    return 1;
  }
  double K = 1000;
  double N = 100;
  {
    std::stringstream ss{argv[1]};
    ss >> K;
  }
  {
    std::stringstream ss{argv[2]};
    ss >> N;
  }
  std::vector<double> cf;
  std::vector<double> x;
  for (int i = 1; i < N; ++i) {
    x.push_back(i);
    cf.push_back(K/i);
  }
  plt::plot(x, cf);
  {
    std::ostringstream ss;
    ss << N << " values of " << K << "/i";
    plt::title(ss.str());
  }
  plt::xlabel("x");
  plt::ylabel("cf");
  plt::show();
}