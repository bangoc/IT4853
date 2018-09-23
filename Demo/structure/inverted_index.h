#ifndef STRUCTURE_INVERTED_INDEX_H_
#define STRUCTURE_INVERTED_INDEX_H_

#include "structure/conversions.h"
#include "structure/dictionary.h"
#include "structure/postings.h"

#include <iostream>

struct SimpleIndexEntry {
  std::int32_t termid;
  struct Posting {
    std::int32_t docid;
    std::vector<std::int32_t> positions;
  };
  using SimpleIndexPostingList = std::vector<Posting>;
  SimpleIndexPostingList postings;
};

using SimpleIndex = std::vector<SimpleIndexEntry>;
using IdToPath = std::map<std::int32_t, std::string>;
using IdToTerm = std::map<std::int32_t, std::string>;

bool BuildSimpleIndex(const std::string& in_folder, const std::string& out_folder);
bool SerializeSimpleIndex(const std::string& file_path, const SimpleIndex& simple_index);
bool ParseSimpleIndex(const std::string& file_path, SimpleIndex& out);

std::ostream& operator<<(std::ostream& stream, const SimpleIndex& simple_index);
std::istream& operator>>(std::istream& stream, const SimpleIndex& simple_index);

#endif  // STRUCTURE_INVERTED_INDEX_H_