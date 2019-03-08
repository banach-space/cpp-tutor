//========================================================================
// FILE:
//  strings_2_main.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//  Code samples to help understand:
//    * SSO (short string optimisation)
//    * implications of copying strings (dynamic allocations), in particular
//      how std::string_view is superior in this respect
//  It's reccomend to build this file with multiple compilers (e.g. GCC and
//  clang, and in particular different versions of those) and compare the
//  output. The size of the internal buffer for SSO should differ each time.
//
//  This file implements a `main` function and is meant to be used as a
//  standalone project.
//
// License: MIT
//========================================================================
#include <algorithm>
#include <iostream>
#include <new>
#include <string>
#if __cplusplus >= 201703L
#include <string_view>
#endif

void* operator new(std::size_t count) {
  std::cout << "[new]   " << count << " bytes" << std::endl;
  return std::malloc(count);
}

void operator delete(void* raw_memory) noexcept {
  if (nullptr == raw_memory) {
    return;
  }

  std::cout << "[delete]   "
            << "addr: " << raw_memory << std::endl;
  std::free(raw_memory);
}

void getString(const std::string& str) {}
#if __cplusplus == 201703L
void getStringView(std::string_view sv) {}
#endif

int main() {
  size_t sec_num = {1};
  const char message[] = "0123456789-123456789-123456789-123456789";

  // 1. DEFINE THE STRINGS
  std::cout << "==>   " << sec_num++ << " Copy assignment:" << std::endl;

  std::string small = {"0123456789"};
  std::string large = {"0123456789abcdefghijklmnopqrs"};
  std::string very_large = {
      "0123456789ABCDEFGHIKLMNOPQRSabcdefghijklmnopqrs0123456789ABCDEFGHIKLMNOP"
      "QRSabcdefghijklmnopqrs"};

  std::cout << std::endl
            << "==>   " << sec_num++
            << " Explicit constructor call:" << std::endl;

  std::string five_chars("AAAAA");
  std::string fifteen_chars(15, 'B');
  std::string sixteen_chars(16, 'C');
  std::string one_hundred_chars(100, 'D');

  // 2. CREATE SUBSTRINGS + string_view
#if __cplusplus >= 201703L
  std::cout << std::endl
            << "==>   " << sec_num++
            << " Substrings + std::string_view:" << std::endl;

  std::string small_substr = small.substr(5);
  std::string large_substr = large.substr(15);
  std::string very_large_substr = very_large.substr(15);

  std::string_view small_sv(small);
  std::string_view large_sv(large);
  std::string_view very_large_sv(very_large);
#endif

  // 3. getString
  std::cout << std::endl << "==>   " << sec_num++ << " getString:" << std::endl;

  getString(large);
  getString("0123456789-123456789-123456789-123456789");
  getString(message);

  // 4. getStringView
#if __cplusplus >= 201703L
  std::cout << std::endl
            << "==>   " << sec_num++ << " getStringView:" << std::endl;

  getStringView(large);
  getStringView("0123456789-123456789-123456789-123456789");
  getStringView(message);
#endif

  // 5. Deallocation
  std::cout << std::endl;
  std::cout << "==>   " << sec_num << " Deallocation:" << std::endl;
}
