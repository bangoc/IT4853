#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include "base.h"

#include <iostream>
#include <map>

std::istream& operator>>(std::istream& stream, Dictionary& dict);
std::ostream& operator<<(std::ostream& stream, const Dictionary& dict);
bool ParseDictionary(const std::string& file_name, Dictionary& out);
bool SerializeDictionary(const std::string& file_name, const Dictionary& dict);

#endif  // DICTIONARY_H_