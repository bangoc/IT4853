#include "algorithm/files.h"
#include "structure/inverted_index.h"

#include <algorithm>

namespace {

void AddToken(const Token& token, IdToTerm& id_term, SimpleIndex& simple_index,
              bool new_term, bool new_doc, bool new_pos) {
  if (new_term) {
    id_term[id_term.size()] = token.term;
    SimpleIndexEntry index_entry;
    index_entry.termid = id_term.size() - 1;
    SimpleIndexEntry::Posting posting;
    posting.docid = token.docid;
    posting.positions.push_back(token.position);
    index_entry.postings.push_back(posting);
    simple_index.push_back(index_entry);
  } else if (new_doc) {
    SimpleIndexEntry& index_entry = simple_index[simple_index.size() - 1];
    SimpleIndexEntry::Posting posting;
    posting.docid = token.docid;
    posting.positions.push_back(token.position);
    index_entry.postings.push_back(posting);
  } else if (new_pos) {
    SimpleIndexEntry& index_entry = simple_index[simple_index.size() - 1];
    SimpleIndexEntry::Posting& posting = index_entry.postings[index_entry.postings.size() - 1];
    posting.positions.push_back(token.position);
  } else {
    // This should not happen
  }
}

}// namespace

bool BuildSimpleIndex(const std::string& in_folder, const std::string& out_folder) {
  TokenList token_list;
  IdToPath id_path;
  ParseTokenFolder(in_folder, token_list, id_path);
  std::sort(token_list.begin(), token_list.end());
  IdToTerm id_term;
  SimpleIndex simple_index;
  AddToken(token_list[0], id_term, simple_index, true, true, true);
  for (auto i = 2; i < token_list.size(); ++i) {
    Token& token1 = token_list[i - 1];
    Token& token2 = token_list[i];
    if (token2.term != token1.term) {
      AddToken(token2, id_term, simple_index, true, true, true);
    } else if (token2.docid != token1.docid) {
      AddToken(token2, id_term, simple_index, false, true, true);
    } else if (token2.position != token1.position) {
      AddToken(token2, id_term, simple_index, false, false, true);
    } else {
      // This should not happen
    }
  }
  std::experimental::filesystem::create_directories(out_folder);
  SerializeSimpleIndex(out_folder + "/simple_index.dat", simple_index);
  SerializeIdToPath(out_folder + "/id_path.dat", id_path);
  SerializeIdToTerm(out_folder + "/id_term.dat", id_term);
  return true;
}

std::ostream& operator<<(std::ostream& stream, const SimpleIndex& simple_index) {
  std::stringstream ss;
  for (const auto& entry: simple_index) {
    ss << entry.termid;
    for (const auto& posting: entry.postings) {
      ss << " " << posting.docid << " " << posting.positions.size();
      for (const auto& position: posting.positions) {
        ss << " " << position;
      }
    }
    ss << std::endl;
  }
  stream << ss.str();
  return stream;
}

bool SerializeSimpleIndex(const std::string& file_path, const SimpleIndex& simple_index) {
  std::ofstream output_file{file_path};
  output_file << simple_index;
  return true;
}

std::istream& operator>>(std::istream& stream, SimpleIndex& out) {
  std::string line;
  out.clear();
  while (std::getline(stream, line)) {
    std::stringstream ss{line};
    SimpleIndexEntry entry;
    ss >> entry.termid;
    std::int32_t docid, sz;
    while (ss >> docid && ss >> sz) {
      SimpleIndexEntry::Posting posting;
      posting.docid = docid;
      for (auto i = 0; i < sz; ++i) {
        std::int32_t position;
        ss >> position;
        posting.positions.push_back(position);
      }
      entry.postings.push_back(posting);
    }
    out.push_back(entry);
  }
  return stream;
}

bool ParseSimpleIndex(const std::string& file_path, SimpleIndex& out) {
  std::ifstream inp{file_path};
  inp >> out;
  return true;
}