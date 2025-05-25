//========================================================================
// FILE:
//    vector_main_1.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    A very simple comparison of std::vector and llvm::SmallVector:
//      * Capacity vs size.
//      * Creating a large LLVM vector (in terms of capacity and size) on the
//      stack.
//      * Are `new` + `delete` used for allocation? Only for std::vector.
//      * Short presentation of fmt - implementation of the format library.
//
//    For more in-depth comparison, see vector_main_2.cpp
//
// License: MIT
//========================================================================
#include <llvm/ADT/SmallVector.h>
#include <llvm/ADT/StringRef.h>

#include <cppt_ag.hpp>
#include <cppt_tools.hpp>
#include <iostream>
#include <vector>
#if __cplusplus >= 202000L
// Allows fancy way of printing ranges. Available in C++20. On Ubuntu, you will
// have to install libfmt-dev.
//
// This is an implementation of:
//  * https://en.cppreference.com/w/cpp/utility/format
#include <fmt/ranges.h>
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

auto printVec = [](const auto& vec) {
  for (const auto& x : vec) std::cout << x << ' ';
  std::cout << '\n';
};

//==============================================================================
// main
//==============================================================================
int main(int argc, const char** argv) {
  cppt::header(argv[0]);

  size_t sec_num = 1;

  //-------------------------------------------------------------------------
  // 1. DEFINE SOME VECTORS
  //-------------------------------------------------------------------------
  std::cout << sec_num++ << ". DEFINE VECTORS:" << std::endl;
  std::vector<int32_t> v_empty = {};
  std::vector<int32_t> v_small = {123};
  std::vector<int32_t> v_large(2000, 123);
  llvm::SmallVector<int32_t, 0> sv_empty = {};
  llvm::SmallVector<int32_t> sv_small = {321};
  llvm::SmallVector<int32_t> sv_large_default_inline(2000, 321);
  // Create 2000 elements on stack!
  llvm::SmallVector<int32_t, 2000> sv_large_all_inline(2000, 321);

  //-------------------------------------------------------------------------
  // 2. PRINT THE VECTORS
  //-------------------------------------------------------------------------
  std::cout << std::endl << sec_num++ << ". PRINT VECTORS:" << std::endl;
  std::cout << "C++ Vector: ";
  printVec(v_small);
#if __cplusplus >= 202002L
  fmt::print("v = {}\n", v_small);
#endif
  std::cout << "LLVM SmallVector: ";
  printVec(sv_small);
#if __cplusplus >= 202002L
  fmt::print("v = {}\n", sv_small);
#endif

  //-------------------------------------------------------------------------
  // 3. PRINT THE SIZES
  //-------------------------------------------------------------------------
  std::cout << std::endl << sec_num++ << ". PRINT VECTOR SIZES:" << std::endl;

  std::cout << "C++ Vector\n";
  std::cout << "Size of v_empty: " << sizeof(v_empty) << " (bytes)"
            << std::endl;
  std::cout << "Size of v_small: " << sizeof(v_small) << " (bytes)"
            << std::endl;
  std::cout << "Size of v_large: " << sizeof(v_large) << " (bytes)"
            << std::endl;

  std::cout << "LLVM SmallVector\n";
  std::cout << "Size of sv_empty: " << sizeof(sv_empty) << " (bytes)"
            << std::endl;
  std::cout << "Size of sv_small: " << sizeof(sv_small) << " (bytes)"
            << std::endl;
  std::cout << "Size of sv_large_default_inline: "
            << sizeof(sv_large_default_inline) << " (bytes)" << std::endl;
  std::cout << "Size of sv_large_all_inline: " << sizeof(sv_large_all_inline)
            << " (bytes)" << std::endl;

  //-------------------------------------------------------------------------
  // 3. PRINT THE CAPACITIES
  //-------------------------------------------------------------------------
  std::cout << std::endl
            << sec_num++ << ". PRINT VECTOR CAPACITIES:" << std::endl;

  std::cout << "LLVM SmallVector\n";
  std::cout << "Capacity of sv_small: " << sv_small.capacity_in_bytes()
            << " (bytes)" << std::endl;
  std::cout << "Capacity of sv_large_all_inline: "
            << sv_large_default_inline.capacity_in_bytes() << " (bytes)"
            << std::endl;
  std::cout << std::endl;

  cppt::footer(argv[0]);
}
