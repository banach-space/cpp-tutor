//========================================================================
// FILE:
//  test/tests_session1.cpp
//
// AUTHOR:
//  banach-space@github
//
// DESCRIPTION:
//  Google Test based unit tests for session 1.
//
// License: Apache License 2.0
//========================================================================
#include <strings.hpp>
#include <gtest/gtest.h>

#include <cstring>
#include <iostream>
#include <string_view>
#include <vector>

//========================================================================
// Test Fixtures
//========================================================================
struct CciChapter1_Q2 : public ::testing::Test {

  // A vector of test strings tuples: {original string, reversed string}
  std::vector<std::tuple<std::string, std::string>> test_strings;

  CciChapter1_Q2() {
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
TEST_F(CciChapter1_Q2, reverse_c_string) {
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

    reverse(current_str);
    ASSERT_STREQ(current_str, std::get<1>(pair).c_str());

    delete[](current_str);
  }
}

TEST_F(CciChapter1_Q2, reverse_cpp_string) {
  for (auto pair : test_strings) {
    std::string current_str(std::get<0>(pair));

    reverse(&current_str);
    ASSERT_EQ(current_str, std::get<1>(pair).c_str());
  }
}
