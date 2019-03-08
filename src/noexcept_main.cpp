//========================================================================
// FILE:
//  noexcept_main.hpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//  Illustrates the noexcept keyword and demonstrates that std::vector has
//  different behavior if the type's move constructor is marked noexcept. This
//  reason behind this is very well explained here:
//   *
//   https://www.reddit.com/r/cpp_questions/comments/51btqw/why_does_stdvector_have_different_behavior_if_the/
//
// License: MIT
//========================================================================
#include <iostream>
#include <vector>

//========================================================================
// Helper functions and data structures
//========================================================================
// Throwing in foo triggers a call to std::terminate
void foo() noexcept(true) { throw 13; }

// Throwing in bar is fine
void bar() noexcept(false) { throw 13; }

// A is a trivial class with it's move constructor marked as noexcept. Note
// that move-constructing means that the id of the object moved-from is
// negated.
struct A {
  // Default constructor.
  A() : id(++n_items) {
    std::cout << "  A: default constructor for object: " << id << std::endl;
  }

  // Copy constructor.
  A(const A &other) : id(++n_items) {
    std::cout << "  A: copy constructor for object: " << id << std::endl;
  }

  // Copy assignment operator.
  A &operator=(const A &other) = delete;

  // Move constructor.
  A(A &&other) noexcept {
    id = other.id;
    other.id = -other.id;
    std::cout << "  A: moving object: " << id << std::endl;
  }

  // Move assignment operator.
  A &operator=(A &&other) = delete;

  // Destructor.
  ~A() { std::cout << "  A: destructing object: " << id << std::endl; }

 private:
  // The id of the current object
  int id;
  // The total number of objects created
  static size_t n_items;
};

size_t A::n_items = 0;

// B is a trivial class identical to B, but it's move constructor _are_not_
// marked as noexcept.Note that move-constructing means that the id of the
// object moved-from is negated.
struct B {
  // Default constructor.
  B() : id(++n_items) {
    std::cout << "  B: default constructor for object: " << id << std::endl;
  }

  // Copy constructor.
  B(const B &other) : id(++n_items) {
    std::cout << "  B: copy constructor for object: " << id << std::endl;
  }

  // Copy assignment operator.
  B &operator=(const B &other) = delete;

  // Move constructor.
  B(B &&other) {
    id = other.id;
    other.id = -other.id;
    std::cout << "  B: moving object: " << id << std::endl;
  }

  // Move assignment operator.
  B &operator=(B &&other) = delete;

  // Destructor.
  ~B() { std::cout << "  B: destructing object: " << id << std::endl; }

 private:
  // The id of the current object
  int id;
  // The total number of objects created
  static size_t n_items;
};

size_t B::n_items = 0;

//========================================================================
// main
//========================================================================
int main() {
  // 1. A VECTOR OF As.
  // The following code _will_not_ trigger any copy-constructions. Although v_A
  // will be resized, it's move constructors _is_ marked as noexcept and that's
  // what std::vector::resize will use.
  std::vector<A> v_A;

  std::cout << "Insert element 1" << std::endl;
  v_A.push_back(A());
  std::cout << "Insert element 2" << std::endl;
  v_A.push_back(A());
  std::cout << "Insert element 3" << std::endl;
  v_A.push_back(A());

  // 2. A VECTOR OF Bs.
  // The following code _will_ trigger copy-constructions. v_B will be
  // resized and B's move constructor _is_not_ marked as noexcept.
  std::vector<B> v_B;

  std::cout << "Insert element 1" << std::endl;
  v_B.push_back(B());
  std::cout << "Insert element 2" << std::endl;
  v_B.push_back(B());
  std::cout << "Insert element 3" << std::endl;
  v_B.push_back(B());

  // 3. THROW AN EXCEPTION INSIDE A FUNCTION DECORATED WITH noexcept(false)
  try {
    bar();
  } catch (...) {
    std::cout << "Exception in bar caught" << std::endl;
  }

  // 4. THROW AN EXCEPTION INSIDE A FUNCTION DECORATED WITH noexcept(true)
  // Change std::terminate so that it's obvious that it's being called.
  std::set_terminate([]() {
    std::cout << "!!!! Unhandled exception !!!!\n";
    std::abort();
  });

  try {
    foo();
  } catch (...) {
    std::cout << "Exception in foo caught" << std::endl;
  }
}
