#ifndef VSM_QUERY_H_
#define VSM_QUERY_H_

#include <cstdint>
#include <string>
#include <vector>

struct VSMQuery {
  VSMQuery();
  VSMQuery(const std::vector<std::int32_t>& terms);
  void Init(const std::vector<std::int32_t>& terms);
  struct TermWeight {
    std::int32_t termid;
    double tf;
  };
  std::vector<TermWeight> query_terms;
};

#endif  // VSM_QUERY_H_