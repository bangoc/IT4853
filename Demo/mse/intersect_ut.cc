#include "intersect.h"
#include "resources/files.h"

#include <gtest/gtest.h>

#include <list>

TEST(Intersect, UnOrdered) {
  std::list<long> la, lb;
  ParseList(unsorted_list1, la);
  ParseList(sorted_list1, lb);
  std::list<long> out;
  EXPECT_EQ(Intersect(la, lb, out, true), false);
  EXPECT_EQ(Intersect(la, lb, out, false), true);
}

TEST(Intersect, Ordered) {
  std::list<long> la, lb;
  ParseList(sorted_list1, la);
  ParseList(sorted_list3, lb);
  std::list<long> out;
  EXPECT_EQ(Intersect(la, lb, out, true), true);
  std::list<long> lexpected {1, 3, 6};
  EXPECT_EQ(out, lexpected);
  EXPECT_EQ(Intersect(la, lb, out, false), true);
  EXPECT_EQ(out, lexpected);
}

TEST(Intersect, OrderedWithSkipPointer) {
  std::list<std::list<long>> la, lb;
  ParseList(sorted_list1, la, 2);
  ParseList(sorted_list3, lb, 2);
  std::list<long> out;
  EXPECT_EQ(IntersectSkipPointer(la, lb, out), true);
  std::list<long> lexpected {1, 3, 6};
  EXPECT_EQ(out, lexpected);
}