#ifndef STRUCTURE_CONVERSIONS_H_
#define STRUCTURE_CONVERSIONS_H_

#include <iostream>
#include <map>
#include <string>

using IdToPath = std::map<std::int32_t, std::string>;
using IdToTerm = std::map<std::int32_t, std::string>;
using TermToId = std::map<std::string, std::int32_t>;

std::ostream& operator<<(std::ostream& stream, const std::map<std::int32_t, std::string>& m);
std::istream& operator>>(std::istream& stream, std::map<std::int32_t, std::string>& m);
bool ParseIdToPath(const std::string& file_name, IdToPath& out);
bool SerializeIdToPath(const std::string& file_name,
                       const IdToPath& id_to_path);
bool ParseIdToTerm(const std::string& file_name, IdToTerm& out);
bool SerializeIdToTerm(const std::string& file_name,
                       const IdToTerm& id_to_term);

#endif  // STRUCTURE_CONVERSIONS_H_