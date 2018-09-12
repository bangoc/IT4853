#include <fstream>
#include <string>
template<typename T>
void ParseList(const std::string& file_name, T& out) {
  std::ifstream inp{file_name};
  typename T::value_type val;
  while (inp >> val) {
    out.push_back(val);
  }
}