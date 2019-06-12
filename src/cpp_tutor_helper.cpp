//========================================================================
// FILE:
//  cpp_tutor_helper.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Helper functions - implementation.
//
// License: MIT
//========================================================================
#include "../include/cpp_tutor_helper.h"

#include <iostream>

void cppt::header(const char* filename) {
  std::cout << "-------------------------------------" << std::endl;
  std::cout << "FILENAME: " << filename << std::endl << "CPP TUTOR: execution begins" << std::endl;
  std::cout << "-------------------------------------" << std::endl << std::endl;
}

void cppt::footer(const char* filename) {
  std::cout << std::endl; 
  std::cout << "-------------------------------------" << std::endl;
  std::cout << "CPP TUTOR: execution successful!" << std::endl;
  std::cout << "-------------------------------------" << std::endl;
}
