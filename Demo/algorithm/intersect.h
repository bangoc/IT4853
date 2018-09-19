#ifndef ALGORITHM_INTERSECT_H_
#define ALGORITHM_INTERSECT_H_

#include <algorithm/utilities.h>

#include <list>

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

template<typename T>
bool IntersectSkipPointer(const std::list<T>& la,
                          const std::list<T>& lb,
                          T& out) {
  out.clear();
  auto pa = la.begin();
  auto pb = lb.begin();
  auto ppa = pa->begin();
  auto ppb = pb->begin();
  while (pa != la.end() && pb!= lb.end()) {
    while (ppa != pa->end() && ppb != pb->end()) {
      if (*ppa == *ppb) {
        out.push_back(*ppa);
        ++ppa;
        ++ppb;
      } else if (*ppa < *ppb) {
        ++ppa;
      } else {
        ++ppb;
      }
    }
    if (ppa == pa->end()) {
      while (++pa != la.end() && (ppb == pb->end() || pa->back() < *ppb));
      if (pa != la.end()) {
        ppa = pa->begin();
      }
    }
    if (ppb == pb->end()) {
      while (++pb != lb.end() && (ppa == pa->end() || pb->back() < *ppa));
      if (pb != lb.end()) {
        ppb = pb->begin();
      }
    }
  }
  return true;
}

#endif