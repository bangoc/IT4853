/*
 list all files in a given directory
*/

#include "mse/files_iterator.h"

#include <iostream>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Usage: ./file_iterator path_to_directory\n";
    return 1;
  }
  std::vector<std::string> txt_files;
  ListFiles<std::experimental::filesystem::recursive_directory_iterator>(
    argv[1], {".txt"}, txt_files);
  for (auto &s: txt_files) {
    std::cout << s << std::endl;
  }
  return 0;
}