#include "base.h"
#include "inverted_index.h"
#include "index_reader.h"

#include <iostream>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Usage: ./ld index_data_folder" << std::endl;
    return 1;
  }
  PostingTermVector ptv;
  IdToPath id_path;
  IdToTerm id_term;
  LoadIndexData(argv[1], ptv, id_path, id_term);
  std::vector<double> ld(id_path.size());
  std::vector<std::string> explain(id_path.size());
  CalculateLd(ptv, ld, &explain);
  for (auto i = 0; i < ld.size(); ++i) {
    std::cout << i << ":" << ld[i] << ": " << explain[i] << std::endl;
  }
  return 0;
}