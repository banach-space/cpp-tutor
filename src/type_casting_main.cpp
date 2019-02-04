//========================================================================
// FILE:
//  type_casting.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    TODO
//
// License: MIT
//========================================================================
#include <iostream>

//========================================================================
// Data structures
//========================================================================
struct A {};
struct B { public: B (A a) {} };

struct C {
  C (int a, int b) { x=a; y=b; }
  int result() { return x+y;}
 private:
  int x,y;
};

struct D {
  virtual ~D() = default;
};
struct E : public D {};

int main() {
  // 1. Implicit conversion
  short a = 2000;
  int b;
  b = a;

  A obj_A;
  B obj_B = obj_A;

  // 2. Explicit conversion
  int c;
  c = (int) a;    // c-like cast notation
  c = int (a);

  C * p_obj_C;
  p_obj_C = (C*) &obj_B;
  std::cout << p_obj_C->result() << std::endl;

  // 3. dynamic_cast
  D obj_D;
  E obj_E;
  D* p_obj_D;
  E* p_obj_E;

  p_obj_D = dynamic_cast<D*>(&obj_E);
  if (p_obj_D == nullptr) std::cout << "Null pointer on first type-cast" << std::endl;

  p_obj_E = dynamic_cast<E*>(&obj_D);
  if (p_obj_E == nullptr) std::cout << "Null pointer on second type-cast" << std::endl;


  // 4. static_cast
  double d=3.14159265;
  int i = static_cast<int>(d);

  p_obj_E = static_cast<E*>(&obj_D);
  if (p_obj_E == nullptr) std::cout << "Null pointer on third type-cast" << std::endl;

  // 5. reinterpret_cast
  A *p_obj_A = &obj_A;
  B *p_obj_B = reinterpret_cast<B*>(p_obj_A);
  if (p_obj_B == nullptr) std::cout << "Null pointer on fourth type-cast" << std::endl;

  // 6. const_cast
  int ii = 3;                 // i is not declared const
  const int& rci = ii; 
  const_cast<int&>(rci) = 4; // OK: modifies i
}
