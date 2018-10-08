#ifndef STRUCTURE_INVERTED_INDEX_H_
#define STRUCTURE_INVERTED_INDEX_H_

#include "structure/base.h"
#include "structure/conversions.h"
#include "structure/vsm_query.h"

struct InvertedIndex {
  InvertedIndex(const std::string& index_data_path);
  PostingTermVector ptv;
  IdToPath id_path;
  IdToTerm id_term;
  TermToId term_id;
  std::vector<double> ld;
  double N;
};

void CalculateLd(const PostingTermVector& ptv,
                 std::vector<double>& ld,
                 std::vector<std::string>* explain);
void CosineSimilarity(const InvertedIndex& index,
                      const VSMQuery& query,
                      std::vector<ScoreDoc>& similarity);
void ParseVSMQuery(const std::string& query_text, VSMQuery& query,
                   InvertedIndex& index);

bool operator<(const ScoreDoc& d1, const ScoreDoc& d2);

#endif  // STRUCTURE_INVERTED_INDEX_H_