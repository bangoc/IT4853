#include "algorithm/files.h"

bool ParseTokenFile(const std::string& file_name,
      std::vector<std::string>& out) {
  std::ifstream inp(file_name);
  out.clear();
  std::string line;
  while (std::getline(inp, line)) {
    std::stringstream ss{line};
    std::string token;
    while (std::getline(ss, token, '|')) {
      if (token.length() > 0)
        out.push_back(token);
    }
  }
  return true;
}

bool ListTokFiles(const std::string& in_folder, bool recursive,
                  std::vector<std::string>& out) {
  std::set<std::string> filters {".tok"};
  if (recursive) {
    ListFiles<std::experimental::filesystem::recursive_directory_iterator>(in_folder, filters, out);
  } else {
    ListFiles<std::experimental::filesystem::directory_iterator>(in_folder, filters, out);
  }
  return true;
}

bool ParseTokenFolder(const std::string& in_folder,
                      TokenList& out_tokens,
                      IdToPath& id_to_path) {
  std::vector<std::string> inp_files;
  ListTokFiles(in_folder, false, inp_files);
  for (auto i = 0; i < inp_files.size(); ++i) {
    id_to_path[i] = inp_files[i];
    std::vector<std::string> terms;
    ParseTokenFile(inp_files[i], terms);
    std::int32_t pos = 0;
    for (const std::string& t: terms) {
      Token token;
      token.term = t;
      token.docid = i;
      token.position = pos++;
      out_tokens.push_back(token);
    }
  }
  return true;
}