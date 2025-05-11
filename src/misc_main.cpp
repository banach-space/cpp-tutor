//==============================================================================
// FILE:
//    misc_main.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//  * is_object_v
//  * sizeof for empty objects
//  * has_unique_object_representations_v
//
// License: MIT
//==============================================================================
#include <cppt_ag.hpp>
#include <cppt_tools.hpp>

#include <iostream>
//==============================================================================
// Data types
//==============================================================================
// This is an empty struct, so its size should be 0, right? See below.
struct Empty {
};

// Would should be the size of `NonEmpty`? See below.
struct NonEmpty : Empty {
  char a;
};

struct UniqueRepr {
  int a, b;
};

struct NonUniqueRepr {
  char a;
  int b;
};

// Surely the size of A and B should be identical?
struct A {
  short s;
  int n;
  char c;
};

struct B {
  char c;
  short s;
  int n;
};

//==============================================================================
// main
//==============================================================================
int main(int argc, char *argv[]) {
  cppt::header(argv[0]);

  size_t sec_num = {1};

  //-------------------------------------------------------------------------
  // 1. WHAT IS AN OBJECT IN C++?
  //-------------------------------------------------------------------------
  std::cout << sec_num++ << ". WHAT IS AN OBJECT IN C++?\n";
  std::cout << "Is `int` an object? Answer: " << std::is_object_v<int> << std::endl;
  // The standard calls out functions as non-objects, despite them occupying
  // memory (one of the criteria)
  std::cout << "Is function an objec? Answer: "
            << std::is_object_v<decltype(main)> << std::endl;

  //-------------------------------------------------------------------------
  // 2. SIZEOF EMPTY?
  //  Empty Base Optimization (EBO), see:
  //    * https://en.cppreference.com/w/cpp/language/ebo
  //-------------------------------------------------------------------------
  std::cout << "\n" << sec_num++ << ". SIZEOF EMPTY?\n";
  // Somewhat surprisingly, the size of `Empty` is not 0! All C++ types occupy
  // non-zero bytes of storage by definition (even empty objects). Otherwise,
  // an object and its neighbor could occupy same memory address - that would be
  // confusing!
  Empty em;
  std::cout << "What's the size of an empty class? Answer: " << sizeof em << std::endl;
  // Interestingly, due to "Empty Base Optimization" (EBO), `NonEmpty` (which
  // inherits from `Empty`) will also have size 1 (i.e. the size of its only
  // member variable).
  NonEmpty nem;
  std::cout << "What's the size of an non-empty class? Answer: " << sizeof nem << std::endl;

  //-------------------------------------------------------------------------
  // 3. SIZEOF STRUCT
  //  Due to padding, the size of A and B will be different.
  //-------------------------------------------------------------------------
  std::cout << "\n" << sec_num++ << ". SIZEOF STRUCT?\n";
  A a;
  B b;
  std::cout << "What's the size of A? Answer: " << sizeof a << std::endl;
  std::cout << "What's the size of B? Answer: " << sizeof b << std::endl;

  //-------------------------------------------------------------------------
  // 4. UNIQUE REPRESENTATION?
  //  The trait that's being checked here is true for types uniquely defined by
  //  their values. This will exclude e.g.
  //    * types requiring padding (C++ does not specify what happens to those),
  //  and
  //    * floating point types (due to e.g. NoN not having standard
  //    representation).
  //-------------------------------------------------------------------------
  std::cout << "\n" << sec_num++ << ". UNIQUE REPRESENTATION?\n";
  std::cout
      << "Does `int` have unique representation? Answer: "
      << std::has_unique_object_representations_v<int> << std::endl;
  std::cout
      << "Does `float` have unique representation? Answer: "
      << std::has_unique_object_representations_v<float> << std::endl;
  std::cout
      << "Does `UniqueRepr` have unique representation? Answer: "
      << std::has_unique_object_representations_v<UniqueRepr> << std::endl;
  std::cout
      << "Does `UniqueRepr` have unique representation? Answer: "
      << std::has_unique_object_representations_v<UniqueRepr> << std::endl;
  std::cout
      << "Does `NonUniqueRepr` have unique representation? Answer: "
      << std::has_unique_object_representations_v<NonUniqueRepr> << std::endl;

  cppt::footer(argv[0]);
}
