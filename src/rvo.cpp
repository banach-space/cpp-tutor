//========================================================================
// FILE:
//  rvo.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    This file can be used to demonstrate (Named-)Return-Value-Optimisation
//    ((N)RVO) and how it's related to the move constructor (i.e. whether and
//    when it gets called. In this file RVO is also referred to as copy
//    elision.
//
//    Note that the rules for RVO (but not NRVO) changed in C++17 in which
//    copy elision is guaranteed and doesn't require a move constructor. In
//    C++11 and C++14 you require the move constructor for this file to
//    compile without errors.
//
//    Relevant blog posts:
//      * https://jonasdevlieghere.com/guaranteed-copy-elision/
//      * https://blog.tartanllama.xyz/guaranteed-copy-elision/
//      * https://source.coveo.com/2018/11/07/interaction-between-move-semantic-and-copy-elision-in-c++/
//      * https://riptutorial.com/cplusplus/example/8222/guaranteed-copy-elision
//
//    Relevant compiler flags (GCC and clang):
//      * -fno-elide-constructors
//    With this flag:
//      * there's no copy elision at all in C++11 and C++14
//      * there's no copy elision for NRVO (and xvalues) in C++17 (but for RVO
//      the copy elision is guaranteed)
//
// License: MIT
//========================================================================
#include <iostream>
#include <utility>

#include "cpp_tutor.h"

//========================================================================
// Helper objects
//========================================================================
class List {
  struct Node {
    explicit Node(int new_val) : val_(new_val), next_(nullptr) {}
    int val_;
    Node *next_;
  };

  Node *head_ = nullptr;;

 public:
  explicit List() {
    std::cout << "    Explicit constructor" << std::endl; 
  };
  List(const List &) {
    std::cout << "    Copy constructor" << std::endl;
  }
#ifdef COMPILATION_ERROR
  // In C++11 and C++14 the move constructor is required when returning objects
  // by value from functions. That's because copy elision is optional and
  // compilers are free to apply it or not (hence a move constructor might be
  // required). In C++17 copy elision is guaranteed and hence you no longer
  // need the move constructor for functions returning by value. In summary,
  // deleting the move constructor will lead to a compiler error for C++11 and
  // C++14 (it's required in foo_rvo and foo_nvro).
  List(List &&) = delete;
#else
  List(List &&) {
    std::cout << "    Move constructor" << std::endl;  
  };
#endif
  ~List() = default;
  List operator=(List) = delete;
  List operator=(List &&) = delete;

  void createHead(int new_val) {
    auto *new_node = new Node(new_val);
    head_ = new_node;
  }
};

//========================================================================
// Utility functions
//========================================================================
List foo_nrvo() {
  int a = 10;
  List local_list;
  local_list.createHead(a);

  return local_list;
} 

List foo_rvo() {
  // Under C++17 you are guaranteed that this return value is never copy- or
  // move-constructed (thanks to guaranteed copy elision), but instead
  // constructed where it's actually needed.
  return List{};
}

#ifndef COMPILATION_ERROR
// foo_xvalue requires move constructor, which is only defined if
// COMPILATION_ERROR is *not* defined
List foo_xvalue() {
  int a = 10;
  List local_list;
  local_list.createHead(a);

  return std::move(local_list);
}
#endif

//========================================================================
// main
//========================================================================
int main() {
  std::cout << "Returning lvalue - NRVO:" << std::endl;
  List temp_list_1 = foo_nrvo();

  std::cout << "Returning prvalue - RVO:" << std::endl;
  List temp_list_2 = foo_rvo();

#ifndef COMPILATION_ERROR
  // foo_xvalue requires move constructor, which is only defined if
  // COMPILATION_ERROR is *not* defined
  std::cout << "Returning xvalue - no (N)RVO:" << std::endl;
  List temp_list_3 = foo_xvalue();
#endif

  return 0;
}
