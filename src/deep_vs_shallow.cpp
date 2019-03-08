//========================================================================
// FILE:
//    deep_vs_shallow.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Implementation of Deep and Shallow
//
// License: MIT
//========================================================================
#include <deep_vs_shallow.hpp>
#include <iostream>

Shallow::Shallow() { m_data = new int[m_capacity]; }

Shallow::Shallow(const Shallow& rhs) { m_data = rhs.m_data; }

Shallow::~Shallow() {
  if (m_data != nullptr) {
    delete[] m_data;
    m_data = nullptr;
  }
}

void Shallow::add(int elem) {
  if (m_num_elements >= m_capacity) {
    std::cout << "Full buffer, exiting." << std::endl;
    return;
  }

  m_data[m_num_elements] = elem;
  m_num_elements++;
}

int& Shallow::getElemAt(unsigned idx) { return m_data[idx]; }

Deep::Deep() { m_data = new int[m_capacity](); }

Deep::Deep(const Deep& rhs) {
  m_data = new int[m_capacity];
  for (size_t ii = 0; ii < m_capacity; ii++) {
    m_data[ii] = rhs.m_data[ii];
  }
}

Deep::~Deep() { delete[] m_data; }

void Deep::add(int elem) {
  if (m_num_elements >= m_capacity) {
    std::cout << "Full buffer, exiting." << std::endl;
    return;
  }

  m_data[m_num_elements] = elem;
  m_num_elements++;
}

int& Deep::getElemAt(unsigned idx) { return m_data[idx]; }
