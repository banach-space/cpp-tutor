//========================================================================
// FILE:
//  static_assert_main.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Demonstrates static_assert and type traits.
//
//    Experiment by:
//      * (un-)defining COMPILATION_ERROR
//    and checking the behaviour before and after.
//
//
// License: MIT
//========================================================================
#include <iostream>
#include <type_traits>

#include "cpp_tutor.h"

//========================================================================
// Helper objects/functions
//========================================================================
template <typename T, std::size_t N>
class A {
  static_assert(N > 10, "Size is too small");

  T _points[N];
};

template <typename T1, typename T2>
auto add(T1 t1, T2 t2) -> decltype(t1 + t2) {
  static_assert(std::is_integral<T1>::value, "Type T1 must be integral");
  static_assert(std::is_integral<T2>::value, "Type T2 must be integral");

  return t1 + t2;
}

//========================================================================
// main
//========================================================================
int main() {
  // 1. ASSERT FOR COMPILE-TIME VARS
  constexpr int x = 0;
  constexpr int y = 1;
  static_assert(x != y, "x == y");
#ifdef COMPILATION_ERROR
  static_assert(x == y, "x != y");
#endif

  // 2. STATIC ASSERT TOGETHER WITH TYPE TRAITS
  static_assert(std::is_integral<int>() == true);
  static_assert(std::is_integral<char>() == true);
  static_assert(std::is_integral<double>() == false);
  struct S {};
  static_assert(std::is_integral<S>() == false);

  static_assert(
      std::is_same<std::conditional<true, int, double>::type, int>::value);

  // 3. STATIC ASSERT IN CUSTOM TEMPLATES
  A<int, 16> a1;
#ifdef COMPILATION_ERROR
  A<double, 2> a2;
#endif

  std::cout << add(1, 3) << std::endl;
#ifdef COMPILATION_ERROR
  std::cout << add(1, 3.14) << std::endl;
  std::cout << add("one", 2) << std::endl;
#endif
}
