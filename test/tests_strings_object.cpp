//========================================================================
// FILE:
//  test/tests_strings_object.cpp
//
// AUTHOR:
//  banach-space@github
//
// DESCRIPTION:
//  Google Test based unit tests for Strings
//
// License: Apache License 2.0
//========================================================================
#include <strings_object.hpp>
#include <gtest/gtest.h>

#include <string>
#include <vector>

//========================================================================
// Tests
//========================================================================
TEST(Strings, smoke_test) {
  Strings strs;

  ASSERT_EQ(0, strs.size());
}

TEST(Strings, insert_elements) {
  std::vector<std::string> test_strings = {
    "Andrzej",
    "Warzynski",
    "Nikita",
    "Dell",
    "",
    "A"
  };

  Strings strs{};
  for (auto str : test_strings) {
    strs.append(str);
  }

  ASSERT_EQ(strs.size(), test_strings.size());

  for (auto ii = 0; ii < strs.size(); ii++) {
    ASSERT_EQ(strs.at(ii), test_strings[ii]);
  }
}
