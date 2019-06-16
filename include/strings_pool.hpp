//==============================================================================
// FILE:
//    strings_pool.hpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//
// License: MIT
//==============================================================================
#ifndef _STRINGS_POOL_
#define _STRINGS_POOL_
#include <string>

//==============================================================================
// StringsPool class
//
// A basic memory manager/container for std::string. It stores strings inside a
// preallocated memory pool using `placement new`. It is assumes that only
// small strings are stored [1], so that no dynamic memory allocation within
// string's constructor is used.
//
// [1] Strings that fit into the static internal buffer. See also SSO.
//==============================================================================
class StringsPool {
 public:
  StringsPool();
  StringsPool(char const *const *c_strings, size_t n);
  ~StringsPool();

  // Since a non-default destructor was declared, the following special
  // functions need to be either defined or deleted. Otherwise they will be
  // auto-generated.
  StringsPool(const StringsPool &) = delete;
  StringsPool(StringsPool &&) = delete;
  StringsPool operator=(StringsPool) = delete;
  StringsPool operator=(StringsPool &&) = delete;

  // Get the string at index `idx`
  std::string const &at(size_t idx) const { return memory_[idx]; }
  // Reserve space for `request` strings
  void reserve(size_t request);
  // Add `new_str` to the memory pool
  void append(std::string const &new_str);
  // Get the number of strings currently stored
  size_t size() const { return size_; }

 private:
  // Allocates a new memory for capacity_ strings. All currently stored strings
  // are copied into the new memory pool. Old memory pool is deallocated.
  void reserve();
  // Destroys all strings stored in memory_ and frees the memory.
  void destroy();

  // Number of strings currently stored
  size_t size_ = 0;
  // Number of strings that can be stored inside memory_
  size_t capacity_ = 0;
  // The raw memory pool used for storing strings
  std::string *memory_ = nullptr;
};

#endif
