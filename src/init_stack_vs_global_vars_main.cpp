//========================================================================
// FILE:
//    init_stack_vs_global_vars_main.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Demonstrates what happens if there's no initialization for plain ints,
//    and what's the difference between stack (local) and non-stack (global and
//    static) variables in this context.
//
//    Variables with static storage duration (global vars and vars decorated
//    with the `static` keyword) are guaranteed to be zero-initialised. Local
//    variables often appear to be zero-initialized, but that's just a
//    by-product of where such variables are stored (the runtime stack) and the
//    state of the runtime stack (usually zero-ed at the start of a program).
//
//    Note that although the behaviour presented here is deterministic, it
//    depends on the runtime libraries used. Hence it might change when using
//    different compiler versions. The compilers that I tested this file with
//    are listed in README.md, and the compiler flags can be found in
//    CMakeLists.txt.
//
//    Experiment by:
//      * (un-)defining RUNTIME_ERROR
//    and re-running this file with and without Valgrind (the behaviour won't
//    change, but there will be much more output with Valgrind).
//
//    Relevant links:
//      * https://en.cppreference.com/w/cpp/language/storage_duration
//
// License: MIT
//========================================================================
#include "cpp_tutor.h"
#include <cassert>

//========================================================================
// Helper objects
//========================================================================
// fez will fill the runtime stack with some numbers.
void fez() {
    int a[5] = {1, 2, 3, 4, 5};
}

// bar and baz are deliberately identical. They both exhibit UB because local_i
// is uninitialised. However, if the random value on the stack used for storing
// local_i is indeed 0, then the assert will indeed return true.
void bar() {
  int local_i;
  assert((local_i == 0));
}

void baz() {
  int local_i;
  assert(local_i == 0);
}

// vaz is almost identical to bar and baz, but now local_i has static storage
// duration and hence is guaranteed to be zero-initialized. No UB here.
void vaz() {
  static int local_i;
  assert(local_i == 0);
}

// Static initialisation - this variable is guaranteed to be initialised to 0
static int global_i;

//========================================================================
// main
//========================================================================
int main() {
  int local_i;
  int local_j;

  // This assert is always true
  assert(global_i == 0);
#ifdef RUNTIME_ERROR
  // This following line/assert exhibits UB as local_i is uninitialized:
  //  * compilers will very likely complain (may require -Wall)
  //  * Valgrind will identify this as an error
  //  * assert will probably pass as the stack (and local_i is a stack
  //  variable) is fairly clean at this point
  assert(local_i == 0);
#endif

#ifdef RUNTIME_ERROR
  // Same as above - calling bar yields UB:
  //  * compilers will very likely complain (may require -Wall)
  //  * Valgrind will identify this as an error
  //  * assert in bar will probably pass as the stack (and local_i in bar is a
  //  stack variable) is fairly clean at this point
  bar();
#endif

  // Calling fez `pollutes` the stack with it's local vars.
  fez();

#ifdef RUNTIME_ERROR
  // Similar to the previous two UBs:
  //  * compilers will very likely complain (may require -Wall)
  //  * Valgrind will identify this as an error
  //  * assert will very likely fail as the stack memory used for local_i in
  //  baz has been polluted by local variables in fez (no longer used, but
  //  there's no requirement to `zero` that memory)
  baz();
#endif

  // No UB here.
  vaz();

  return 0;
}
