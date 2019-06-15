//========================================================================
// FILE:
//    type_casting_main.cpp
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
//    The examples presented here demonstrate both _good_ and _bad_ casting
//    (always clearly commented). It goes without saying that _bad_ casting
//    should be avoided - only because it can be done doesn't mean that it
//    should.
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
#include <cstdint>
#include <iostream>
#include <typeinfo>

#include "cppt_ag.hpp"

//========================================================================
// Data structures
//========================================================================
//------------------------------------------------------------------------
// A and B are related through B's constructors
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
  C(int32_t a, int32_t b) : x(a), y(b) {
    std::cout << "    C(a, b)" << std::endl;
  }
  int result() { return x + y; }

 private:
  int32_t x = 0;
  int32_t y = 0;
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

  int32_t some_int = 123;
};

//========================================================================
// main
//========================================================================
int main() {
  // 1. ===> IMPLICIT CONVERSION <===
  std::cout << "1. IMPLICIT CONVERSION:" << std::endl;

  // 1.1 Cast between different integer types
  int16_t var_a = 2000;
  int32_t var_b = var_a;

  // 1.2 Implicit conversion through a specialised constructor
  A obj_A;
  B obj_B = obj_A;

  std::cout << "    Size and type of obj_A: " << sizeof obj_A << " "
            << typeid(obj_A).name() << std::endl;
  std::cout << "    Size and type of obj_B: " << sizeof obj_B << " "
            << typeid(obj_B).name() << std::endl;

  // 2. ===> EXPLICIT CONVERSION <===
  std::cout << "2. EXPLICIT CONVERSION:" << std::endl;

  // 2.1 C-STYLE CASTS
  std::cout << "  2.1 C-style cast:" << std::endl;

  // 2.1.1 Cast between 16 and 32 bit integer types (good example)
  int32_t var_c = (int32_t)var_a;

  // 2.1.2 Cast between pointers (bad example - only because you can, doesn't
  // mean you should!)
  C* p_obj_C;
  p_obj_C = (C*)&obj_B;
#ifdef RUNTIME_ERROR
  // p_obj_C is pointing to something that's not an instance of C!
  std::cout << "    The result from p_obj_C->result(): " << p_obj_C->result()
            << std::endl;
#endif

  // 2.2 DYNAMIC_CAST<T>
  // Used for conversion of polymorphic types. Does runtime check of the types.
  // Returns nullptr if the conversion is not possible (so remember to check
  // the output!)
  std::cout << "  2.2 dynamic_cast<T>:" << std::endl;

  D obj_D;
  E obj_E;
  D* p_obj_D;
  E* p_obj_E;

  // 2.2.1 Cast derived to base (fine)
  p_obj_D = dynamic_cast<D*>(&obj_E);
  if (p_obj_D == nullptr) {
    std::cout << "    Null pointer on 1st dynamic_cast" << std::endl;
  }

  // 2.2.2 Cast base to derived (bad)
  p_obj_E = dynamic_cast<E*>(&obj_D);
  if (p_obj_E == nullptr) {
    std::cout << "    Null pointer on 2nd dynamic_cast" << std::endl;
  }

  // 2.3 STATIC_CAST<T>
  // Used for conversion of non-polymorphic types. Doesn't do runtime checks.
  std::cout << "  2.3 static_cast<T>:" << std::endl;

  // 2.3.1 Cast between numeric types (good)
  double var_d = 3.14159265;
  int32_t var_i = static_cast<int32_t>(var_d);
  std::cout << "    The value of var_i: " << var_i << std::endl;

  // 2.3.2 Cast base to derived (bad)
  p_obj_E = static_cast<E*>(&obj_D);
#ifdef RUNTIME_ERROR
  // ... p_obj_E points to an instance of D and E::print() accesses a
  // variable that's not present in D (the call itself will probably work
  // fine).
  p_obj_E->print();
#endif

  // 2.4 REINTERPRET_CAST<T>
  // Allows any pointer to be converted into any other pointer type. Also allows
  // any integral type to be converted into any pointer type and vice versa. No
  // runtime checks are performed.
  std::cout << "  2.4 reinterpret_cast<T>:" << std::endl;

  // 2.4.1 Cast one pointer type to another pointer type - bad, bad, bad!
  A* p_obj_A = &obj_A;
  p_obj_E = reinterpret_cast<E*>(p_obj_A);
#ifdef RUNTIME_ERROR
  //  p_obj_E points to an instance of A and E::print() accesses a
  // variable that's not present in A.
  p_obj_E->print();
#endif

  // 2.4.2 Cast integer to a pointer - bad, bad, bad!
  int32_t var_j = 123;
  // Bad, bad, bad!
  p_obj_A = reinterpret_cast<A*>(var_j);

  // 2.5 CONST_CAST<T>
  // Used to remove the const, volatile, and __unaligned attributes.
  std::cout << "  2.5 const_cast<T>:" << std::endl;

  // 2.5.1 Modify a non-const variable through a reference-to-const (good
  // example)
  int32_t var_k = 3;
  const int32_t& rck = var_k;
  const_cast<int32_t&>(rck) = 4;
  std::cout << "  The value of var_k: " << var_k << std::endl;

  // 2.5.2 Modify a const variable through a reference-to-const (bad example)
  const int32_t var_l = 3;
  const int32_t& rcl = var_l;
#ifdef RUNTIME_ERROR
  // var_l and for this reason this UB (though might actually work fine on some
  // platforms)
  const_cast<int32_t&>(rcl) = 4;
  std::cout << "  The value of var_l: " << var_l << std::endl;
#endif
}
