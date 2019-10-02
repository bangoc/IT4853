#ifndef BASE_H_
#define BASE_H_

#include <map>
#include <string>
#include <vector>

using TermWeight = std::map<int, double>;
using TermsTable = std::map<std::string, TermWeight>;
using Collection = std::vector<std::string>;
using TermsList = std::vector<std::string>;
using TermFrequency = std::map<std::string, std::map<int, int>>;
using DocumentFrequency = std::map<std::string, int>;
using DocumentLength = std::vector<double>;
using DocScore = std::map<int, double>;
using Scores = std::vector<std::pair<int, double>>;

double MyLog(double param);

#endif  // BASE_H_