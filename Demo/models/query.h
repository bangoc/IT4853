#ifndef QUERY_H_
#define QUERY_H_

#include "base.h"

class Query {
 public:
  bool Parse(const std::string& query);
  int GetTf(const std::string& term) const;
  double GetWtf(const std::string& term, char measure) const;
 private:
  std::map<std::string, int> tf;
  int max_tf;
  double ave_tf;
};

#endif  // QUERY_H_