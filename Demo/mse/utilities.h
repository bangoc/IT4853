#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <fstream>
#include <string>
#include <vector>

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

template<typename T>
void ParseList(const std::string& file_name, T& out, int step_size) {
  typename T::value_type sublist;
  typename T::value_type::value_type val;
  std::ifstream inp{file_name};
  int cc = 0;
  while (inp >> val) {
    ++cc;
    sublist.push_back(val);
    if (cc >= step_size) {
      out.push_back(sublist);
      sublist.clear();
      cc = 0;
    }
  }
  if (cc > 0) {
    out.push_back(sublist);
    sublist.clear();
  }
}

bool Tokenize(const std::string& line, char separator, std::vector<std::string>& out);

#endif  // UTILITIES_H_