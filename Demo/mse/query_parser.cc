#include "query_parser.h"

#include "stick_tokenizer.h"
#include "vsm_query.h"

void ParseVSMQuery(const std::string& query_text, VSMQuery& query,
                   InvertedIndex& index) {
  std::vector<std::string> query_tokens;
  ParseTokenLine(query_text, query_tokens);
  std::vector<std::int32_t> term_ids;
  for (auto& tk: query_tokens) {
    auto it = index.term_id.find(tk);
    if (it != index.term_id.end()) {
      term_ids.push_back(it->second);
    }
  }
  query.Init(term_ids);
}