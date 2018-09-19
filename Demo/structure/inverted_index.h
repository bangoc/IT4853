#include "structure/dictionary.h"
#include "structure/posting.h"

struct InvertedIndex {
  Dictionary dict;
  Postings postings;
};