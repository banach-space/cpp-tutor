//========================================================================
// FILE:
//    deep_vs_shallow_main.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Shows the difference between deep and shallow copy. Try to guess what's
//    going to be printed. Then study compare that against the actual output
//    and make sure that you understand any discrepancies.
//
// License: MIT
//========================================================================
#include <iostream>

#include <deep_vs_shallow.hpp>
#include "cpp_tutor.h"

int main() {
  // 1. SHALLOW COPY
  Shallow obj_a;
  for (unsigned ii = 0; ii < 10; ii++) {
    obj_a.add(ii);
  }

  Shallow *obj_b = new Shallow(obj_a);
  obj_b->getElemAt(0) = 100;

  for (unsigned ii = 0; ii < 10; ii++) {
    std::cout << obj_a.getElemAt(ii) << " ";
  }
  std::cout << std::endl;

  // 2. DEEP COPY
  Deep obj_c;
  for (unsigned ii = 0; ii < 10; ii++) {
    obj_c.add(ii);
  }

  Deep *obj_d = new Deep(obj_c);
  obj_d->getElemAt(0) = 100;

  for (unsigned ii = 0; ii < 10; ii++) {
    std::cout << obj_c.getElemAt(ii) << " ";
  }
  std::cout << std::endl;

  // FREE MEMORY
  delete obj_b;
  delete obj_d;

  return 0;
}
