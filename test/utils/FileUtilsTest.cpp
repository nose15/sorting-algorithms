//
// Created by lukasz on 09.04.25.
//
#include <gtest/gtest.h>
#include <FileUtils.hpp>

class FileUtilsTest : public testing::Test {};

TEST(FileUtilsTest, TestParsingThreads) {
  std::string line = "2,5-10,12";
  std::vector<uint32_t> output = FileUtils::parseInts(line);

  auto desired = std::vector<uint32_t>{2,5,6,7,8,9,10,12};
  ASSERT_EQ(output, desired);
}