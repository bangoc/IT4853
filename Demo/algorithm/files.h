#ifndef ALGORITHM_FILES_H_
#define ALGORITHM_FILES_H_

#include "structure/conversions.h"
#include "structure/token.h"

#include <experimental/filesystem>
#include <fstream>
#include <set>
#include <string>
#include <vector>

bool ParseTokenFile(const std::string& file_name,
      std::vector<std::string>& out);

bool ParseTokenFolder(const std::string& in_folder,
                      TokenList& out_tokens,
                      IdToPath& id_to_path);


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
#endif  // ALGORITHM_FILES_H_