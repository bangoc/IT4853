#include "intersect.h"

#include <iostream>
#include <list>

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << "Usage: ./p list1 list2" << std::endl;
    return 1;
  }
  std::list<int> la, lb, out;
  ParseList(argv[1], la);
  ParseList(argv[2], lb);
  Intersect(la, lb, out);
  for (auto it = out.begin(); it != out.end(); ++it) {
    std::cout << " " << *it;
  }
}