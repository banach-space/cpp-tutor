//========================================================================
// FILE:
//  strings_1_main.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//  Code samples to help understand:
//    1. the difference between:
//      - char* and char[] (based on the result of sizeof)
//      - C-strings, std::string and std::string_view (based on the result of
//      sizeof)
//      - various ways of reversing a string (based on the representation)
//  C++17 specific code was commented out with macros. It's best to study
//  strings.cpp alongside this file.
//
// License: MIT
//========================================================================
#include <strings_object.hpp>

#include <iostream>

//========================================================================
// Utility functions
//========================================================================
// Prints the strings inside the input instance of Strings
void print_strings(Strings const &store) {
  for (size_t idx = 0; idx != store.size(); ++idx) {
    std::cout << store.at(idx) << std::endl;
  }
}

// Creates an instance of Strings on stack and prints it's contents (based on
// input args)
void create_stack_object(char *argv[], size_t argc) {
  // stack allocated object
  Strings store{argv, argc};
  print_strings(store);
}

// Creates and returns heap allocated instance of Strings (based on input args)
Strings *get_heap_object(char *argv[], size_t argc) {
  return new Strings{argv, argc};
}

//========================================================================
// main
//========================================================================
int main(int argc, char *argv[]) {
  create_stack_object(argv, argc);

  Strings *sp = get_heap_object(argv, argc);
  delete sp;

  char buffer[sizeof(Strings)];
  sp = new (buffer) Strings{argv, static_cast<size_t>(argc)};
  sp->~Strings();
}
