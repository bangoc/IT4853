#include "sorted.h"

void IntersectSorted(const PostingsList& l1, const PostingsList& l2,
                     PostingsList& out) {
  auto iter1 = l1.begin();
  auto iter2 = l2.begin();
  while (iter1 != l1.end() && iter2 != l2.end()) {
    if (*iter1 == *iter2) {
      out.push_back(*iter1);
      ++iter1;
      ++iter2;
    } else {
      if (*iter1 < *iter2) {
        ++iter1;
      } else {
        ++iter2;
      }
    }
  }
}
