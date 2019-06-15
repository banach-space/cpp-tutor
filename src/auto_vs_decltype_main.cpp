//========================================================================
// FILE:
//  auto_vs_decltype.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Examples to demonstrate auto and decltype. Note that type deduction for
//    auto works very similar to type deduction for functions template. The
//    only notable difference is std::initializer_list<>. As per § 14.8.2.5/5
//    of the C++11 standard, std::initliazer_list<> is a non-deduced context
//    for a template argument. However with auto, § 7.1.6.4/6 has explicit
//    support for std::initializer_list<>
//
//    Experiment by:
//      * (un-)defining COMPILATION_ERROR
//      * (un-)defining DANGLING_REF_OR_PTR
//    and checking the behaviour before and after.
//
//    References:
//    * http://thbecker.net/articles/auto_and_decltype/section_01.html
//
// License: MIT
//========================================================================
#include <cassert>
#include <iostream>
#include <type_traits>
#include <typeinfo>
#include <vector>

#include "cppt_ag.hpp"

//========================================================================
// Helper objects/functions
//========================================================================
// AFAIK the result of multiplication is never an lvalue and hence decltype
// never gives SomeType&, but SomeType instead.
template <typename T, typename S>
auto multiply(T lhs, S rhs) -> decltype(lhs * rhs) {
  return lhs * rhs;
}

// The return value of the tenary operator "?" might be an lvalue (e.g. when
// both arguments are l-values) and if expr is an lvalue, then decltype(expr)
// is SomeType&. Therefore, without std::remove_reference the following is
// potentially returning a ref to a local variable. This example was originally
// discussed here:
//  * http://thbecker.net/articles/auto_and_decltype/section_08.html
template <typename T, typename S>
auto min_func(T x, S y) ->
#ifndef DANGLING_REF_OR_PTR
    typename std::remove_reference<decltype(x < y ? x : y)>::type {
#else
    decltype(x < y ? x : y) {
#endif
  return x < y ? x : y;
}

//========================================================================
// main
//========================================================================
int main() {
  // 1. AUTO INSTEAD OF ITERATOR SPECIFIER
  std::vector<int> vect_1(2);
  std::vector<int> vect_2(2);

  // 1.1 Old style ...
  std::cout << "POPULATE vect_1:" << std::endl;
  for (std::vector<int>::iterator it = vect_1.begin(); it != vect_1.end();
       ++it) {
    std::cin >> *it;
  }

  // 1.2 ... vs with auto
  std::cout << "POPULATE vect_2:" << std::endl;
  for (auto it = vect_2.begin(); it != vect_2.end(); ++it) {
    std::cin >> *it;
  }

  // 2. AUTO INSTEAD OF TYPE SPECIFIER FOR SCALAR VARS
  int x = 42;
  const int &crx = x;
  assert(crx == x);

  // 2.1  Auto without ref - reference and top level const specifier are
  // _ignored_
  auto something =
      crx;  // something is an int, intialised with crx, that is not const
  assert(something == x && crx == x);
  something = 43;
  assert(something == 43 && crx == 42 && x == 42);

  // 2.2 Auto with ref - reference and top level const specifier are _preserved_
  const int y = 13;
  auto &some_other_thing = y;
  assert(some_other_thing == y);
#ifdef COMPILATION_ERROR
  some_other_thing = 44;
#endif

  // 2.3 Auto with ref and const - reference and top level const specifier are
  // _preserved_
  const auto &some_other_other_thing =
      x;  // some_other_thing is a const int&, intialised with x
  assert(some_other_other_thing == x && crx == x);
#ifdef COMPILATION_ERROR
  some_other_other_thing = 43;
#endif
  x = 43;
  assert(some_other_other_thing == 43 && crx == 43 && x == 43);

  // 3. DECLTYPE (MULTIPLY USES DECLTYPE)
  // 3.1 Function return type using decltype
  auto some_var_1 = multiply(10u, 10u);
  std::cout << "Type of some_var_1: " << typeid(some_var_1).name() << std::endl;

  auto some_var_2 = multiply(10, 10);
  std::cout << "Type of some_var_2: " << typeid(some_var_2).name() << std::endl;

  auto some_var_3 = multiply(10u, 10.0f);
  std::cout << "Type of some_var_3: " << typeid(some_var_3).name() << std::endl;

  auto some_var_4 = multiply(10u, 10.0);
  std::cout << "Type of some_var_4: " << typeid(some_var_4).name() << std::endl;

  // 3.2 Types aliases using decltype
  int z = 10;
  const int cz = 42;
  const int &crz = x;

  using z_type = decltype(z);
  using cz_type = decltype(cz);
  using crz_type = decltype(crz);

  z_type var_1 = 10;
  cz_type var_2 = var_1;
  assert(var_1 == var_2);
#ifdef COMPILATION_ERROR
  // Can't modify var_2, it's a constant (decltype preserves that)
  var_2 = 10;
#endif

  crz_type var_3 = var_1;
  assert(var_1 == 10 && var_2 == 10 && var_3 == 10);
#ifdef COMPILATION_ERROR
  // Can't modify var_3, it's a constant (decltype preserves that)
  var_3 = 100;
#endif

  // Can modify var_1, it's not a constant
  var_1 = 100;
  assert(var_1 == 100 && var_2 == 10 && var_3 == 100);

  // 3.3 Dangling ref when using decltype for functions
  // Always safe
  std::cout << multiply(z, crz) << std::endl;
  // Check the implementation for comments, but this might be returning a ref
  // to a local variable (both z and crz are l-values).
  std::cout << min_func(z, crz) << std::endl;
}
