#include <fstream>
#include <string>

template<typename T>
bool IsAscendingList(const T& l) {
  auto it = l.begin();
  if (it != l.end()) {
    auto previous = *it;
    while (++it != l.end()) {
      auto current = *it;
      if (current <= previous)
        return false;
      previous = current;
    }
  }
  return true;
}

template<typename T>
void ParseList(const std::string& file_name, T& out) {
  std::ifstream inp{file_name};
  typename T::value_type val;
  while (inp >> val) {
    out.push_back(val);
  }
}