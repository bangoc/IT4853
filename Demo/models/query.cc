#include "query.h"

#include <cmath>
#include <iostream>

#include "tokenizer.h"

bool Query::Parse(const std::string& query) {
  TermsList list;
  Tokenize(list, query);
  for (auto& term: list) {
    tf[term]++;
  }
  int max = 0;
  double ave = 0;
  for (auto& term_freq: tf) {
    if (term_freq.second > max) {
      max = term_freq.second;
    }
    ave += term_freq.second;
  }
  max_tf = max;
  ave_tf = ave / tf.size();
  return true;
}

int Query::GetTf(const std::string& term) const {
  auto term_freq = tf.find(term);
  if (term_freq != tf.end()) {
    return term_freq->second;
  }
  return 0;
}

double Query::GetWtf(const std::string& term, char measure) const {
  int tf_tq = GetTf(term);
  if (tf_tq < 1) {
    return 0;
  }
  switch (measure) {
    case 'n':
      return tf_tq;
    case 'l':
      return 1 + MyLog(tf_tq);
    case 'a':
      return 0.5 + 0.5 * tf_tq / max_tf;
    case 'b':
      if (tf_tq > 0) {
        return 1;
      }
      return 0;
    case 'L':
      return (1 + MyLog(tf_tq))/ (1 + MyLog(ave_tf));
  }
  std::cerr << "Unknown tf measure " << measure << " for query ";
  return 0;
}
