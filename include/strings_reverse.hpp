//========================================================================
// FILE:
//    strings_reverse.hpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Functions for reversing C and C++ strings - prototypes.
//
// License: MIT
//========================================================================
#ifndef _STRINGS_
#define _STRINGS_

#include <string>

// Reverse a C string
void reverse_c_str(char *input_str);
// Reverse a C++ string (based on std::swap)
void reverse_cpp_str_swap(std::string *input_str);
// Rerverse a C++ string (based on std::reverse)
void reverse_cpp_str_alg(std::string *input_str);

#endif
