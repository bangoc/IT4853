#ifndef ALGORITHM_FILES_H_
#define ALGORITHM_FILES_H_

#include <fstream>
#include <string>
#include <vector>

bool ParseToken(const std::string& file_name,
      std::vector<std::string>& out);

#endif  // ALGORITHM_FILES_H_