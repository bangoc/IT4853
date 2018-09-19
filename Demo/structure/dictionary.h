#ifndef STRUCTURE_DICTIONARY_H_
#define STRUCTURE_DICTIONARY_H_

#include <map>

struct WordEntry {
  std::int32_t df;
  std::int32_t posting_list_pointer;
};

using Dictionary = std::map<std::string, WordEntry>;

bool ParseDictionary(const std::string& file_name, Dictionary& out);
bool SerializeDictionary(const std::string& file_name, const Dictionary& dict);

#endif  // STRUCTURE_DICTIONARY_H_