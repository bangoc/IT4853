template<typename T>
void Intersect(const T& la, const T& lb, T& out) {
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
}