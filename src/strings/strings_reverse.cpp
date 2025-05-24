//==============================================================================
// FILE:
//    strings_reverse.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Functions for reversing C and C++ strings - implementations.
//    Key takeaway - whenever possible, always use algorithms from STL.
//
// License: MIT
//==============================================================================
#include "strings_reverse.hpp"

#include <algorithm>

void reverse_c_str(char *input_str) {
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

void reverse_cpp_str_swap(std::string *input_str) {
  size_t length = input_str->length();

  // Swap characters starting from two end points.
  for (size_t ii = 0; ii < length / 2; ii++) {
    std::swap((*input_str)[ii], (*input_str)[length - ii - 1]);
  }
}

void reverse_cpp_str_alg(std::string *input_str) {
  std::reverse(input_str->begin(), input_str->end());
}
