#include <gtest/gtest.h>
#include <algorithm/resources/files.h>
#include "algorithm/files.h"
#include "algorithm/files.cc"

TEST(ParseToken, StickSeperator) {
  std::vector<std::string> tokens;
  EXPECT_EQ(ParseTokenFile(tokenized_text1, tokens), true);
  std::vector<std::string> tokens_expected {
    "Trường", "Đại Học", "Bách Khoa", "Hà Nội",
    "Viện", "Công nghệ", "thông tin", "và", "truyền thông",
    "Tìm kiếm", "và", "trình diễn", "thông tin"};
  EXPECT_EQ(tokens, tokens_expected);
}