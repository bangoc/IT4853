#ifndef FILES_ITERATOR_H_
#define FILES_ITERATOR_H_

#include "conversions.h"
#include "token.h"

#include <experimental/filesystem>
#include <set>
#include <string>
#include <vector>

template<typename Iterator>
bool ListFiles(const std::string& in_folder,
               const std::set<std::string>& filters,
               std::vector<std::string>& out) {
  for (auto& p: Iterator(in_folder)) {
    if (std::experimental::filesystem::is_regular_file(p) &&
        filters.find(p.path().extension()) != filters.end())
      out.push_back(p.path().string());
  }
}

bool ListTokFiles(const std::string& in_folder, bool recursive,
                  std::vector<std::string>& out);

bool ParseTokenFolder(const std::string& in_folder,
                      TokenList& out_tokens,
                      IdToPath& id_to_path);

#endif  // FILES_ITERATOR_H_