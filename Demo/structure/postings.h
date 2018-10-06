#ifndef STRUCTURE_POSTINGS_H_
#define STRUCTURE_POSTINGS_H_

#include "structure/base.h"
#include "structure/conversions.h"
#include "structure/dictionary.h"

#include <iostream>

bool BuildPostingTermVector(const std::string& in_folder, const std::string& out_folder);
bool SerializePostingTermVector(const std::string& file_path, const PostingTermVector& ptv);
bool ParsePostingTermVector(const std::string& file_path, PostingTermVector& ptv);

std::ostream& operator<<(std::ostream& stream, const PostingTermVector& ptv);
std::istream& operator>>(std::istream& stream, PostingTermVector& ptv);

#endif  // STRUCTURE_POSTINGS_H_