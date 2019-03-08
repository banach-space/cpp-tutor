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
//    References:
//    * http://thbecker.net/articles/auto_and_decltype/section_01.html
//
// License: MIT
//========================================================================
#include <cassert>
#include <iostream>
#include <typeinfo>
#include <vector>

#include "cpp_tutor.h"

//========================================================================
// Helper objects/functions
//========================================================================
template <typename T, typename S>
auto multiply(T lhs, S rhs) -> decltype(lhs * rhs) {
  return lhs * rhs;
}

template <typename T, typename S>
auto fpmin(T x, S y) -> decltype(x < y ? x : y) {
  return x < y ? x : y;
}

//========================================================================
// main
//========================================================================
int main() {
  // 1. auto INSTEAD OF ITERATOR SPECIFIER
  std::vector<int> vect_1(2);
  std::vector<int> vect_2(2);

  std::cout << "POPULATE vect_1:" << std::endl;
  for (std::vector<int>::iterator it = vect_1.begin(); it != vect_1.end();
       ++it) {
    std::cin >> *it;
  }

  std::cout << "POPULATE vect_2:" << std::endl;
  for (auto it = vect_2.begin(); it != vect_2.end(); ++it) {
    std::cin >> *it;
  }

  // 2. auto INSTEAD OF TYPE SPECIFIER FOR SCALAR VARS
  int x = int();  // x is an int, initialized to 0
  assert(x == 0);

  const int &crx = x;  // crx is a const int& that refers to x
  x = 42;
  assert(crx == 42 && x == 42);

  auto something = crx;

  assert(something == 42 && crx == 42 && x == 42);
  // something is not const:
  something = 43;
  // something is not a reference to x:
  assert(something == 43 && crx == 42 && x == 42);

  const auto &some_other_thing = crx;
  assert(some_other_thing == 42 && crx == 42 && x == 42);
#ifdef COMPILATION_ERROR
  some_other_thing = 43;  // error, some_other_thing is const
#endif
  x = 43;
  assert(some_other_thing == 43 && crx == 43 && x == 43);

#ifdef COMPILATION_ERROR
  const int c = 0;
  auto &rc = c;
  rc = 44;  // error: const qualifier was not removed
#endif

  // 3. decltype (multiply uses decltype)
  auto some_var_1 = multiply(10u, 10u);
  std::cout << "Type of some_var_1: " << typeid(some_var_1).name() << std::endl;

  auto some_var_2 = multiply(10, 10);
  std::cout << "Type of some_var_2: " << typeid(some_var_2).name() << std::endl;

  auto some_var_3 = multiply(10u, 10.0f);
  std::cout << "Type of some_var_3: " << typeid(some_var_3).name() << std::endl;

  auto some_var_4 = multiply(10u, 10.0);
  std::cout << "Type of some_var_4: " << typeid(some_var_4).name() << std::endl;

  int y;
  const int cy = 42;
  const int &cry = x;

  using y_type = decltype(y);
  using cy_type = decltype(cy);
  using cry_type = decltype(cry);

  y_type var_1 = 10;
  cy_type var_2 = var_1;
  assert(var_1 == var_2);
#ifdef COMPILATION_ERROR
  // Can't modify var_2, it's a constant (decltype preserves that);
  var_2 = 10;
#endif

  cry_type var_3 = var_1;
  assert(var_1 == 10 && var_2 == 10 && var_3 == 10);
#ifdef COMPILATION_ERROR
  // Can't modify var_3, it's a constant (decltype preserves that);
  var_3 = 100;
#endif

  // Can modify var_1, it's not a constant
  var_1 = 100;
  assert(var_1 == 100 && var_2 == 10 && var_3 == 100);
}
