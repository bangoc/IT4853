#ifndef INVERTED_INDEX_H_
#define INVERTED_INDEX_H_

#include "base.h"
#include "conversions.h"
#include "vsm_query.h"

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

bool operator<(const ScoreDoc& d1, const ScoreDoc& d2);

#endif  // INVERTED_INDEX_H_