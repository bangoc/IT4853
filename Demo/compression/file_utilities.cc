#include "file_utilities.h"

#include <iostream>

int Compare(const std::string& file_name1, const std::string& file_name2) {
  std::vector<std::uint8_t> data1;
  std::vector<std::uint8_t> data2;
  LoadFile(file_name1, data1);
  LoadFile(file_name2, data2);
  if (data1.size() != data2.size()) {
    std::cout << "Different length!" << std::endl;
    return 1;
  }
  for (auto i = 0; i < data1.size(); ++i) {
    if (data1[i] != data2[i]) {
      std::cout << "Different value at " << i << ":"
                << static_cast<std::int32_t>(data1[i]) << " "
                << static_cast<std::int32_t>(data2[i]) << std::endl;
      return 1;
    }
  }
  std::cout << "Same values." << std::endl;
  return 0;
}