#include "naive.h"

void IntersectNaive(const PostingsList& l1, const PostingsList& l2,
                    PostingsSet& out) {
  for (auto it1 = l1.begin(); it1 != l1.end(); ++it1) {
    for (auto it2 = l2.begin(); it2 != l2.end(); ++it2) {
      if (*it1 == *it2 && out.find(*it1) == out.end()) {
        out.insert(*it1);
      }
    }
  }
}