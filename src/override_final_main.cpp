//========================================================================
// FILE:
//  override_final_main.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//  Demonstrate the usage of override and final.
//
// License: MIT
//========================================================================
#include "cpp_tutor.h"

//========================================================================
// Helper objects
//========================================================================
struct A {
  virtual void foo() {}
  virtual void fez() {}
  void bar() {}
};

#ifndef COMPILATION_ERROR
struct B : A
#else
struct B final : A
#endif
{
  void foo() override {}
  void fez() final{};
#ifdef COMPILATION_ERROR
  void foo() const override {}
  void bar() override {}
#endif
};

struct C : B {
  void foo(){}
#ifdef COMPILATION_ERROR
  void fez(){}
#endif
};

//========================================================================
// main
//========================================================================
int main() { B var_b; }
