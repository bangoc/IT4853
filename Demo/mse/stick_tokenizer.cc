#include "stick_tokenizer.h"
#include "token.h"

#include <fstream>
#include <sstream>

bool ParseTokenLine(const std::string& line,
      std::vector<std::string>& out) {
  std::stringstream ss{line};
  std::string token;
  while (std::getline(ss, token, '|')) {
    if (token.length() > 0)
      out.push_back(token);
  }
  return true;
}

bool ParseTokenFile(const std::string& file_name,
      std::vector<std::string>& out) {
  std::ifstream inp(file_name);
  out.clear();
  std::string line;
  while (std::getline(inp, line)) {
    std::vector<std::string> tokens;
    ParseTokenLine(line, tokens);
    for (auto& tk: tokens) {
      out.push_back(tk);
    }
  }
  return true;
}
