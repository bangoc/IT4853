#ifndef QUERY_PARSER_H_
#define QUERY_PARSER_H_

#include "vsm_query.h"
#include "inverted_index.h"

void ParseVSMQuery(const std::string& query_text, VSMQuery& query,
                   InvertedIndex& index);

#endif  // QUERY_PARSER_H_