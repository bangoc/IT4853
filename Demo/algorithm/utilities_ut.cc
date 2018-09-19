#include <list>

#include <algorithm/utilities.h>
#include <algorithm/resources/files.h>
#include <gtest/gtest.h>

TEST(ParseList, NoTrailing) {
  std::list<long> lexp {1, 2, 3, 5, 6};
  std::list<long> l;
  ParseList(sorted_list1, l);
  EXPECT_EQ(l, lexp);
}

TEST(ParseList, WithTrailing) {
  std::list<long> lexp {1, 2, 3, 5, 6};
  std::list<long> l;
  ParseList(sorted_list2, l);
  EXPECT_EQ(l, lexp);
}

TEST(ParseList, UnSorted) {
  std::list<long> lexp {2, 3, 1, 5, 6};
  std::list<long> l;
  ParseList(unsorted_list1, l);
  EXPECT_EQ(l, lexp);
}

TEST(ParseList, SkipPointer) {
  std::list<std::list<long>> l;
  ParseList(sorted_list3, l, 2);
  std::list<std::list<long>> lexpected {{1, 3}, {4, 6}, {8, 10}};
  EXPECT_EQ(l, lexpected);
}

TEST(ParseList, Vector) {
  std::vector<long> v;
  ParseList(sorted_list2, v);
  std::vector<long> vexpected {1, 2, 3, 5, 6};
  EXPECT_EQ(v, vexpected);
}

TEST(IsAscendingList, Ordered) {
  std::list<long> l;
  ParseList(sorted_list2, l);
  EXPECT_EQ(IsAscendingList(l), true);
}

TEST(IsAscendingList, UnOrdered) {
  std::list<long> l;
  ParseList(unsorted_list1, l);
  EXPECT_EQ(IsAscendingList(l), false);
}

TEST(IsAscendingList, OrderedVector) {
  std::vector<long> v {1, 2, 3, 5, 6};
  EXPECT_EQ(IsAscendingList(v), true);
}