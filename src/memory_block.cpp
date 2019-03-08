//========================================================================
// FILE:
//  memory_block.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    The implementation of MemoryBlock
//
// License: MIT
//========================================================================
#include <memory_block.hpp>

MemoryBlock::MemoryBlock(size_t length)
    : m_length(length), m_data(new int[length]) {
  std::cout << "In MemoryBlock(size_t). length = " << m_length << "."
            << std::endl;
}

MemoryBlock::~MemoryBlock() {
  std::cout << "In ~MemoryBlock(). length = " << m_length << ".";

  if (m_data != nullptr) {
    std::cout << " Deleting resource.";
    // Delete the resource.
    delete[] m_data;
  }

  std::cout << std::endl;
}

MemoryBlock::MemoryBlock(const MemoryBlock &other)
    : m_length(other.m_length), m_data(new int[other.m_length]) {
  std::cout << "In MemoryBlock(const MemoryBlock&). length = " << other.m_length
            << ". Copying resource." << std::endl;

  std::copy(other.m_data, other.m_data + m_length, m_data);
}

MemoryBlock &MemoryBlock::operator=(const MemoryBlock &other) {
  std::cout << "In operator=(const MemoryBlock&). length = " << other.m_length
            << ". Copying resource." << std::endl;

  if (this != &other) {
    // Free the existing resource.
    delete[] m_data;

    m_length = other.m_length;
    m_data = new int[m_length];
    std::copy(other.m_data, other.m_data + m_length, m_data);
  }
  return *this;
}

size_t MemoryBlock::length() const { return m_length; }

MemoryBlock::MemoryBlock(MemoryBlock &&other) noexcept
    : m_length(0), m_data(nullptr) {
  std::cout << "In MemoryBlock(MemoryBlock&&). length = " << other.m_length
            << ". Moving resource." << std::endl;

  // Copy the data pointer and its length from the
  // source object.
  m_data = other.m_data;
  m_length = other.m_length;

  // Release the data pointer from the source object so that
  // the destructor does not free the memory multiple times.
  other.m_data = nullptr;
  other.m_length = 0;
}

MemoryBlock &MemoryBlock::operator=(MemoryBlock &&other) noexcept {
  std::cout << "In operator=(MemoryBlock&&). length = " << other.m_length << "."
            << std::endl;

  if (this != &other) {
    // Free the existing resource.
    delete[] m_data;

    // Copy the data pointer and its length from the
    // source object.
    m_data = other.m_data;
    m_length = other.m_length;

    // Release the data pointer from the source object so that
    // the destructor does not free the memory multiple times.
    other.m_data = nullptr;
    other.m_length = 0;
  }
  return *this;
}
