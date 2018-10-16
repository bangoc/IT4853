#include "token.h"

bool operator<(const Token& tk1, const Token& tk2) {
  return (tk1.term < tk2.term) ||
    (tk1.term == tk2.term &&
     (tk1.docid < tk2.docid || (tk1.docid == tk2.docid && tk1.position < tk2.position)));
}

std::ostream& operator<<(std::ostream& stream, const Token& token) {
  stream << token.term << " " << token.docid << " " << token.position;
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const TokenList& token_list) {
  for (const auto& token: token_list) {
    stream << " " << token;
  }
  return stream;
}