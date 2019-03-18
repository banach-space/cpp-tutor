//========================================================================
// FILE:
//    type_casting.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//   Various types of type casting:
//      * implicit and explicit (C-style)
//      * static_cast
//      * dynamic_cast
//      * reinterpret_cast
//      * const_cast
//
//    Experiment by:
//      * (un-)defining RUNTIME_ERROR
//
//    Relevant links:
//      * https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.cbclx01/implicit_conversion_sequences.htm
//      * http://www.cplusplus.com/doc/tutorial/typecasting/
//      * https://embeddedartistry.com/blog/2017/2/28/c-casting-or-oh-no-we-broke-malloc
//
// License: MIT
//========================================================================
#include <iostream>
#include <typeinfo>

//========================================================================
// Data structures
//========================================================================
//------------------------------------------------------------------------
// A and B through B's constructors
//------------------------------------------------------------------------
struct A {
  A() { std::cout << "     A()" << std::endl; }
};

struct B {
 public:
  B(A a) { std::cout << "    B(A)" << std::endl; }
};

//------------------------------------------------------------------------
// C is unrelated to A and B
//------------------------------------------------------------------------
struct C {
  C(int a, int b) : x(a), y(b) { std::cout << "    C(a, b)" << std::endl; }
  int result() { return x + y; }

 private:
  int x = 0;
  int y = 0;
};

//------------------------------------------------------------------------
// E inherits from D (note that it contains data not present in D)
//------------------------------------------------------------------------
struct D {
  D() { std::cout << "    D()" << std::endl; }
  virtual ~D() = default;
};

struct E : public D {
  E() { std::cout << "    E()" << std::endl; }
  void print() {
    std::cout << "    Hello from an instance of E!" << std::endl;
    std::cout << "    The value of some_int: " << some_int << std::endl;
  }

  int some_int = 123;
};

//========================================================================
// main
//========================================================================
int main() {
  // 1. IMPLICIT CONVERSION
  std::cout << "1. Implicit conversion:" << std::endl;

  short var_a = 2000;
  int var_b;
  var_b = var_a;

  A obj_A;
  B obj_B = obj_A;

  std::cout << "    Size and type of obj_A: " << sizeof obj_A << " "
            << typeid(obj_A).name() << std::endl;
  std::cout << "    Size and type of obj_B: " << sizeof obj_B << " "
            << typeid(obj_B).name() << std::endl;

  // 2. EXPLICIT CONVERSION
  std::cout << "2. Explicit conversion:" << std::endl;
  // 2.1 C-style casts
  std::cout << "  2.1 C-style cast:" << std::endl;

  int var_c;
  var_c = (int)var_a;  // c-like cast notation
  var_c = int(var_a);

  C* p_obj_C;
  p_obj_C = (C*)&obj_B;
#ifdef RUNTIME_ERROR
  std::cout << "    The result from p_obj_C->result(): " << p_obj_C->result()
            << std::endl;
#endif

  // 2.2 dynamic_cast<T>
  // Used for conversion of polymorphic types. Does runtime check of the types
  // and returns nullptr if the conversion is not possible.
  std::cout << "  2.2 dynamic_cast<T>:" << std::endl;

  D obj_D;
  E obj_E;
  D* p_obj_D;
  E* p_obj_E;

  p_obj_D = dynamic_cast<D*>(&obj_E);
  if (p_obj_D == nullptr) {
    std::cout << "    Null pointer on 1st type-cast" << std::endl;
  }

  p_obj_E = dynamic_cast<E*>(&obj_D);
  if (p_obj_E == nullptr) {
    std::cout << "    Null pointer on 2nd type-cast" << std::endl;
  }

  // 2.3 static_cast<T>
  // Used for conversion of non-polymorphic types. Doesn't do runtime checks -
  // won't prevent you from doing silly things.
  std::cout << "  2.3 static_cast<T>:" << std::endl;

  double d = 3.14159265;
  int i = static_cast<int>(d);
  std::cout << "    The value of i: " << i << std::endl;

  p_obj_D = dynamic_cast<D*>(&obj_E);
  if (p_obj_D == nullptr) {
    std::cout << "    Null pointer on 1st type-cast" << std::endl;
  }

  // Although this is possible (and the compiler won't complain) ...
  p_obj_E = static_cast<E*>(&obj_D);
  if (p_obj_E == nullptr) {
    std::cout << "    Null pointer on 3rd type-cast" << std::endl;
  } else {
#ifdef RUNTIME_ERROR
    // ... p_obj_E points to an instance of D and E::print() accesses a
    // variable that's not present in D (the call itself will probably work
    // fine).
    p_obj_E->print();
#endif
  }

  // 2.4 reinterpret_cast<T>
  // Allows any pointer to be converted into any other pointer type. Also allows
  // any integral type to be converted into any pointer type and vice versa. No
  // runtime checks are performed.
  std::cout << "  2.4 reinterpret_cast<T>:" << std::endl;

  A* p_obj_A = &obj_A;
  p_obj_E = reinterpret_cast<E*>(p_obj_A);  // Bad, bad, bad!
  if (p_obj_E == nullptr) {
    std::cout << "    Null pointer on 4th type-cast" << std::endl;
  }

  int var_i = 123;
  p_obj_A = reinterpret_cast<A*>(var_i);  // Bad, bad, bad!
  if (p_obj_A == nullptr) {
    std::cout << "    Null pointer on 5th type-cast" << std::endl;
  }

  // 2.5 const_cast<T>
  // Used to remove the const, volatile, and __unaligned attributes.
  std::cout << "  2.5 const_cast<T>:" << std::endl;

  // ii is not declared const so it can be modified
  int ii = 3;
  // rci is a ref to a const int (but i is not const), so it cannot be used to
  // modify ii directly
  const int& rci = i;
  // OK: modifies ii through rci with a const_cast
  const_cast<int&>(rci) = 4;
}
