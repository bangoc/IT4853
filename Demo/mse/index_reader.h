#ifndef INDEX_READER_H_
#define INDEX_READER_H_

#include "base.h"
#include "conversions.h"
#include "dictionary.h"

#include <iostream>

bool LoadIndexData(const std::string& index_data_folder,
                   PostingTermVector& ptv,
                   IdToPath& id_path,
                   IdToTerm& id_term);

std::istream& operator>>(std::istream& stream, PostingTermVector& ptv);

#endif  // INDEX_READER_H_