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