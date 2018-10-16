#include "base.h"
#include "inverted_index.h"
#include "query_parser.h"

#include <iostream>

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << "Usage: ./search index_folder_path \"query text\"" << std::endl;
    return 1;
  }
  InvertedIndex index{argv[1]};
  VSMQuery query;
  ParseVSMQuery(argv[2], query, index);
  std::vector<ScoreDoc> similarity;
  CosineSimilarity(index, query, similarity);
  for (auto i = 0; i < similarity.size(); ++i) {
    std::int32_t id = similarity[i].docid;
    std::cout << id << ":" << index.id_path[id] << ":" << similarity[i].score
              << similarity[i].explain << std::endl;
  }
  return 0;
}