#include "structure/dictionary.h"

#include <fstream>
#include <sstream>

bool ParseDictionary(const std::string& file_name, Dictionary& out) {
  std::ifstream inp{file_name};
  std::string line;
  while (std::getline(inp, line)) {
    std::stringstream ss;
    std::string word;
    WordEntry entry;
    std::getline(ss, word, '|');
    std::string entry_string;
    std::getline(ss, entry_string, '|');
    std::stringstream tmp{entry_string};
    tmp >> entry.df;
    tmp >> entry.posting_list_pointer;
    out[word] = entry;
  }
  return true;
}

bool SerializeDictionary(const std::string& file_name, const Dictionary& dict) {
  std::ofstream out{file_name};
  for (const auto& entry: dict) {
    out << entry.first << "|"
        << entry.second.df << " " << entry.second.posting_list_pointer << std::endl;
  }
  return true;
}