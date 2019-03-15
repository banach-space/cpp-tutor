//========================================================================
// FILE:
//    init_brace_elision_main.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Demonstrates how brace elision in aggregate initialisation works.
//    Although it's an interesting syntactic sugar, it's consider to have
//    negative impact on code clarity and is best avoided.
//
//    Relevant links:
//      * https://en.cppreference.com/w/cpp/language/aggregate_initialization
//
// License: MIT
//========================================================================

//========================================================================
// Helper objects
//========================================================================
struct Foo {
    int a;
    struct Bar {
        int i;
        int j;
        int k[3];
    } b;
};

//========================================================================
// main
//========================================================================
int main() {
  // Aggregate initialisation
  Foo foo_1 = {1, {2, 3, {4, 5, 6}}};
  // Aggregate initialisation with brace elision (result same as above)
  Foo foo_2 = {1, 2, 3, 4, 5, 6};

  // Aggregate initialisation (without the assignment operator)
  Foo foo_3{1, {2, 3, {4, 5, 6}}};

  // Aggregate initialisation (without the assignment operator) with brace
  // elision (result same as above).
  // NOTE: Oddly, the following wasn't valid until C++14, but both GCC and
  // Clang allow it even in C++11 mode.
  Foo foo_4{1, 2, 3, 4, 5, 6};
}
