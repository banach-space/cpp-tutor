//========================================================================
// FILE:
//    delete_vs_default_main.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Demonstrates the =delete and =default mechanisms.
//
//    Experiment by:
//      * (un-)defining COMPILATION_ERROR
//    and checking the compiler errors before and after.
//
//
// License: MIT
//========================================================================
#include <cassert>
#include <iostream>
#include <string>
#include <utility>

#include "cpp_tutor.h"

//========================================================================
// Helper objects/functions
//========================================================================
class Shape {
 public:
  // Default constructor
  explicit Shape(std::string name) : type(std::move(name)) {}

  // Default copyt operations
  Shape(const Shape&) = default;
  Shape& operator=(const Shape&) = default;
  ~Shape() = default;

  // No move operations
  Shape(Shape&&) = delete;
  Shape& operator=(Shape&&) = delete;

  std::string type;
};

inline bool operator==(const Shape& lhs, const Shape& rhs) {
  return (lhs.type == rhs.type);
}

inline bool operator!=(const Shape& lhs, const Shape& rhs) {
  return !(lhs == rhs);
}

//========================================================================
// main
//========================================================================
int main() {
  Shape square("square");
  Shape triangle("triangle");
  // Verify that square and triangle are indeed two different objects
  assert(square != triangle);

  // Default'ed copy intialisation
  Shape square_2(square);
  assert(square == square_2);

  // Default'ed copy assignment
  triangle = square;
  assert(square == triangle);

#ifdef COMPILATION_ERROR
  // Deleted move construction and assignment
  Shape square_3 = std::move(square_2);
  Shape square_4(std::move(square_2));
#endif
}
