//========================================================================
// FILE:
//  init_aggregate_main.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Demonstrates aggregate initialization in modern C++.
//
//    Experiment by:
//      * (un-)defining RUNTIME_ERROR
//      * (un-)defining COMPILATION_ERROR
//
// License: MIT
//========================================================================
#include "cpp_tutor.h"
#include <cassert>

//========================================================================
// Helper objects
//========================================================================
// Foo has a constructor and hence is non-aggregate type. It's member variables
// are uninitialized.
class Foo {
 public:
  Foo() {}
  int get_i() { return i; }
  double get_j() { return j; }

 private:
  int i;
  double j;
};

// Bar is an aggregate type in C++14 and higher (it has in-member class
// initializers, which makes it non-aggregate in C++11). It's member variables
// are always initialized.
class Bar {
 public:
  int get_i() { return i; }
  double get_j() { return j; }

  // Default member initializers - since C++11
  int i = 0;
  double j = 0;
};

// Baz is an aggregate type. It's member variables are uninitialized.
class Baz {
 public:
  int get_i() { return i; }
  double get_j() { return j; }

  int i;
  double j;
};

// This instance of Foo is guaranteed to be zero-initialised.
static Foo global_foo;

//========================================================================
// main
//========================================================================
int main() {
  // 1. AGGREGATE INITIALISATION FOR ARRAYS
  int array_i[4] = {0, 1, 2, 3};
  int array_j[] = {0, 1, 2, 3};
  // Guaranteed to be zero-initialised
  int array_z[13] = {};

  // 2. AGGREGATE INITIALISATION FOR CLASSES
#if __cplusplus >= 201403L
  // Aggregate initialisation (only for aggregate types)
  Bar bar = {1, 3.14};
#else
  // Default initialisation.  Recall that in C++11 having in-class member
  // initializers makes a struct/class non-aggregate.
  Bar bar;
#endif

#ifdef COMPILATION_ERROR
  // Foo is non-aggregate type (it has a constructor) - this won't work
  Foo foo = {1, 2};
#else
  Foo foo;
#endif

  // 3. PARTIAL AGGREGATE INITIALISATION FOR CLASSES
  // This line provides the init value for Baz::i only ...
  Baz baz = {1};
  // ... but now Baz::j is guaranteed to be zero-initialised.
  double j = baz.get_j();

  // 4. IMPLICIT AGGREGATE INITIALIZATION
#ifdef RUNTIME_ERROR
  // Foo's member variables are _almost_ always (see below) undefined. Reading
  // them is UB.
  return foo.get_i();
#else
  // Unlike foo, global_foo (and it's member variables) is guaranteed to be
  // zero-initialised, because it has static storage duration (it's a global
  // var).
  return global_foo.get_i();
#endif
}
