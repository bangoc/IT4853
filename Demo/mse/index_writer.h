#ifndef INDEX_WRITER_H_
#define INDEX_WRITER_H_

#include "base.h"
#include "conversions.h"
#include "dictionary.h"

#include <iostream>

bool PrepareIndexData(const std::string& in_folder,
                      PostingTermVector& ptv,
                      IdToPath& id_path,
                      IdToTerm& id_term);
bool PrepareIndexData(const std::string& in_folder, const std::string& out_folder);

bool SerializePostingTermVector(const std::string& file_path, const PostingTermVector& ptv);
std::ostream& operator<<(std::ostream& stream, const PostingTermVector& ptv);

#endif  // INDEX_WRITER_H_