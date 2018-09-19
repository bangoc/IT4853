#include "structure/postings.h"

#include <string>

void CreateDemoPostings() {
  Postings postings {{{1, {1, 3, 5}}, {2, {2, 6, 8}}, {3, {5, 8, 9, 12}}},
                     {{3, {1, 2, 6}}, {5, {2, 5, 8}}},
                     {{2, {5, 7, 9, 10}}, {6, {1, 3, 5, 7, 9, 11}}}
                    };
  SerializePostings("demo_postings1.txt", postings);
}

int main() {
  CreateDemoPostings();
}