#ifndef INDEX_H_
#define INDEX_H_

#include "base.h"

class Index {
 public:

  using Terms = std::vector<std::string>;

  // return docId
  int AddDocument(const std::string& doc);

  int GetNumDocs() const;
  bool GetTerms(Terms& out) const;
  bool GetLengthNU(DocumentLength& out, char measure) const;
  bool GetLengthB(DocumentLength& out, char measure, double alpha) const;
  bool GetLengthC(DocumentLength& out, const std::string& schema) const;
  int GetTf(const std::string& term, int doc_id) const;
  int GetDf(const std::string& term) const;
  int GetMaxTf(int doc_id) const;
  double GetAveTf(int doc_id) const;
  double GetWtf(const std::string& term, int doc_id, char multiplier) const;
  double GetWdf(const std::string& term, char multiplier) const;
 private:
  TermFrequency tf;
  DocumentFrequency df;
  int max_docid = 0;
};

#endif  // INDEX_H_