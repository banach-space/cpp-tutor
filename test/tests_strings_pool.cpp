//========================================================================
// FILE:
//    test/tests_strings_pool.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Unit tests for the StringsPool class (defined in strings_pool.cpp)
//
// License: Apache License 2.0
//========================================================================
#include <strings_pool.hpp>
#include <gtest/gtest.h>

#include <string>
#include <vector>

//========================================================================
// Tests
//========================================================================
TEST(StringsPoolObject, smoke_test) {
  StringsPool strs;

  ASSERT_EQ(0, strs.size());
}

TEST(StringsPoolObject, insert_elements) {
  std::vector<std::string> test_strings = {"Andrzej", "Warzynski", "Nikita",
                                           "Dell",    "",          "A"};

  StringsPool strs{};
  for (auto str : test_strings) {
    strs.append(str);
  }

  ASSERT_EQ(strs.size(), test_strings.size());

  for (auto ii = 0; ii < strs.size(); ii++) {
    ASSERT_EQ(strs.at(ii), test_strings[ii]);
  }
}
