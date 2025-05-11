//==============================================================================
// FILE:
//    pointers_main.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Content:
//      - allocating and deallocating dynamic memory for various data structures
//      - matching various variants of `new` and `delete`
//      - arrays decaying to pointers in function calls
//
//    Key takeaway:
//      - Every allocation needs to be followed by a deallocation 
//      - Lack of deallocation leads to memory leaks
//      - Mismatch in new and delete leads to memory leaks
//
//    Experiment by:
//      - (un-)defining MEMORY_LEAK, re-building and re-running
//
// License: MIT
//==============================================================================
#include <cppt_ag.hpp>
#include <cppt_tools.hpp>

#include <iostream>
#include <string>

//==============================================================================
// Data types
//==============================================================================
struct POD {
  int iVal;
  double dVal;
};

// What size do you think this function will report?
void foo(std::string input_array[5]) {
  std::cout << "Size of the input array inside foo: " << sizeof input_array
            << std::endl;
}

// Dummy class
class Z {
  int a = 10;
};

//==============================================================================
// main
//==============================================================================
int main(int argc, char *argv[]) {
  cppt::header(argv[0]);

  //-------------------------------------------------------------------------
  // 1. BASIC "NEW"
  //-------------------------------------------------------------------------
  int *ip = new int;
  delete ip;

  auto *str = new std::string;
  delete str;

  //-------------------------------------------------------------------------
  // 2. "NEW" FOR ARRAYS (_WITHOUT_ INTIALISATION)
  //-------------------------------------------------------------------------
  int *intarr = new int[20];
  delete[] intarr;

  auto *stringarr = new std::string[10];
  delete[] stringarr;

  //-------------------------------------------------------------------------
  // 3. "NEW" FOR ARRAYS (_WITH_ INTIALISATION)
  //-------------------------------------------------------------------------
  // A pointer to 5 0-intialised PODs
  POD *pp = new POD[5]();
  delete[] pp;

  // A pointer to 9 0-intialised doubles
  auto *pd = new double[9]();
  delete[] pd;

  //-------------------------------------------------------------------------
  // 4. ALLOCATING A DYNAMIC ARRAY OF POINTERs
  //-------------------------------------------------------------------------
  auto **sp = new std::string *[5];
  for (size_t idx = 0; idx != 5; ++idx) {
    sp[idx] = new std::string;
  }

  std::cout << "Size of a pointer: " << sizeof sp << std::endl;
#ifdef MEMORY_LEAK
  // This won't deallocate memory pointed to by pointers inside sp
  delete[] sp;
#else
  for (size_t idx = 0; idx != 5; ++idx) {
    delete sp[idx];
  }
  delete[] sp;
#endif

  //-------------------------------------------------------------------------
  // 5. STACK-ALLOCATED ARRAY (size outside and inside a function)
  //-------------------------------------------------------------------------
  std::string static_stringarr[10];
  std::cout << "Size of static_stringarr: " << sizeof static_stringarr << std::endl;

  foo(static_stringarr);

  //-------------------------------------------------------------------------
  // 6. PLACEMENT NEW
  //-------------------------------------------------------------------------
  char *memory = new char[sizeof(Z)];
  Z *a = new (memory) Z;
#ifndef MEMORY_LEAK
  // Placement new requires placement delete
  delete (a, memory);
#endif

  char *memory2 = new char[5 * sizeof(Z)];
  Z *b = new (memory2) Z[5];
#ifndef MEMORY_LEAK
  // Placement new requires placement delete
  delete[](b, memory2);
#endif

  cppt::footer(argv[0]);
}
