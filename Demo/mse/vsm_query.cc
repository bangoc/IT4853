#include "vsm_query.h"

#include <map>

VSMQuery::VSMQuery() {
}

VSMQuery::VSMQuery(const std::vector<std::int32_t>& terms) {
  Init(terms);
}

void VSMQuery::Init(const std::vector<std::int32_t>& terms) {
  std::map<std::int32_t, std::int32_t> term_tf;
  for (auto id: terms) {
    ++term_tf[id];
  }
  for (auto it = term_tf.begin(); it != term_tf.end(); ++it) {
    TermWeight tw;
    tw.termid = it->first;
    tw.tf = it->second;
    query_terms.push_back(tw);
  }
}
