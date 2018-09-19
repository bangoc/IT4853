#include "structure/postings.h"

#include <fstream>
#include <sstream>
#include <string>

bool ParsePostings(const std::string& file_name, Postings& out) {
  std::ifstream inp{file_name};
  std::string line;
  while (std::getline(inp, line)) {
    std::stringstream ss{line};
    std::string scard;
    PostingList list;
    while (std::getline(ss, scard)) {
      PostingCard card;
      ss >> card.docid;
      std::int32_t pos;
      while (ss >> pos) {
        card.positions.push_back(pos);
      }
      list.push_back(card);
    }
    out.push_back(list);
  }
  return true;
}


bool SerializePostings(const std::string& file_name, const Postings& postings) {
  std::ostringstream out;
  for (const PostingList& list: postings) {
    for (const PostingCard& card: list) {
      out << card.docid;
      for (std::int32_t pos: card.positions)
        out << " " << pos;
      out << "|";
    }
    out << std::endl;
  }
  std::ofstream fout{file_name};
  fout << out.str();
  return true;
}