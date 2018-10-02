#include <iostream>
#include <cstdint>
#include <vector>

struct PostingDoc {
  std::int32_t docid;
  std::vector<std::int32_t> positions;
};

using PostingsList = std::vector<PostingDoc>;

struct DocPositions {
  std::int32_t docid;
  std::int32_t pos1;
  std::int32_t pos2;
};

using PositionalAnswer = std::vector<DocPositions>;

std::int32_t abs(std::int32_t value) {
  return value < 0 ? -value: value;
}

void PositionalIntersect(
      const PostingsList& p1,
      const PostingsList& p2,
      std::int32_t k,
      PositionalAnswer& answer) {
  answer.clear();
  auto iter1 = p1.begin();
  auto iter2 = p2.begin();
  while (iter1 != p1.end() && iter2 != p2.end()) {
    if (iter1->docid == iter2->docid) {
      std::vector<std::int32_t> l;
      auto& pp1 = iter1->positions;
      auto& pp2 = iter2->positions;
      auto pp1_iter = pp1.begin();
      auto pp2_iter = pp2.begin();
      while (pp1_iter != pp1.end()) {
        while (pp2_iter != pp2.end()) {
          if (abs(*pp1_iter - *pp2_iter) <= k) {
            l.push_back(*pp2_iter);
          } else {
            if (*pp2_iter > *pp1_iter) {
              break;
            }
          }
          ++pp2_iter;
        }
        while (l.size() > 0 && abs(l[0] - *pp1_iter) > k) {
          l.erase(l.begin());
        }
        for (auto ps: l) {
          answer.push_back({iter1->docid, *pp1_iter, ps});
        }
        ++pp1_iter;
      }
      ++iter1;
      ++iter2;
    } else {
      if (iter1->docid < iter2->docid) {
        ++iter1;
      } else {
        ++iter2;
      }
    }
  }
}

int main() {
  PostingsList p1 {{1, {1, 2, 5, 8, 10}},
                   {2, {3, 6, 8, 10, 15}},
                   {3, {3, 5, 9, 11, 15, 17}}
                  };
  PostingsList p2 {{1, {3, 9}},
                   {2, {12}},
                   {3, {10, 12, 16}}
                  };
  PositionalAnswer answer;
  PositionalIntersect(p1, p2, 1, answer);
  for (auto& a: answer) {
    std::cout << a.docid <<
      "<" << a.pos1 << ", " << a.pos2 << ">" << std::endl;
  }
}