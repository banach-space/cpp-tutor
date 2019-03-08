//========================================================================
// FILE:
//  set_new_handler_example.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Illustrates how to use set_new_handler()
//
//  DISCLAIMER:
//    I haven't been able to demonstrate outofMemory in action. My laptop hangs
//    before the exception is thrown.
//
// License: MIT
//========================================================================
#include <iostream>
#include <string>

void outOfMemory() {
  std::cout << "Memory exhausted. Program terminates." << std::endl;
  exit(1);
}

class Z {
  int a = 10;
};

int main() {
  std::set_new_handler(outOfMemory);

  char* memory = new char[sizeof(Z)];
  Z* a = new (memory) Z;

  char* memory2 = new char[5 * sizeof(Z)];
  Z* b = new (memory2) Z[5];

  char* memory3 = new char[4 * sizeof(Z)];
  Z* c = new (memory3) Z[500];
}
