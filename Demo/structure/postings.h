#ifndef STRUCTURE_POSTINGS_H_
#define STRUCTURE_POSTINGS_H_

#include "structure/base.h"
#include "structure/conversions.h"
#include "structure/dictionary.h"

#include <iostream>

bool PrepareIndexData(const std::string& in_folder,
                      PostingTermVector& ptv,
                      IdToPath& id_path,
                      IdToTerm& id_term);
bool PrepareIndexData(const std::string& in_folder, const std::string& out_folder);
bool LoadIndexData(const std::string& index_data_folder,
                   PostingTermVector& ptv,
                   IdToPath& id_path,
                   IdToTerm& id_term);

bool SerializePostingTermVector(const std::string& file_path, const PostingTermVector& ptv);
std::ostream& operator<<(std::ostream& stream, const PostingTermVector& ptv);
std::istream& operator>>(std::istream& stream, PostingTermVector& ptv);

#endif  // STRUCTURE_POSTINGS_H_