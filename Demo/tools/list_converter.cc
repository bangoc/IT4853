/*
 convert between text and binary format
*/

#include <cstdint>
#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, const char* argv[]) {
  if (argc != 4) {
    std::cout << "Usage: " << std::endl
    << "./listcv t2b ordered_list1.txt ordered_list1" << std::endl
    << "./listcv b2t ordered_list1 ordered_list1.txt" << std::endl;
    return 1;
  }
  std::string cmd{argv[1]};
  if (cmd == "t2b") {
    std::ifstream inp{argv[2]};
    std::int32_t val;
    std::vector<std::int32_t> values;
    while (inp >> val) {
      values.push_back(val);
    }
    std::ofstream out{argv[3]};
    char sz = 32;
    out.write(&sz, 1);
    std::int32_t len = static_cast<std::int32_t>(values.size());
    out.write(reinterpret_cast<char*>(&len), 4);
    out.write(reinterpret_cast<char*>(values.data()), values.size() * 4);
  } else if (cmd == "b2t") {
    std::ifstream inp{argv[2]};
    char sz = 0;
    inp.read(&sz, 1);
    std::int32_t len = 0;
    inp.read(reinterpret_cast<char*>(&len), 4);
    std::cout << "Number of elements = " << len << std::endl;
    std::int32_t* a = new std::int32_t[len];
    inp.read(reinterpret_cast<char*>(a), 4 * len);
    for (int i = 0; i < len; ++i) {
      std::cout << " " << a[i];
    }
    std::cout << std::endl;
  } else {
    std::cout << "Unrecognized command." << std::endl;
  }
}