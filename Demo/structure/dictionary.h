#ifndef STRUCTURE_DICTIONARY_H_
#define STRUCTURE_DICTIONARY_H_

#include "structure/base.h"

#include <iostream>
#include <map>

std::istream& operator>>(std::istream& stream, Dictionary& dict);
std::ostream& operator<<(std::ostream& stream, const Dictionary& dict);
bool ParseDictionary(const std::string& file_name, Dictionary& out);
bool SerializeDictionary(const std::string& file_name, const Dictionary& dict);

#endif  // STRUCTURE_DICTIONARY_H_