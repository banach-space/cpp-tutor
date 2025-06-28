//========================================================================
// FILE:
//  const_vs_constepxr.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Discusses the constexpr keyword. Note that constexpr was introduced in
//    C++11, but only in C++14 the specification was relaxed enough to make
//    it practical to write constexpr functions. A very good overview can be
//    found here (CopperSpice videos by Barbara Geller and Ansel Sermersheim)
//    *  https://www.youtube.com/watch?v=Dpob2KsYLWs
//
// License: MIT
//========================================================================
#include <cppt_ag.hpp>
#include <iostream>

//========================================================================
// Helper objects
//========================================================================
//------------------------------------------------------------------------
// The following 2 functions calculate gcd (greatest common divisor) at compile
// time.
//------------------------------------------------------------------------
// C++11 implementation - only one return statement allowed, no loops, etc.
constexpr int gcd_cpp11(int a, int b) {
  return (b == 0) ? a : gcd_cpp11(b, a % b);
}

// C++14 implementation - many restrictions are relaxed, e.g. loops and auto
// are now allowed
constexpr auto gcd_cpp14(int a, int b) {
  while (b != 0) {
    auto t = b;
    b = a % b;
    a = t;
  }
  return a;
}

//------------------------------------------------------------------------
// The following functions implement the Fibonacci sequence calculation. The
// 1st implementation uses templates, and the 2nd constexpr.
//------------------------------------------------------------------------
template <unsigned n>
struct fibonacci_tmp {
  static const unsigned value =
      fibonacci_tmp<n - 1>::value + fibonacci_tmp<n - 2>::value;
};

template <>
struct fibonacci_tmp<0> {
  static const unsigned value = 0;
};

template <>
struct fibonacci_tmp<1> {
  static const unsigned value = 1;
};

constexpr unsigned fibonacci_cxp(const unsigned x) {
  return x <= 1 ? x : fibonacci_cxp(x - 1) + fibonacci_cxp(x - 2);
}

//------------------------------------------------------------------------
// Type punning through members of a union + constexpr
//
// UB in constexpr is not allowed and the compilation should fail, but only if
// `f` is used in constexpr context.
//------------------------------------------------------------------------
union U {
  float f;
  int n;
};

constexpr int f() {
  U u{1.5f};
  return u.n;  // UB (u.f is the active member)
}

//========================================================================
// main
//========================================================================
int main() {
  // 1. CONST VS COMPILE-TIME-CONST
  // Integers with const qualifiers are compile time constants. Doubles aren't
  // and require constexpr to become compile time consts.
  const int var_a =
      10;  // can be evaluated at compile time (i.e. compile time constant)
#ifdef COMPILATION_ERROR
  const double var_b =
      3.8;  // cannot be evaluated at compile time (i.e. run-time constant)
#else
  constexpr double var_b =
      3.8;  // can be evaluated at compile time (i.e. compile time constant)
#endif

  const int var_c = var_a + 5;           // compile time constant
  constexpr double var_d = var_b - 2.7;  // compile time constant

  // 2. CONST vs CONSTEXPR for pointers
  const int *ptr_e;
  constexpr int *ptr_f = nullptr;  // equivalent to int *const ptr_f (as opposed
                                   // to const int *ptr_f)

  // 3. GCD
  // Compile time calculations
  constexpr int gcd_1 = gcd_cpp11(11, 121);
  constexpr int gcd_2 = gcd_cpp14(11, 121);
  std::cout << "GCD: compile-time" << std::endl;
  std::cout << "(C++11)  gcd_cpp11(11, 121): " << gcd_1 << std::endl;
  std::cout << "(C++14)  gcd_cpp14(11, 121): " << gcd_2 << std::endl;

  // Runtime calculations
  int a = 11;
  int b = 121;
  int gcd_3 = gcd_cpp11(a, b);
  int gcd_4 = gcd_cpp14(a, b);

  std::cout << "GCD: run-time" << std::endl;
  std::cout << "(C++11)  gcd_cpp11(a, b): " << gcd_3 << std::endl;
  std::cout << "(C++14)  gcd_cpp14(a, b): " << gcd_4 << std::endl;

  // 4. FIBONACCI
  // Compile time calculations
  constexpr unsigned c = 10;
  constexpr unsigned fib_1 = fibonacci_tmp<c>::value;
  constexpr unsigned fib_2 = fibonacci_cxp(c);

  std::cout << "FIBONACCI: compile-time" << std::endl;
  std::cout << "  fibonacci_tmp<c>: " << fib_1 << std::endl;
  std::cout << "  fibonacci_cxp(c): " << fib_2 << std::endl;

  // Runtime calculations
  unsigned d = 10;
  unsigned fib_3 = fibonacci_cxp(d);

  std::cout << "FIBONACCI: run-time" << std::endl;
  std::cout << "  fibonacci_cxp(d): " << fib_3 << std::endl;

  // 5. UB in the context of constexpr is not allowed and the compilation
  // should fail (and it does!)
#ifdef COMPILATION_ERROR
  constexpr auto r = f();  // would not compile
#endif
  auto r1 = f();  // compiles, as not a constexpr context, but still UB
  std::cout << r1 << std::endl;
}
