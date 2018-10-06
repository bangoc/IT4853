#ifndef STRUCTURE_INVERTED_INDEX_H_
#define STRUCTURE_INVERTED_INDEX_H_

#include "structure/base.h"

void CalculateLd(const PostingTermVector& ptv,
                 const std::int32_t N,
                 std::map<std::int32_t, double>& ld,
                 std::map<std::int32_t, std::string>& explain);

#endif  // STRUCTURE_INVERTED_INDEX_H_