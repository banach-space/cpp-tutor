//========================================================================
// FILE:
//  override_final_main.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Demonstrate the usage of override and final. This example doesn't print
//    anything. Instead study the compiler errors when COMPILATION_ERROR is
//    defined (otherwise this example builds cleanly).
//
//    Experiment by:
//      * (un-)defining COMPILATION_ERROR
//    and checking the compiler errors before and after.
//
// License: MIT
//========================================================================
#include "cppt_ag.hpp"

//========================================================================
// Helper objects
//========================================================================
struct A {
  virtual void foo(int a) {}
  virtual void fez() {}
  void bar() {}
};

#ifndef COMPILATION_ERROR
struct B : A
#else
struct B final : A
#endif
{
  void fez() final{};
#ifndef COMPILATION_ERROR
  void foo(int a) override {}
#else
  void foo(float a) override {}
  void bar() override {}
#endif
};

struct C : B {
  void foo() {}
#ifdef COMPILATION_ERROR
  void fez() {}
#endif
};

//========================================================================
// main
//========================================================================
int main() { B var_b; }
