//========================================================================
// FILE:
//    strings.cpp
//
// AUTHOR:
//  banach-space@github
//
// DESCRIPTION:
//   Helper functions for tutoring the concept of strings in C and C++
//
// License: MIT
//========================================================================
#include <strings.hpp>

void reverse(char *input_str) {
  if ('\0' == *input_str) {
    return;
  }

  char tmp = '\0';
  char *str_end = input_str;
  char *str_start = input_str;

  while ('\0' != *str_end) {
    str_end++;
  }
  str_end--;

  while (str_end > str_start) {
    tmp = *str_start;
    *str_start++ = *str_end;
    *str_end-- = tmp;
  }
}

void reverse(std::string *input_str) {
  size_t length = input_str->length();

  // Swap character starting from two corners
  for (size_t ii = 0; ii < length / 2; ii++) {
    std::swap((*input_str)[ii], (*input_str)[length - ii - 1]);
  }
}
