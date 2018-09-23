#include "algorithm/files.h"

#include <iostream>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Usage: ./files_main in_folder" << std::endl;
    return 1;
  }

  TokenList token_list;
  IdToPath id_path;
  ParseTokenFolder(argv[1], token_list, id_path);
  std::cout << token_list << std::endl;
  std::cout << id_path;
}