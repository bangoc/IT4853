#ifndef STRUCTURE_TOKEN_H_
#define STRUCTURE_TOKEN_H_

#include <string>
#include <vector>
#include <iostream>

struct Token {
  std::string term;
  std::int32_t docid;
  std::int32_t position;
};

using TokenList = std::vector<Token>;

bool operator<(const Token& tk1, const Token& tk2);
std::ostream& operator<<(std::ostream& stream, const Token& token);
std::ostream& operator<<(std::ostream& stream, const TokenList& token_list);

#endif  // STRUCTURE_TOKEN_H_