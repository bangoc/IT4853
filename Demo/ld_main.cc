#include "structure/base.h"
#include "structure/inverted_index.h"
#include "structure/postings.h"

#include <iostream>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Usage: ./ld posting_term_file" << std::endl;
    return 1;
  }
  PostingTermVector ptv;
  const std::int32_t N = 5;
  ParsePostingTermVector(argv[1], ptv);
  std::map<std::int32_t, double> ld;
  std::map<std::int32_t, std::string> explain;
  CalculateLd(ptv, N, ld, explain);
  for (auto it = ld.begin(); it != ld.end(); ++it) {
    std::cout << it->first << ":" << it->second << ": " << explain[it->first] << std::endl;
  }
  return 0;
}