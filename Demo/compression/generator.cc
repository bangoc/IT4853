#include <cstdlib>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <vector>

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << "Usage: ./gen number file_name" << std::endl;
    return 1;
  }
  std::int32_t n = 0;
  {
    std::stringstream ss{argv[1]};
    ss >> n;
  }
  std::cout << "Generating " << n << " numbers..." << std::endl;
  std::srand(time(0));
  std::set<std::int32_t> values;
  std::int32_t max = 10 * n;
  while (values.size() < n) {
    std::int32_t v = rand() % max;
    if (values.find(v) == values.end()) {
      values.insert(v);
    }
  }
  std::vector<std::int32_t> tmp;
  for (auto v: values) {
    tmp.push_back(v);
  }
  std::ofstream out{argv[2], std::ios_base::binary};
  out.write(reinterpret_cast<char*>(tmp.data()), tmp.size() * sizeof(std::int32_t));
  return 0;
}