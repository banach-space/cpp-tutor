//========================================================================
// FILE:
//  memory_block.hpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//  Illustrates a basic memory manager with a move-constructor and move-assign
//  operator. As per:
//    https://stackoverflow.com/questions/18085383/c11-rvalue-reference-calling-copy-constructor-too
//  move-constructor and move-assign-operator need to be marked as noexcept.
//  It's a good exercise to remove noexcept and re-run this code (i.e. the
//  move special functions).
//
//  Originally published here:
//    https://docs.microsoft.com/en-us/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=vs-2017
//
// License: MIT
//========================================================================
#include <cppt_tools.hpp>

#include <algorithm>
#include <iostream>

class MemoryBlock {
 public:
  // Simple constructor that initializes the resource.
  explicit MemoryBlock(size_t length);
  // Copy constructor.
  MemoryBlock(const MemoryBlock &other);
  // Copy assignment operator.
  MemoryBlock &operator=(const MemoryBlock &other);
  // Move constructor.
  MemoryBlock(MemoryBlock &&other) noexcept;
  // Move assignment operator.
  MemoryBlock &operator=(MemoryBlock &&other) noexcept;
  // Destructor.
  ~MemoryBlock() ;

  // Retrieves the length of the data resource.
  size_t length() const;

 private:
  // The length of the resource.
  size_t m_length;
  // The resource.
  int *m_data;
};
