#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>

#include "config.h"
#include "index.h"
#include "parser.h"
#include "tokenizer.h"
#include "query.h"

void PrintUsage() {
  std::cout << "Usage: vsm collection.txt \"query\" ddd.qqq" << std::endl;
  std::cout << "Other parameters can be set using environment variables\n"
            << "to use base 10 for log, set VSM_LOG_BASE=10\n"
            << "to use alpha = 2 for byte size normalization, set VSM_BNORM_ALPHA=2\n";
}

int main(int argc, char* argv[]) {
	DefaultConfig();
	if (argc != 4) {
		PrintUsage();
		return 1;
	}
	std::string query{argv[2]};
	std::string schema{argv[3]};
	if (schema.length() != 7 || schema[3] != '.') {
		PrintUsage();
		return 1;
	}
	Collection collection;
	if (!ParseCollection(collection, argv[1])) {
    return 1;
  }
  std::cout << "Query: " << query << std::endl;
  std::cout << "schema: " << schema << std::endl;
  std::cout << "Other parameters: Log Base = " << kLogBase
            << "; BNorm Alpha = " << kBnormAlpha << std::endl;
	Index index;
  for (auto& doc: collection) {
    index.AddDocument(doc);
  }
  int n = index.GetNumDocs();
  DocumentLength dl;
  switch (schema[2]) {
    case 'n':
    case 'u':
      index.GetLengthNU(dl, schema[2]);
      break;
    case 'c':
      index.GetLengthC(dl, schema);
      break;
    case 'b':
      index.GetLengthB(dl, schema[2], 1.0);
      break;
    default:
      std::cerr << "Unknown normalization!\n";
      return 1;
  }
  std::cout << "Document length (" << schema[2] << "): \n";
  for (int i = 0; i < dl.size(); ++i) {
    std::cout << "dl[" << i << "] = " << dl[i] << "\t";
  }
  std::cout << "\n";
  Index::Terms terms;
  DocScore rsv;
  index.GetTerms(terms);
  std::cout << std::setprecision(3) << std::setw(6);
  std::cout << "Term\tdf\t";
  for (int i = 0; i < n; ++i) {
    std::cout << "VB" << i << "\t.\t.\t";
  }
  Query q;
  q.Parse(query);
  std::cout << "Query\t.\t" << "\n";
  std::cout << ".\t.\t";
  for (int i = 0; i < n; ++i) {
    std::cout << "tf\td" << i << "\td" << i << "*\t";
  }
  std::cout << "tf\tq\t\n";
  for (auto& term: terms) {
    std::cout << term << "\t" << index.GetDf(term) << "\t";
    int tf_tq = q.GetTf(term);
    double w_tq = 
        q.GetWtf(term, schema[4]) * index.GetWdf(term, schema[5]);
    for (int i = 0; i < n; ++i) {
      double w = index.GetWtf(term, i, schema[0]) *
                 index.GetWdf(term, schema[1]);
      double wnorm = w / dl[i];
      std::cout << index.GetTf(term, i) << "\t" << w << "\t" 
                << wnorm << "\t";
      rsv[i] += wnorm * w_tq;
    }
    std::cout << tf_tq << "\t" << w_tq;
    std::cout << "\n";
  }
  Scores scores;
  for (auto& doc_score: rsv) {
    std::cout << "rsv[VB" << doc_score.first << ", q] = " 
               << doc_score.second << "\t";
    scores.push_back(doc_score);
  }
  std::cout << "\n";
  std::sort(scores.begin(), scores.end(), 
            [] (const auto& a, const auto& b) {return a.second > b.second;});
  std::cout << "Ranking:\n";
  for (auto& doc_score: scores) {
    std::cout << "VB" << doc_score.first << "\n";
  }
	return 0;
}