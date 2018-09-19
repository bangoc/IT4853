#include "algorithm/files.h"

bool ParseToken(const std::string& file_name,
      std::vector<std::string>& out) {
  std::ifstream inp(file_name);
  out.clear();
  std::string line;
  while (std::getline(inp, line)) {
    std::stringstream ss{line};
    std::string token;
    while (std::getline(ss, token, '|')) {
      if (token.length() > 0)
        out.push_back(token);
    }
  }
  return true;
}