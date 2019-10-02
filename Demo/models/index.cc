#include "index.h"
#include "tokenizer.h"

#include <cmath>
#include <iostream>
#include <set>

int Index::AddDocument(const std::string& doc) {
  TermsList list;
  Tokenize(list, doc);
  std::set<std::string> unique_terms;
  for (auto& term: list) {
    tf[term][max_docid]++;
    if (unique_terms.find(term) == unique_terms.end()) {
      df[term]++;
      unique_terms.insert(term);
    }
  }
  return max_docid++;
}

int Index::GetNumDocs() const {
  return max_docid;
}

bool Index::GetTerms(Terms& out) const {
  for (auto& iter: tf) {
    out.push_back(iter.first);
  }
  return true;
}

bool Index::GetLengthNU(DocumentLength& out, char measure) const {
  for (int i = 0; i < max_docid; ++i) {
    out.push_back(0);
  }
  switch (measure) {
    case 'n': {
      for (int i = 0; i < max_docid; ++i) {
        out[i] = 1;
      }
      return true;
    }
    case 'u': {
      for (auto& iter: tf) {
        auto term = iter.first;
        for (auto& doc_freq: iter.second) {
          if (doc_freq.second > 0) {
            ++out[doc_freq.first];
          }
        }
      }
      return true;
    }
  }
  return false;
}

bool Index::GetLengthB(DocumentLength& out, 
                       char measure, double alpha) const {
  for (int i = 0; i < max_docid; ++i) {
    out.push_back(0);
  }
  switch (measure) {
    case 'b': {
      for (auto& iter: tf) {
        auto term = iter.first;
        for (auto& doc_freq: iter.second) {
          out[doc_freq.first] += term.length() * doc_freq.second;
        }
      }
      for (int i = 0; i < max_docid; ++i) {
        out[i] = std::pow(out[i], alpha);
      }
      return true;
    }
  }
  return false;
}
bool Index::GetLengthC(DocumentLength& out, 
                       const std::string& schema) const {
  for (int i = 0; i < max_docid; ++i) {
    out.push_back(0);
  }
  switch (schema[2]) {
    case 'c': {
      for (auto& term_postings: tf) {
        auto term = term_postings.first;
        for (auto& doc_freq: term_postings.second) {
          double w =
              GetWtf(term, doc_freq.first, schema[0]) *
              GetWdf(term, schema[1]);
          out[doc_freq.first] += w * w;
        }
      }
      for (int i = 0; i < max_docid; ++i) {
        out[i] = std::sqrt(out[i]);
      }
      return true;
    }
  }
  return false;
}

int Index::GetTf(const std::string& term, int doc_id) const {
  auto term_postings = tf.find(term);
  if (term_postings == tf.end()) {
    return 0;
  }
  auto doc_freq = term_postings->second.find(doc_id);
  if (doc_freq == term_postings->second.end()) {
    return 0;
  }
  return doc_freq->second;
}

int Index::GetDf(const std::string& term) const {
  auto term_df = df.find(term);
  if (term_df == df.end()) {
    return 0;
  }
  return term_df->second;
}

int Index::GetMaxTf(int doc_id) const {
  int max = 0;
  for (auto& iter: tf) {
    auto doc_freq = iter.second.find(doc_id);
    if (doc_freq != iter.second.end() && 
        doc_freq->second > max) {
      max = doc_freq->second;
    }
  }
  return max;
}

double Index::GetAveTf(int doc_id) const {
  double ave = 0;
  double cc = 0;
  for (auto& iter: tf) {
    auto doc_freq = iter.second.find(doc_id);
    if (doc_freq != iter.second.end()) {
      ++cc;
      ave += doc_freq->second;
    }
  }
  ave /= cc;
  return ave;
}

double Index::GetWtf(const std::string& term, 
                  int doc_id, char multiplier) const {
  int tf_td = GetTf(term, doc_id);
  if (tf_td < 1) {
    return 0;
  }
  switch (multiplier) {
    case 'n': {
      return tf_td;
    }
    case 'l': {
      if (tf_td > 0) {
        return 1 + MyLog(tf_td);
      }
      return 0;
    }
    case 'a': {
      double max = GetMaxTf(doc_id);
      if (max > 0) {
        return 0.5 + 0.5 * tf_td/max;
      }
      return 0;
    }
    case 'b': {
      if (tf_td > 0) {
        return 1;
      }
      return 0;
    }
    case 'L': {
      double ave = GetAveTf(doc_id);
      return (1 + MyLog(tf_td))/(1 + MyLog(ave));
    }
  }
  return 0;
}

double Index::GetWdf(const std::string& term, 
                     char multiplier) const {
  int N = max_docid;
  double df = (double)GetDf(term);
  if (df < 1) {
    return 0;
  }
  switch (multiplier) {
    case 't': {
      if (df < N) {
        return MyLog(N/df);
      }
      return 0;
    }
    case 'n': {
      return 1;
    }
    case 'p': {
      if (N > df) {
        double w = MyLog((N-df)/df);
        if (w > 0) {
          return w;
        }
      }
      return 0;
    }
  }
  return 0;
}
