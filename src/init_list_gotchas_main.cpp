//========================================================================
// FILE:
//    init_list_gotchas_main.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Demonstrates gotchas related to std::initializer_list
//
//    Experiment by:
//      * (un-)defining RUNTIME_ERROR
//      * (un-)defining COMPILATION_ERROR
//
// License: MIT
//========================================================================
#include "cppt_ag.hpp"
#include <cassert>
#include <vector>
#include <string>
#include <map>
#include <iostream>

//========================================================================
// Helper objects
//========================================================================
//-----------------------------------------------------------------------------
// Classes for exploiting {}
//-----------------------------------------------------------------------------
template <typename T>
struct FooBar {
  FooBar() {
    std::cout << "  FooBar()" << std::endl; 
  }; 
  FooBar(std::initializer_list<T> list) {
    std::cout << "  FooBar(std::initializer_list<T>)" << std::endl; 
  }
};

//========================================================================
// main
//========================================================================
int main() {
  // 1. WHAT DO THESE ACTUALLY MEAN?
  std::vector<int> v1{3, 0};     // {3, 0}
  std::vector<int> v2(3, 0);     // {0, 0, 0}

  std::string s1(48, 'a');       // "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
  std::string s2{48, 'a'};       // "0a"

  // 3 strings or 1 string equal "3"?
  std::vector<std::string> v{3};
  std::cout << "Size of v: " << v.size() << std::endl;

  // 2. EMPTY BRACES {} ARE SPECIAL!
  // Calls the default ctor even though there's a constructor taking std::initlizier_list
  FooBar<int> foo_bar1{};            
  // Calls the ctor taking std::initializer_list
  FooBar<int> foo_bar2{1};

  // 3. NO NARROWING CONVERSION
#ifdef COMPILATION_ERROR
  int var_k{2.0};
#endif 

  // 4. NESTED BRACES
  // Nice case
  std::map<std::string, int> my_map {{"abc", 1}, {"def", 2}};

  // Evil case
  std::vector<std::string> v3 = {{"abc"}, {"def"}};
#ifdef RUNTIME_ERROR
  std::vector<std::string> v4 = {{"abc", "def"}};
  std::cout << v4[1] << std::endl;
#endif

  // 5. AUTO AND STD::INITIALIZER_LIST
  // This is an int
  auto some_int{3};
  // This looks like an int
  auto some_other_int = {3};

  // This is an int
  int yet_another_int = some_int;
#ifdef COMPILATION_ERROR
  // This would be fine provided that some_other_int was indeed an int
  int yet_some_other_int = some_other_int;
#endif

}
