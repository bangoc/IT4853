#include "index_reader.h"

#include "index_constant.h"
#include "inverted_index.h"

#include <algorithm>
#include <fstream>
#include <sstream>

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
    std::ifstream inp{index_data_folder + "/" + kPtvName};
    inp >> ptv;
  }
  {
    std::ifstream inp{index_data_folder + "/" + kIdPathName};
    inp >> id_path;
  }
  {
    std::ifstream inp{index_data_folder + "/" + kIdTermName};
    inp >> id_term;
  }
  return true;
}

InvertedIndex::InvertedIndex(const std::string& index_data_path) {
  LoadIndexData(index_data_path, ptv, id_path, id_term);
  N = static_cast<double>(id_path.size());
  ld.resize(id_path.size(), 0);
  CalculateLd(ptv, ld, nullptr);
  for (auto& it: id_term) {
    term_id[it.second] = it.first;
  }
}
