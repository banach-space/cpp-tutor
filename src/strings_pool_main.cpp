//==============================================================================
// FILE:
//    strings_pool_main.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Content:
//      - A custom memory pool using placement new: StringsPool
//
//    Experiment by:
//      * running the execuatable with an arbitrary number of (relatively)
//      short arguments
//      * (un-)defining MEMORY_LEAK, re-building and re-running
//
//    It's best to study strings_pool.cpp alongside this file.
//
// License: MIT
//==============================================================================
#include <strings_pool.hpp>
#include <cppt_tools.hpp>

#include <iostream>

//==============================================================================
// Utility functions
//==============================================================================
// Prints the strings inside the input instance of StringsPool
void print_strings(StringsPool const &store) {
  for (size_t idx = 0; idx != store.size(); ++idx) {
    std::cout << store.at(idx) << std::endl;
  }
}

// Creates an instance of StringsPool on stack and prints it's contents (based
// on input args)
void create_stack_object(char *argv[], size_t argc) {
  // stack allocated object
  StringsPool store{argv, argc};
  print_strings(store);
}

// Creates and returns heap allocated instance of StringsPool (based on input
// args)
StringsPool *get_heap_object(char *argv[], size_t argc) {
  return new StringsPool{argv, argc};
}

//==============================================================================
// main
//==============================================================================
int main(int argc, char *argv[]) {
  cppt::header(argv[0]);

  create_stack_object(argv, argc);

  StringsPool *sp = get_heap_object(argv, argc);
  delete sp;

  char buffer[sizeof(StringsPool)];
  sp = new (buffer) StringsPool{argv, static_cast<size_t>(argc)};
  sp->~StringsPool();

  cppt::footer(argv[0]);
}
