//========================================================================
// FILE:
//  rvalue_vs_lvalue.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    TODO
//
// License: MIT
//========================================================================
#include <utility>
#include <cassert>
#include <cpp_tutor.h>

//========================================================================
// Data structures and example functions
//========================================================================
class SomeClass {
  int a = 0xdeadbeef;
};

void foo(SomeClass &arg) {
  return;
}

void bar(SomeClass &&arg) {
  return;
}

void baz(const SomeClass &arg) {
  return;
}

template<typename T>
void g(T&& x)
{
}
 
template<typename T>
void f(T&& x)
{
    g(x);
    g(std::forward<T>(x));
}

//========================================================================
// main
//========================================================================
int main()
{
  // 1. l-value references
  SomeClass b;
  SomeClass &c = b;
  assert (&b == &c);

  int x;
  int &ref1 = x; // A
#ifdef COMPILATION_ERROR
  int &ref2 = 5; // B
#endif

  const int &ref3 = x; // C
  const int &ref4 = 5; // D

  // 2. r-value references
#ifdef COMPILATION_ERROR
  int &&ref5 = x; // E
#endif
  int &&ref6 = 5; // F

#ifdef COMPILATION_ERROR
  const int &&ref7 = x; // G
#endif
  const int &&ref8 = 5; // H

  // 3. Function calls
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

}
