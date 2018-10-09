#include "file_utilities.h"

#include <cstdlib>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <vector>

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cout << "Usage: ./gen number max file_name" << std::endl
              << "Where max >= 10 * number" << std::endl
              << "example: ./gen 10 1000 data" << std::endl;
    return 1;
  }
  std::int32_t n = 0;
  std::int32_t max = 0;
  {
    std::stringstream ss{argv[1]};
    ss >> n;
  }
  {
    std::stringstream ss{argv[2]};
    ss >> max;
    if (max < 10 * n) {
      max = 10 * n;
    }
  }
  std::cout << "Generating " << n
            << " numbers in [1.." << max << "] ..." << std::endl;
  std::srand(time(0));
  std::set<std::int32_t> values;
  while (values.size() < n) {
    std::int32_t v = rand() % max;
    if (v < 1) {
      v = 1;
    }
    if (values.find(v) == values.end()) {
      values.insert(v);
    }
  }
  std::vector<std::int32_t> tmp;
  for (auto v: values) {
    tmp.push_back(v);
  }
  SaveToFile(argv[3], tmp);
  return 0;
}