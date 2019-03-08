//========================================================================
// FILE:
//    null_vs_nullptr_main.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Demonstrates the nullptr literal and the NULL macro. When dealing with
//    pointers NULL, nullptr and 0 (the integer) are equivalent. However,
//    nullptr should be used exclusively!
//
//    GCC and CLANG give different warnings - it is worth building with both
//    and comparing.
//
// License: MIT
//========================================================================
#include <cassert>
#include <iostream>
#include "cpp_tutor.h"

//========================================================================
// Helper functions
//========================================================================
void foo(int i) { std::cout << "foo: Integer overload\n"; }
void foo(int *pi) { std::cout << "foo: Pointer to integer overload\n"; }
void foo(double *pd) { std::cout << "foo: Pointer to double overload\n"; }
void foo(std::nullptr_t nullp) { std::cout << "foo: Null pointer overload\n"; }

void bar(int i) { std::cout << "bar: Integer overload\n"; }
void bar(int *pi) { std::cout << "bar: Pointer to integer overload\n"; }

//========================================================================
// main
//========================================================================
int main() {
  // 1. EQUIVALENCE OF 0,NULL AND nullptr - INTEGERS AND POINTERS
  int var_a = NULL;
  int *var_b = 0;
  assert(0 == NULL);
  assert(0 == nullptr);

#ifdef COMPILATION_ERROR
  int var_c = nullptr;
  int *var_d = 10;
#endif

  // 2. int vs NULL vs nullptr IN FUNCTION CALLS
  int *ptr_int;
  double *ptr_double;

  foo(var_a);
  foo(ptr_int);
  foo(ptr_double);
  foo(0);
  // Would be ambiguous without void foo(nullptr_t)
  foo(nullptr);
#ifdef COMPILATION_ERROR
  // Ambiguous if NULL is an integral null pointer constant (as is the case in
  // most implementations)
  foo(NULL);
#endif

  bar(0);
#ifdef COMPILATION_ERROR
  // Ambiguous even though there's only one overload for pointers
  bar(NULL);
#endif
}
