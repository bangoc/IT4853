#ifndef STRUCTURE_POSTINGS_H_
#define STRUCTURE_POSTINGS_H_

#include <string>
#include <vector>

struct PostingCard{
  std::int32_t docid;
  std::vector<std::int32_t> positions;
};

using PostingList = std::vector<PostingCard>;
using Postings = std::vector<PostingList>;

bool ParsePostings(const std::string& file_name, Postings& out);
bool SerializePostings(const std::string& file_name, const Postings& postings);

#endif  // STRUCTURE_POSTINGS_H_