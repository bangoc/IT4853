#include "structure/inverted_index.h"

#include <cmath>
#include <sstream>

void CalculateLd(const PostingTermVector& ptv,
                 const std::int32_t N,
                 std::map<std::int32_t, double>& ld,
                 std::map<std::int32_t, std::string>& explain) {
  for (const auto& posting_term: ptv) {
    double idf = log(N/posting_term.postings.size());
    for (const auto& posting_doc: posting_term.postings) {
      double tf = 1 + log(posting_doc.positions.size());
      double w = tf * idf;
      ld[posting_doc.docid] += w * w;
      {
        std::stringstream ss;
        ss << posting_term.termid << ":(log(" << N << "/" << posting_term.postings.size() << ") *"
           << "(1 + log(" << posting_doc.positions.size() << ")))^2";
        explain[posting_doc.docid] += (ss.str() + " + ");
      }
    }
  }
}