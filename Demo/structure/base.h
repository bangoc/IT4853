#ifndef STRUCTURE_BASE_H_
#define STRUCTURE_BASE_H_

#include <cstdint>
#include <map>
#include <vector>

struct PostingDoc {
  std::int32_t docid;
  std::vector<std::int32_t> positions;
};

using PostingDocVector = std::vector<PostingDoc>;

struct PostingTerm {
  std::int32_t termid;
  PostingDocVector postings;
};

using PostingTermVector = std::vector<PostingTerm>;

struct WordEntry {
  std::int32_t df;
  std::int32_t posting_list_pointer;
};

using Dictionary = std::map<std::string, WordEntry>;

#endif  // STRUCTURE_BASE_H_