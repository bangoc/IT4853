#include "structure/conversions.h"

#include <fstream>
#include <string>
#include <sstream>

std::ostream& operator<<(std::ostream& stream, const std::map<std::int32_t, std::string>& m) {
  for (const auto& entry: m) {
    stream << entry.first << std::endl
           << entry.second << std::endl;
  }
  return stream;
}

std::istream& operator>>(std::istream& stream, std::map<std::int32_t, std::string>& m) {
  std::string sid, svalue;
  m.clear();
  while (std::getline(stream, sid) && std::getline(stream, svalue)) {
    std::stringstream ss{sid};
    std::int32_t id;
    ss >> id;
    m[id] = svalue;
  }
  return stream;
}

bool ParseIdToPath(const std::string& file_name, IdToPath& out) {
  std::ifstream inp{file_name};
  inp >> out;
  return true;
}

bool SerializeIdToPath(const std::string& file_name,
                       const IdToPath& id_to_path) {
  std::ofstream out{file_name};
  out << id_to_path;
  return true;
}

bool ParseIdToTerm(const std::string& file_name, IdToTerm& out) {
  std::ifstream inp{file_name};
  inp >> out;
  return true;
}

bool SerializeIdToTerm(const std::string& file_name,
                       const IdToTerm& id_to_term) {
  std::ofstream out{file_name};
  out << id_to_term;
  return true;
}
