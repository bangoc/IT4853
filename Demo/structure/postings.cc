#include "algorithm/files.h"
#include "structure/postings.h"

#include <algorithm>

namespace {

void AddToken(const Token& token, IdToTerm& id_term, PostingTermVector& ptv,
              bool new_term, bool new_doc, bool new_pos) {
  if (new_term) {
    id_term[id_term.size()] = token.term;
    PostingTerm posting_term;
    posting_term.termid = id_term.size() - 1;
    PostingDoc posting_doc;
    posting_doc.docid = token.docid;
    posting_doc.positions.push_back(token.position);
    posting_term.postings.push_back(posting_doc);
    ptv.push_back(posting_term);
  } else if (new_doc) {
    PostingTerm& posting_term = ptv[ptv.size() - 1];
    PostingDoc posting_doc;
    posting_doc.docid = token.docid;
    posting_doc.positions.push_back(token.position);
    posting_term.postings.push_back(posting_doc);
  } else if (new_pos) {
    PostingTerm& posting_term = ptv[ptv.size() - 1];
    PostingDoc& posting_doc = posting_term.postings[posting_term.postings.size() - 1];
    posting_doc.positions.push_back(token.position);
  } else {
    // This should not happen
  }
}

}// namespace

bool BuildPostingTermVector(const std::string& in_folder, const std::string& out_folder) {
  TokenList token_list;
  IdToPath id_path;
  ParseTokenFolder(in_folder, token_list, id_path);
  std::sort(token_list.begin(), token_list.end());
  IdToTerm id_term;
  PostingTermVector ptv;
  AddToken(token_list[0], id_term, ptv, true, true, true);
  for (auto i = 2; i < token_list.size(); ++i) {
    Token& token1 = token_list[i - 1];
    Token& token2 = token_list[i];
    if (token2.term != token1.term) {
      AddToken(token2, id_term, ptv, true, true, true);
    } else if (token2.docid != token1.docid) {
      AddToken(token2, id_term, ptv, false, true, true);
    } else if (token2.position != token1.position) {
      AddToken(token2, id_term, ptv, false, false, true);
    } else {
      // This should not happen
    }
  }
  std::experimental::filesystem::create_directories(out_folder);
  SerializePostingTermVector(out_folder + "/ptv.dat", ptv);
  SerializeIdToPath(out_folder + "/id_path.dat", id_path);
  SerializeIdToTerm(out_folder + "/id_term.dat", id_term);
  return true;
}

std::ostream& operator<<(std::ostream& stream, const PostingTermVector& ptv) {
  std::stringstream ss;
  for (const auto& entry: ptv) {
    ss << entry.termid;
    for (const auto& posting_doc: entry.postings) {
      ss << " " << posting_doc.docid << " " << posting_doc.positions.size();
      for (const auto& position: posting_doc.positions) {
        ss << " " << position;
      }
    }
    ss << std::endl;
  }
  stream << ss.str();
  return stream;
}

bool SerializePostingTermVector(const std::string& file_path, const PostingTermVector& ptv) {
  std::ofstream output_file{file_path};
  output_file << ptv;
  return true;
}

std::istream& operator>>(std::istream& stream, PostingTermVector& ptv) {
  std::string line;
  ptv.clear();
  while (std::getline(stream, line)) {
    std::stringstream ss{line};
    PostingTerm posting_term;
    ss >> posting_term.termid;
    std::int32_t docid, sz;
    while (ss >> docid && ss >> sz) {
      PostingDoc posting_doc;
      posting_doc.docid = docid;
      for (auto i = 0; i < sz; ++i) {
        std::int32_t position;
        ss >> position;
        posting_doc.positions.push_back(position);
      }
      posting_term.postings.push_back(posting_doc);
    }
    ptv.push_back(posting_term);
  }
  return stream;
}

bool ParsePostingTermVector(const std::string& file_path, PostingTermVector& ptv) {
  std::ifstream inp{file_path};
  inp >> ptv;
  return true;
}