//==============================================================================
// FILE:
//    strings_2_main.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Content:
//    - SSO, i.e. Short String Optimisation.
//    - Implications of copying strings (dynamic allocations) and how
//    std::string_view is superior in this respect.
//
//    Too fully appreciate these examples, build this file with different
//    compilers (e.g. GCC and clang) or different versions of one compiler
//    (e.g. Clang 14 vs Clang 20) and compare the output. The size of the
//    internal buffer for SSO should differ each time (this should be obvious
//    from the printed output).
//
// 		Key takeaways:
//		- Using string_view guarantees that there will be no dynamic
//      memory allocations.
//    - Most modern implementations of STL use SSO, but the size of the internal
//      buffer is not fixed.
//
// License: MIT
//==============================================================================
#include "cppt_ag.hpp"
#include "cppt_tools.hpp"

#include "llvm/Support/raw_ostream.h"
#include <llvm/ADT/StringRef.h>

#include <algorithm>
#include <iostream>
#include <new>
#include <string>

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
void getStringView(std::string_view sv) {}
void getStringRef(llvm::StringRef sv) {}

//==============================================================================
// main
//==============================================================================
int main(int argc, const char** argv) {
  cppt::header(argv[0]);

  size_t sec_num = {1};
  const char message[] = "0123456789-123456789-123456789-123456789";

  //-------------------------------------------------------------------------
  // 1. DEFINE SOME STRINGS
  //-------------------------------------------------------------------------
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

  //-------------------------------------------------------------------------
  // 2. CREATE SUBSTRINGS + string_view + StringRef
  //-------------------------------------------------------------------------
  // Are new and delete being invoked? When and why?
  std::cout << "\n" << sec_num++ << ". SUBSTRINGS + STD::STRING_VIEW:\n";

  std::string small_substr = small.substr(5);
  std::string large_substr = large.substr(15);
  std::string very_large_substr = very_large.substr(15);

  std::string_view small_sv(small);
  std::string_view large_sv(large);
  std::string_view very_large_sv(very_large);

  llvm::StringRef small_sr(small);
  llvm::StringRef large_sr(large);
  llvm::StringRef very_large_sr(very_large);

  //-------------------------------------------------------------------------
  // 3. CALL getString
  //-------------------------------------------------------------------------
  // Are new and delete being invoked? When and why?
  std::cout << "\n" << sec_num++ << ". CALL getString:\n";

  getString(large);
  getString("0123456789-123456789-123456789-123456789");
  getString(message);

  //-------------------------------------------------------------------------
  // 4. CALL getStringView
  //-------------------------------------------------------------------------
  // Are new and delete being invoked? When and why?
  std::cout << "\n" << sec_num++ << ". CALL getStringView:\n";

  getStringView(large);
  getStringView("0123456789-123456789-123456789-123456789");
  getStringView(message);

  //-------------------------------------------------------------------------
  // 5. CALL getStringVRef
  //-------------------------------------------------------------------------
  // Are new and delete being invoked? When and why?
  std::cout << "\n" << sec_num++ << ". CALL getStringView:\n";

  getStringView(large);
  getStringView("0123456789-123456789-123456789-123456789");
  getStringView(message);

  //-------------------------------------------------------------------------
  // 6. DEALLOCATION
  //-------------------------------------------------------------------------
  std::cout << "\n" << sec_num << ". DEALLOCATE AUTOMATIC VARIABLES:\n";
  std::cout << "(after the closing `{`)\n";

  cppt::footer(argv[0]);

  // Overloaded operator delete() will be called after closing
  // `{`.
}
