//==============================================================================
// FILE:
//    strings_2_main.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Content:
//    - SSO (short string optimisation)
//    - implications of copying strings (dynamic allocations), in particular
//      how std::string_view is superior in this respect
//
//    Too fully appreciate these examples, build this file with multiple
//    compilers (e.g. GCC and clang, or different versions of those) and
//    compare the output. The size of the internal buffer for SSO should differ
//    each time, which should be obvious from the output.
//
// 		Key takeaways:
//		- Using string_view guarantees that there will be no dynamic
//      memory allocations
//    - Most modern implementations of STL use SSO, but the size of the internal
//      buffer is not fixed
//
//
// License: MIT
//==============================================================================
#include "cppt_ag.hpp"
#include "cppt_tools.hpp"

#include <algorithm>
#include <iostream>
#include <new>
#include <string>
#if __cplusplus >= 201703L
#include <string_view>
#endif

//==============================================================================
// Helper functions
//==============================================================================
// Global replacements for `new` and `delete`. Normally you wouldn't overload
// these without very compelling reasons. Here we just want to track every
// implicit invocation. Otherwise these are rather basic replacements.
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

// Dummy functions that take strings. In neither case there should be any
// copying involved, right?
void getString(const std::string& str) {}
#if __cplusplus == 201703L
void getStringView(std::string_view sv) {}
#endif

//==============================================================================
// main
//==============================================================================
int main(int argc, const char** argv) {
  cppt::header(argv[0]);

  size_t sec_num = {1};
  const char message[] = "0123456789-123456789-123456789-123456789";

  // 1. DEFINE SOME STRINGS
  // Are new and delete being invoked? When and why?
  std::cout << sec_num++ << ". COPY ASSIGNMENT:\n";

  std::string small = {"0123456789"};
  std::string large = {"0123456789abcdefghijklmnopqrs"};
  std::string very_large = {
      "0123456789ABCDEFGHIKLMNOPQRSabcdefghijklmnopqrs0123456789ABCDEFGHIKLMNOP"
      "QRSabcdefghijklmnopqrs"};

  std::cout << "\n" << sec_num++ << ". EXPLICIT CONSTRUCTOR CALL:\n";

  std::string five_chars("AAAAA");
  std::string fifteen_chars(15, 'B');
  std::string sixteen_chars(16, 'C');
  std::string one_hundred_chars(100, 'D');

  // 2. CREATE SUBSTRINGS + string_view
  // Are new and delete being invoked? When and why?
  std::cout << "\n" << sec_num++ << ". SUBSTRINGS + STD::STRING_VIEW:\n";

  std::string small_substr = small.substr(5);
  std::string large_substr = large.substr(15);
  std::string very_large_substr = very_large.substr(15);

#if __cplusplus >= 201703L
  std::string_view small_sv(small);
  std::string_view large_sv(large);
  std::string_view very_large_sv(very_large);
#endif

  // 3. CALL getString
  // Are new and delete being invoked? When and why?
  std::cout << "\n" << sec_num++ << ". CALL getString:\n";

  getString(large);
  getString("0123456789-123456789-123456789-123456789");
  getString(message);

  // 4. CALL getStringView
  // Are new and delete being invoked? When and why?
#if __cplusplus >= 201703L
  std::cout << "\n" << sec_num++ << ". CALL getStringView:\n";

  getStringView(large);
  getStringView("0123456789-123456789-123456789-123456789");
  getStringView(message);
#endif

  // 5. DEALLOCATION
  std::cout << "\n" << sec_num << ". DEALLOCATE AUTOMATIC VARIABLES:\n";
  std::cout << "(after the closing `{`)\n";

  cppt::footer(argv[0]);

  // Overloaded operator delete() will be called after closing
  // `{`.
}
