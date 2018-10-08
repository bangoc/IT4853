#include "algorithm/utilities.h"

#include <sstream>

bool Tokenize(const std::string& line, char separator, std::vector<std::string>& out) {
  std::stringstream ss{line};
  out.clear();
  std::string token;
  while (std::getline(ss, token, separator)) {
    out.push_back(token);
  }
  return true;
}