//========================================================================
// FILE:
//  pointers_main.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Examples showing how to:
//      * allocate and deallocate dynamic memory for various data structures
//      * correctly match various variants of `new` and `delete`
//    Note that if incorrect version of "delete" is used (or no "delete" at
//    all), then there's a memory leak.
//
//    Also, foo was implemented to show how arrays decay into pointers when
//    used as function arguments (evidenced by the size of the corresponding
//    data structure before and after entering the function).
//
//    The version guarded with MEMORY_LEAK exhibits memory leaks. Make sure you
//    understand why!
//
// License: MIT
//========================================================================
#include "cppt_ag.hpp"
#include "cppt_tools.hpp"

#include <algorithm>
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

// Plain Old Data Structure
struct POD {
  int iVal;
  double dVal;
};

// What do you think this function will return?
void foo(std::string input_array[5]) {
  std::cout << "Size of an array inside a function: " << sizeof input_array
            << std::endl;
}

// Dummy class for demonstration purposes
class Z {
  int a = 10;
};

int main() {
  // 1. BASIC "NEW"
  int *ip = new int;
  delete ip;

  auto *str = new std::string;
  delete str;

  // 2. "NEW" for arrays (_without_ intialisation)
  int *intarr = new int[20];
  delete[] intarr;

  auto *stringarr = new std::string[10];
  delete[] stringarr;

  // 3. "NEW" for arrays (_with_ intialisation)
  // A pointer to 5 0-intialised PODs
  POD *pp = new POD[5]();
  delete[] pp;
  // A pointer to 9 0-intialised doubles
  auto *pd = new double[9]();
  delete[] pd;

  // 4. Allocating a dynamic array of pointers
  auto **sp = new std::string *[5];
  for (size_t idx = 0; idx != 5; ++idx) {
    sp[idx] = new std::string;
  }

  std::cout << "Size of a pointer: " << sizeof sp << std::endl;
#ifdef MEMORY_LEAK
  delete[] sp;
#else
  for (size_t idx = 0; idx != 5; ++idx) {
    delete sp[idx];
  }
  delete[] sp;
#endif

  // 5. Stack-allocated array (to see the size)
  std::string static_stringarr[10];
  std::cout << "Size of an array: " << sizeof static_stringarr << std::endl;
  foo(static_stringarr);

  // 6. PLACEMENT "NEW"
  char *memory = new char[sizeof(Z)];
  Z *a = new (memory) Z;
#ifndef MEMORY_LEAK
  delete (a, memory);
#endif

  char *memory2 = new char[5 * sizeof(Z)];
  Z *b = new (memory2) Z[5];
#ifndef MEMORY_LEAK
  delete[](b, memory2);
#endif
}
