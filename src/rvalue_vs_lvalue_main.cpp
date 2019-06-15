//========================================================================
// FILE:
//  rvalue_vs_lvalue_main.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    TODO
//
// License: MIT
//========================================================================
#include <cassert>
#include <iostream>
#include <utility>

#include <cppt_ag.hpp>

//========================================================================
// Helper functions and data structures
//========================================================================
class SomeClass {
  int a = 0xdeadbeef;
};

void foo(SomeClass &arg) { return; }

void bar(SomeClass &&arg) { return; }

void baz(const SomeClass &arg) { return; }

void overloaded(const int &arg) { std::cout << "    Pass by lvalue\n"; }
void overloaded(int &&arg) { std::cout << "    Pass by rvalue\n"; }

template <typename T>
void forwarding(T &&arg) {
  std::cout << "  Call via std::forward: " << std::endl;
  overloaded(std::forward<T>(arg));

  std::cout << "  Call via std::move: " << std::endl;
  ;
  overloaded(std::move(arg));

  std::cout << "  Call by simple passing: " << std::endl;
  overloaded(arg);
}

//========================================================================
// main
//========================================================================
int main() {
  // 1. L-VALUE REFERENCES
  SomeClass b;
  SomeClass &c = b;
  assert(&b == &c);

  int x;
  int &ref1 = x;  // A
#ifdef COMPILATION_ERROR
  int &ref2 = 5;  // B
#endif

  const int &ref3 = x;  // C
  const int &ref4 = 5;  // D

  // 2. R-VALUE REFERENCES
#ifdef COMPILATION_ERROR
  int &&ref5 = x;  // E
#endif
  int &&ref6 = 5;  // F

#ifdef COMPILATION_ERROR
  const int &&ref7 = x;  // G
#endif
  const int &&ref8 = 5;  // H

  // 3. FUNCTION CALLS
  SomeClass a;

  foo(a);
#ifdef COMPILATION_ERROR
  foo(SomeClass());
#endif

#ifdef COMPILATION_ERROR
  bar(a);
#endif
  bar(std::move(a));
  bar(SomeClass());

  baz(a);
  baz(SomeClass());

  // 4. STD::MOVE VS STD::FORWARD
  std::cout << "Initial caller passes rvalue:\n";
  forwarding(5);

  std::cout << "Initial caller passes lvalue:\n";
  int arg = 5;
  forwarding(arg);
}
