//========================================================================
// FILE:
//    deep_vs_shallow.hpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Declaration of Shallow and Deep used in deep_vs_shallow_main.cpp. Both
//    classes implement a tiny/dummy buffer of ints, the only difference
//    between the two being:
//      - Shallow implements a copy constructor that does shallow copying
//      - Deep implements a copy constructor that does deep copying
//
// License: MIT
//========================================================================
#include <string>

class Shallow {
 public:
  explicit Shallow();
  Shallow(const Shallow &rhs);
  ~Shallow();
  void add(int elem);
  int &getElemAt(unsigned idx);

 private:
  int *m_data = nullptr;
  constexpr static size_t m_capacity = 10;
  size_t m_num_elements = 0;
};

class Deep {
 public:
  explicit Deep();
  Deep(const Deep &rhs);
  ~Deep();
  void add(int elem);
  int &getElemAt(unsigned idx);

 private:
  int *m_data = nullptr;
  constexpr static size_t m_capacity = 10;
  size_t m_num_elements = 0;
};
