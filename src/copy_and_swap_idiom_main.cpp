//==============================================================================
// FILE:
//    copy_and_swap_idiom_main.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//   Basic example of the "copy and swap" idiom:
//     * https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Copy-and-swap
//
//   This idiom helps implement a copy operation that provides strong
//   exception safety. The key idea is to ensure that the original object is
//   not modified or destroyed until a new object is successfully constructed.
//
//   The process involves two steps:
//     1. Construct a new object using RAII (this step may throw).
//     2. If the first step succeeds, use the non-throwing swap method to
//        exchange resources with the current object.
//
// License: MIT
//==============================================================================
#include <algorithm>
#include <cppt_ag.hpp>
#include <cppt_tools.hpp>
#include <cstring>
#include <iostream>

//==============================================================================
// Data types
//==============================================================================
// Custom "string" class - primarily to demonstrate the "copy and swap" idiom.
class ct_string {
  // The string itself
  char *p{};
  std::size_t length{};

 public:
  // --------------------------------------------------------------------------
  // Constructors + destructors
  // --------------------------------------------------------------------------
  ct_string() = default;
  // Ctor that takes a C string.
  ct_string(const char *s) : length(std::strlen(s)) {
    p = new char[length + 1];
    std::copy(s, s + length, p);
    p[length] = '\0';
  }
  // Destructor
  ~ct_string() { delete[] p; }

  // Idiomatic _copy ctor_.
  ct_string(const ct_string &other)
      : p{new char[other.length + 1]}, length(other.length) {
    std::copy(other.p, other.p + other.length, p);
    p[length] = '\0';
  }

  // Idiomatic copy-assignment operator - leverages the copy ctor.
  ct_string &operator=(const ct_string &other) {
    ct_string{other}.swap(*this);
    return *this;
  }
  // Idiomatic move ctor - builds on top of std::exchange:
  //  * https://en.cppreference.com/w/cpp/utility/exchange
  ct_string(ct_string &&other) noexcept
      : p{std::exchange(other.p, nullptr)},
        length{std::exchange(other.length, 0)} {}

  // --------------------------------------------------------------------------
  // Overloaded operators
  // --------------------------------------------------------------------------
  char operator[](std::size_t n) const { return p[n]; }
  char &operator[](std::size_t n) { return p[n]; }

  friend std::ostream &operator<<(std::ostream &os, const ct_string &other) {
    os << other.p << std::endl;
    return os;
  }

  // Idiomatic copy assignment operator
  ct_string &operator=(ct_string &&other) noexcept {
    ct_string{std::move(other)}.swap(*this);
    return *this;
  }

  // Bad implementation of copy assignment operator.
  ct_string &bad_copy_asign(ct_string &other) {
    char *q = new char[other.length + 1];
    // Good, old storage is only deleted _after_ new storage has been
    // allocated.
    delete[] p;
    // Bad, what if p == q!?
    p = q;
    std::copy(other.p, other.p + other.length, p);
    length = other.length;
    p[length] = '\0';
    return *this;
  }

  // --------------------------------------------------------------------------
  // Various helpers
  // --------------------------------------------------------------------------
  void swap(ct_string &other) noexcept {
    std::swap(p, other.p);
    std::swap(length, other.length);
  }

  bool empty() const { return length == 0; }
};

//==============================================================================
// main
//==============================================================================
int main(int argc, char *argv[]) {
  cppt::header(argv[0]);

  ct_string ct_string_1 = "Hello, world!\n";
  ct_string ct_string_2 = "Goodbye, world!\n";

  std::cout << "ct_string_1 before: " << std::endl;
  std::cout << ct_string_1;

  std::cout << "ct_string_1 after BAD assignment (ct_string_1 = ct_string_2): "
            << std::endl;
  ct_string_1 = ct_string_1.bad_copy_asign(ct_string_2);
  std::cout << ct_string_1;

  // This will, counter intuitively, print an empty string.
  std::cout << "ct_string_1 after BAD assignment (ct_string_1 = ct_string_1): "
            << std::endl;
  ct_string_1 = ct_string_1.bad_copy_asign(ct_string_1);
  std::cout << ct_string_1;

  std::cout << "ct_string_2 before: " << std::endl;
  std::cout << ct_string_2;

  std::cout << "ct_string_2 after GOOD assignment (ct_string_1 = ct_string_1): "
            << std::endl;
  ct_string_2 = ct_string_2;
  std::cout << ct_string_2;

  cppt::footer(argv[0]);
}
