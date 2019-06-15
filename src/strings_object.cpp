//========================================================================
// FILE:
//    strings_object.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Implementation of the Strings class. Originally obtained from:
//        https://gitlab.com/fbb-git/cppannotations/blob/master/annotations/yo/memory/examples/strings.cc
//    The credit goes to: Frank B. Brokken (https://github.com/fbb-git)
//
//    The version guarded with MEMORY_LEAK exhibits memory leaks. Make sure you
//    understand why!
//
// License: MIT
//========================================================================
#include <strings_object.hpp>

#include <memory>
#include <string>

#include "cppt_ag.hpp"

Strings::Strings(char const *const *c_strings, size_t num_strings)
    : d_memory(static_cast<std::string *>(operator new(sizeof(std::string)))),
      d_capacity(1) {
  reserve();
  for (size_t ii = 0; ii < num_strings; ii++) {
    std::string str(c_strings[ii]);
    append(str);
  }
}

Strings::Strings()
    : d_memory(static_cast<std::string *>(operator new(sizeof(std::string)))),
      d_capacity(1) {}

Strings::~Strings() {
#ifndef MEMORY_LEAK
  operator delete(d_memory);
#else
  delete[] d_memory;
#endif
}

void Strings::reserve(size_t request) {
  while (request > d_capacity) {
    d_capacity *= 2;
  }

  reserve();
}

void Strings::reserve() {
  std::string *new_memory = static_cast<std::string *>(operator new(
      d_capacity * sizeof(std::string)));

  for (size_t idx = 0; idx != d_size; ++idx) {
    new (new_memory + idx) std::string(d_memory[idx]);
  }

  destroy();
  d_memory = new_memory;
}

void Strings::append(std::string const &next) {
  reserve(d_size + 1);
  new (d_memory + d_size) std::string{next};
  ++d_size;
}

void Strings::destroy() {
  using std::string;
  for (std::string *sp = d_memory + d_size; sp-- != d_memory;) {
    sp->~string();
  }

  operator delete(d_memory);
}
