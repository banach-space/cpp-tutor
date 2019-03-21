//========================================================================
// FILE:
//    test/cpp_tutor_ut_main.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    The main function for unit tests.
//
// License: Apache License 2.0
//========================================================================
#include <gtest/gtest.h>

GTEST_API_ int main(int argc, char *argv[]) {
  // Let Google Test parse the arguments first
  ::testing::InitGoogleTest(&argc, argv);

  // Then, you can handle any that are left

  return RUN_ALL_TESTS();
}
