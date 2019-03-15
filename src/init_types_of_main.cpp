//========================================================================
// FILE:
//    init_types_of_main.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Goes through various types of initialization:
//      * direct initialization (also most vexing parse)
//      * copy initialization
//      * value initialization (since C++03)
//      * list initialization (since C++11)
//
//    Experiment by:
//      * (un-)defining RUNTIME_ERROR
//      * (un-)defining COMPILATION_ERROR
//
//    Relevant links:
//      * https://en.cppreference.com/w/cpp/language/direct_initialization
//      * https://en.cppreference.com/w/cpp/language/copy_initialization
//      * https://en.cppreference.com/w/cpp/language/value_initialization
//      * https://en.cppreference.com/w/cpp/language/list_initialization
//
// License: MIT
//========================================================================
#include "cpp_tutor.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <string>

//========================================================================
// Helper objects
//========================================================================
struct Foo {
  Foo(int arg_i, double arg_j) : i(arg_i), j(arg_j) {}
  int get_i() { return i; }
  double get_j() { return j; }

  int i;
  double j;
};

struct Bar {
  // Cannot be used for copy initialization.
  explicit Bar(int arg_i) : i(arg_i) {
    std::cout << "   Bar(int)" << std::endl;
  }
#ifndef COMPILATION_ERROR
  // Can be used for copy initialization.
  Bar(double arg_j) : j(arg_j) {
    std::cout << "   Bar(double)" << std::endl;
  }
#endif
  Bar(Foo f) {
    std::cout << "   Bar(Foo)" << std::endl;
  }

  int i;
  double j;
};

//-----------------------------------------------------------------------------
// Classes for exploiting value initialisation
//-----------------------------------------------------------------------------
// Value initialization either calls the user-provided constructor or does
// zero-initialization.
struct Baz_without_ctor {
  // No user provided ctor. Value initialization by zero-initialization.
  int i;
};

Baz_without_ctor get_baz_without_ctor() {
  return Baz_without_ctor();     // Value initialisation - i zero-initialised
}

struct Baz_with_ctor {
  // User provided default ctor - value initialization through this ctor
  Baz_with_ctor() {};
  int i;
};

Baz_with_ctor get_baz_with_ctor() {
  return Baz_with_ctor();     // Value initialisation - i is uninitialised
}

struct Baz_with_default_ctor {
  // No user provided ctor. Value initialization by zero-initialization.
  Baz_with_default_ctor() = default;
  int i;
};

Baz_with_default_ctor get_baz_with_default_ctor() {
  return Baz_with_default_ctor();     // Value initialisation - i is zero-initialised
}

struct Baz_with_default_ctor_ool {
  // Out-of-line constructor counts as user provided constructor. This _will_
  // be used for value initialization.
  // EXPLANATION: This constructor could be defined in another TU (or a header
  // file), so the compiler must assume that it's user provided. This is
  // despite the fact that it could be marked with =default at the point of
  // definition (and it is indeed).
  Baz_with_default_ctor_ool();
  int i;
};

// As discussed at the point of declaring this constructor, the compiler
// regards this as user-provided despite "=default" being used.
Baz_with_default_ctor_ool::Baz_with_default_ctor_ool() = default;

Baz_with_default_ctor_ool get_baz_with_default_ctor_ool() {
  return Baz_with_default_ctor_ool();     // Value initialisation - i is uninitialised
}

//-----------------------------------------------------------------------------
// Classes for exploiting {}
//-----------------------------------------------------------------------------
template <typename T>
struct FooBar {
  FooBar(); 
  FooBar(std::initializer_list<T> list) {}
};

//========================================================================
// main
//========================================================================
int main() {
  // 1. DIRECT INITIALIZATION
  // (arguments in parenthesis --> direct initialization)
  Foo foo(1, 3.14);
  int var_i(13);
  auto* foo_ptr = new Foo(1410, 3.14);

  // 2. DIRECT VS COPY INITIALIZATION
  // Direct initialisation
  Bar bar_1(10);
  // Copy initialization - the explicit constructor cannot be used here. 
  Bar bar_2 = 20;

  // 3. (HOWEVER,) MOST VEXING PARSE
  // This is a function declaration - not a constructor call! Yes, C++ is
  // annoying.
  Bar bar_3(Foo());
#ifdef COMPILATION_ERROR
  // ... since bar_3 is _not_ in instance of Bar, this won't compile.
  Bar *bar_ptr = &bar_3;
#endif

  // 3. VALUE INITIALISATION
  // (Either calls the user-provided constructor or does zero-initialization).
  int var_j = int();        // var_j is initialised to 0

  auto baz_1 = get_baz_with_ctor();
#ifdef RUNTIME_ERROR
  assert(baz_1.i == 0);     // baz_1.i is uninitialized - UB
#endif

  auto baz_2 = get_baz_without_ctor();
  assert(baz_2.i == 0);     // baz_2.i is initialized to 0

  auto baz_3 = get_baz_with_default_ctor();
  assert(baz_3.i == 0);     // baz_3.i is initialized to 0

  auto baz_4 = get_baz_with_default_ctor_ool();
#ifdef RUNTIME_ERROR
  assert(baz_4.i == 0);     // baz_4.i is uninitialized - UB
#endif

  // 4. LIST INITIALIZATION
  // (from C++11 onwards)
  // 4.1 Direct list-initialization
  Foo foo_1{1, 3.14};

  // 4.2 Copy list-initialization
  Foo foo_2 = {1, 3.14};

  // CLEANUP
  delete foo_ptr;
}
