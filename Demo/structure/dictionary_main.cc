#include "structure/base.h"
#include "structure/dictionary.h"

void CreateDemoDictionary() {
  Dictionary dict {{"a", {3, 0}},
                   {"b", {5, 1}},
                   {"c", {2, 2}},
                  };
  SerializeDictionary("demo_dictionary1.txt", dict);
}

int main() {
  CreateDemoDictionary();
}