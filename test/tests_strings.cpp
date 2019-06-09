//========================================================================
// FILE:
//    test/tests_strings.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Unit tests for functions for reversing strings (defined in strings.cpp)
//
// License: Apache License 2.0
//========================================================================
#include <strings_reverse.hpp>
#include <gtest/gtest.h>

#include <cstring>
#include <iostream>
#include <vector>

//========================================================================
// Test Fixtures
//========================================================================
struct TestReverseStrings : public ::testing::Test {
  // A vector of test strings tuples: {original string, reversed string}
  std::vector<std::tuple<std::string, std::string>> test_strings;

  TestReverseStrings() {
    test_strings = {{{""}, {""}},
                    {{"aba"}, {"aba"}},
                    {{"abba"}, {"abba"}},
                    {{"Andrzej Warzynski"}, {"iksnyzraW jezrdnA"}},
                    {{"aaaaaaaaaaaaaaaaaaaa"}, {"aaaaaaaaaaaaaaaaaaaa"}},
                    {{"xxxxxxxxxxyyyyyyyyyy"}, {"yyyyyyyyyyxxxxxxxxxx"}}};
  }

 protected:
  void SetUp() override {}
  void TearDown() override {}
};

//========================================================================
// Tests
//========================================================================
TEST_F(TestReverseStrings, reverse_c_str) {
  for (auto pair : test_strings) {
    // What follows is a bit nasty way of generating a modifiable C-string
    // (i.e.  char*) from a CPP string (i.e. resorting to raw painters and
    // dynamic memory allocation).  (one gotcha: std::string.length() won't
    // include the null character)
    auto length = std::get<1>(pair).length();
    char *current_str = nullptr;
    if (length > 0) {
      current_str = new char[length];
      strncpy(current_str, std::get<0>(pair).c_str(), length + 1);
    } else {
      current_str = new char[1];
      *current_str = '\0';
    }

    reverse_c_str(current_str);
    ASSERT_STREQ(current_str, std::get<1>(pair).c_str());

    delete[](current_str);
  }
}

TEST_F(TestReverseStrings, reverse_cpp_str_swap) {
  for (auto pair : test_strings) {
    std::string current_str(std::get<0>(pair));

    reverse_cpp_str_swap(&current_str);
    ASSERT_EQ(current_str, std::get<1>(pair).c_str());
  }
}

TEST_F(TestReverseStrings, reverse_cpp_str_alg) {
  for (auto pair : test_strings) {
    std::string current_str(std::get<0>(pair));

    reverse_cpp_str_alg(&current_str);
    ASSERT_EQ(current_str, std::get<1>(pair).c_str());
  }
}

