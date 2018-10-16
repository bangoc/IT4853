#include "inverted_index.h"
#include "index_reader.h"
#include "stick_tokenizer.h"

#include <algorithm>
#include <cmath>
#include <sstream>

bool operator<(const ScoreDoc& d1, const ScoreDoc& d2) {
  return d1.score < d2.score;
}

void CalculateLd(const PostingTermVector& ptv,
                 std::vector<double>& ld,
                 std::vector<std::string>* explain) {
  double N = static_cast<double>(ld.size());
  for (const auto& posting_term: ptv) {
    double idf = log(N/posting_term.postings.size());
    for (const auto& posting_doc: posting_term.postings) {
      double tf = 1 + log(posting_doc.positions.size());
      double w = tf * idf;
      ld[posting_doc.docid] += w * w;
      if (explain) {
        std::stringstream ss;
        ss << posting_term.termid << ":(log(" << N << "/" << posting_term.postings.size() << ") *"
           << "(1 + log(" << posting_doc.positions.size() << ")))^2";
        (*explain)[posting_doc.docid] += (ss.str() + " + ");
      }
    }
  }
}

// Since lq is a constant for all documents so we will skip calculating it
void CosineSimilarity(const InvertedIndex& index,
                      const VSMQuery& query,
                      std::vector<ScoreDoc>& similarity) {
  similarity.resize(index.id_path.size());
  for (auto i = 0; i < similarity.size(); ++i) {
    similarity[i].docid = i;
  }
  double N = index.N;
  for (auto qt: query.query_terms) {
    auto& posting_term = index.ptv[qt.termid];
    double idf = 1 + log(N/posting_term.postings.size());
    double wtq = (1 + log(qt.tf)) * idf;
    for (const auto& posting_doc: posting_term.postings) {
      double wtd = (1 + log(posting_doc.positions.size())) * idf;
      similarity[posting_doc.docid].score += wtd * wtq;
      {
        std::stringstream ss;
        auto it = index.id_term.find(qt.termid);
        if (it != index.id_term.end()) {
          ss << " " << qt.termid << "(" << it->second << ")"
             << wtd << "*" << wtq << " +";
          similarity[posting_doc.docid].explain += ss.str();
        }
      }
    }
  }
  for (auto i = 0; i < similarity.size(); ++i) {
    similarity[i].score /= index.ld[i];
    {
      std::stringstream ss;
      ss << " Ld: " << index.ld[i];
      similarity[i].explain += ss.str();
    }
  }
  std::sort(similarity.begin(), similarity.end(),
            [](const ScoreDoc& d1, const ScoreDoc& d2) { return d2 < d1; });
}
