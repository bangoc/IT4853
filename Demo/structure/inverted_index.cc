#include "algorithm/files.h"
#include "structure/inverted_index.h"
#include "structure/postings.h"

#include <algorithm>
#include <cmath>
#include <sstream>

bool operator<(const ScoreDoc& d1, const ScoreDoc& d2) {
  return d1.score < d2.score;
}

void ParseVSMQuery(const std::string& query_text, VSMQuery& query,
                   InvertedIndex& index) {
  std::vector<std::string> query_tokens;
  ParseTokenLine(query_text, query_tokens);
  std::vector<std::int32_t> term_ids;
  for (auto& tk: query_tokens) {
    auto it = index.term_id.find(tk);
    if (it != index.term_id.end()) {
      term_ids.push_back(it->second);
    }
  }
  query.Init(term_ids);
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

InvertedIndex::InvertedIndex(const std::string& index_data_path) {
  LoadIndexData(index_data_path, ptv, id_path, id_term);
  N = static_cast<double>(id_path.size());
  ld.resize(id_path.size(), 0);
  CalculateLd(ptv, ld, nullptr);
  for (auto& it: id_term) {
    term_id[it.second] = it.first;
  }
}
