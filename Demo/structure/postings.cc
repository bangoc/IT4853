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

const std::string ptv_name = "ptv.dat";
const std::string id_path_name = "id_path.dat";
const std::string id_term_name = "id_term.dat";

}// namespace

bool PrepareIndexData(const std::string& in_folder,
                      PostingTermVector& ptv,
                      IdToPath& id_path,
                      IdToTerm& id_term) {
  TokenList token_list;
  ParseTokenFolder(in_folder, token_list, id_path);
  std::sort(token_list.begin(), token_list.end());
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
  return true;
}

bool PrepareIndexData(const std::string& in_folder, const std::string& out_folder) {
  PostingTermVector ptv;
  IdToPath id_path;
  IdToTerm id_term;
  PrepareIndexData(in_folder, ptv, id_path, id_term);
  std::experimental::filesystem::create_directories(out_folder);
  SerializePostingTermVector(out_folder + "/" + ptv_name, ptv);
  SerializeIdToPath(out_folder + "/id_path.dat" + id_path_name, id_path);
  SerializeIdToTerm(out_folder + "/id_term.dat" + id_term_name, id_term);
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

bool LoadIndexData(const std::string& index_data_folder,
                   PostingTermVector& ptv,
                   IdToPath& id_path,
                   IdToTerm& id_term) {
  {
    std::ifstream inp{index_data_folder + "/" + ptv_name};
    inp >> ptv;
  }
  {
    std::ifstream inp{index_data_folder + "/" + id_path_name};
    inp >> id_path;
  }
  {
    std::ifstream inp{index_data_folder + "/" + id_term_name};
    inp >> id_term;
  }
  return true;
}