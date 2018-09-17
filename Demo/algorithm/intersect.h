#include <algorithm/utilities.h>

template<typename T>
bool Intersect(const T& la, const T& lb, T& out) {
  out.clear();
  auto pa = la.begin();
  auto pb = lb.begin();
  while (pa != la.end() && pb != lb.end()) {
    if (*pa == *pb) {
      out.push_back(*pa);
      ++pa;
      ++pb;
    } else if (*pa < *pb) {
      ++pa;
    } else {
      ++pb;
    }
  }
  return true;
}

template<typename T>
bool Intersect(const T& la, const T& lb, T& out, bool checking) {
  if (checking) {
    if (!IsAscendingList(la) || !IsAscendingList(lb))
      return false;
  }
  return Intersect(la, lb, out);
}
