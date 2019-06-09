//========================================================================
// FILE:
//    strings_1_main.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Code samples to help understand the difference between:
//      - char* and char[] (based on the result of sizeof)
//      - C-strings, std::string and std::string_view (based on the result of
//        sizeof)
//      - various ways of reversing a string (based on the representation)
//    C++17 specific code was commented out with macros. It's best to study
//    strings_reverse.cpp alongside this file.
//
// License: MIT
//========================================================================
#include <algorithm>
#include <iostream>
#include <string>
#if __cplusplus >= 201703L
#include <string_view>
#endif

#include "../include/strings_reverse.hpp"

int main() {
  // 1. DEFINE THE STRINGS
  char hello_c[] = "Hello World!";
  const char* hello_c_c = "Hello World!";
  std::string hello_cpp(hello_c);
#if __cplusplus >= 201703L
  std::string_view hello_sv(hello_cpp);
#endif

  // 2. PRINT THE STRINGS
  std::cout << "C-string (char[]): " << hello_c << std::endl;
  std::cout << "C-string (const char*): " << hello_c_c << std::endl;
  std::cout << "C++ string: " << hello_cpp << std::endl;
#if __cplusplus >= 201703L
  std::cout << "C++ string_view: " << hello_sv << std::endl;
#endif
  std::cout << std::endl;

  // 3. PRINT THE SIZES
  std::cout << "Size of hello_c: " << sizeof(hello_c) << std::endl;
  std::cout << "Size of hello_c_c: " << sizeof(hello_c_c) << std::endl;
  std::cout << "Size of hello_cpp: " << sizeof(hello_cpp) << std::endl;
#if __cplusplus >= 201703L
  std::cout << "Size of hello_sv: " << sizeof(hello_sv) << std::endl;
#endif
  std::cout << std::endl;

  // 4. REVERSE THE STRINGS
  reverse_c_str(hello_c);
  std::cout << "Reverse of hello_c: " << hello_c << std::endl;

  // UB
  // reverse_c_str(const_cast<char*>(hello_c_c));
  // std::cout << "Reverse of hello_c: " << hello_c << std::endl;

  reverse_cpp_str_swap(&hello_cpp);
  std::cout << "Reverse of hello_cpp: " << hello_cpp << std::endl;

  reverse_cpp_str_alg(&hello_cpp);
  std::cout << "Reverse of hello_cpp: " << hello_cpp << std::endl;

#if __cplusplus >= 201703L
  // Compiler error
  // std::reverse(&hello_sv);
  // std::reverse(hello_sv.begin(), hello_sv.end());
  // std::cout << "Reverse of hello_sv: " << hello_sv << std::endl;
#endif

  std::cout << std::endl;
}
