#ifndef NAIVE_H_
#define NAIVE_H_

#include "base.h"

void IntersectNaive(const PostingsList& l1, const PostingsList& l2,
                    PostingsSet& out);

#endif  // NAIVE_H_