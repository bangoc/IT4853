#ifndef STICK_TOKENIZER_H_
#define STICK_TOKENIZER_H_

#include <string>
#include <vector>

bool ParseTokenLine(const std::string& line,
      std::vector<std::string>& out);

bool ParseTokenFile(const std::string& file_name,
      std::vector<std::string>& out);

#endif  // STICK_TOKENIZER_H_