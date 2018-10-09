#ifndef FILE_UTILITIES_H_
#define FILE_UTILITIES_H_

#include <fstream>
#include <vector>

template<typename T>
void LoadFile(const std::string& src_name,
              std::vector<T>& values) {
  std::ifstream inp{src_name, std::ios::binary | std::ios::ate};
  values.resize(inp.tellg() / sizeof(T));
  inp.seekg(std::ios_base::beg);
  inp.read(reinterpret_cast<char*>(values.data()),
            values.size() * sizeof(T));
}

template<typename T>
void SaveToFile(const std::string& dest_name,
                const std::vector<T>& values) {
  std::ofstream out{dest_name, std::ios::binary};
  out.write(reinterpret_cast<const char*>(values.data()),
              values.size() * sizeof(T));
}

int Compare(const std::string& file_name1, const std::string& file_name2);

#endif  // FILE_UTILITIES_H_