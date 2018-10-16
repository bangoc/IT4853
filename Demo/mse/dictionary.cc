#include "dictionary.h"

#include <fstream>
#include <sstream>

std::istream& operator>>(std::istream& stream, Dictionary& dict) {
  std::string line;
  while (std::getline(stream, line)) {
    std::stringstream ss;
    std::string word;
    WordEntry entry;
    std::getline(ss, word, '|');
    std::string entry_string;
    std::getline(ss, entry_string, '|');
    std::stringstream tmp{entry_string};
    tmp >> entry.df;
    tmp >> entry.posting_list_pointer;
    dict[word] = entry;
  }
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Dictionary& dict) {
  for (const auto& entry: dict) {
    stream << entry.first << "|"
           << entry.second.df << " " << entry.second.posting_list_pointer << std::endl;
  }
  return stream;
}

bool ParseDictionary(const std::string& file_name, Dictionary& out) {
  std::ifstream inp{file_name};
  inp >> out;
  return true;
}

bool SerializeDictionary(const std::string& file_name, const Dictionary& dict) {
  std::ofstream out{file_name};
  out << dict;
  return true;
}