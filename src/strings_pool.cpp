//==============================================================================
// FILE:
//    strings_pool.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Implementation of the StringsPool class.
//
// License: MIT
//==============================================================================
#include <strings_pool.hpp>
#include <cppt_ag.hpp>

#include <memory>
#include <string>

StringsPool::StringsPool(char const *const *c_strings, size_t num_strings)
    : capacity_(1),
      memory_(static_cast<std::string *>(operator new(sizeof(std::string)))) {
  reserve();
  for (size_t ii = 0; ii < num_strings; ii++) {
    std::string str(c_strings[ii]);
    append(str);
  }
}

StringsPool::StringsPool()
    : capacity_(1),
      memory_(static_cast<std::string *>(operator new(sizeof(std::string)))) {}

StringsPool::~StringsPool() {
#ifndef MEMORY_LEAK
  operator delete(memory_);
#else
  delete[] memory_;
#endif
}

void StringsPool::reserve(size_t request) {
  while (request > capacity_) {
    capacity_ *= 2;
  }

  reserve();
}

void StringsPool::reserve() {
  std::string *new_memory =
      static_cast<std::string *>(operator new(capacity_ * sizeof(std::string)));

  for (size_t idx = 0; idx != size_; ++idx) {
    new (new_memory + idx) std::string(memory_[idx]);
  }

  destroy();
  memory_ = new_memory;
}

void StringsPool::append(std::string const &new_str) {
  reserve(size_ + 1);
  new (memory_ + size_) std::string{new_str};
  ++size_;
}

void StringsPool::destroy() {
  using std::string;
  for (std::string *sp = memory_ + size_; sp-- != memory_;) {
    sp->~string();
  }

  operator delete(memory_);
}
