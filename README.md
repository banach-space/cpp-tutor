cpp-tutor
=========
[![Build Status](https://travis-ci.org/banach-space/cpp-tutor.svg?branch=master)](https://travis-ci.org/banach-space/cpp-tutor)

Code examples that I use for tutoring C++.

The intent of this tutorial is to give a quick overview of some of the most
important and interesting features of C++, including new additions in the
latest revision of the language (C++17 at the point of writing this). It is
assumed that you already know how to program and are familiar with
object-oriented design.

Disclaimer
------------
The examples presented here are meant to highlight (and sometimes exploit) the
specifics and quirks of the language. To this end, the presented examples may
exhibit undefined or implementation specific behaviour, or implement solutions
that are against good coding practices. This is done for educational purposes
only!

Status
--------
**WORK-IN-PROGRESS**

## Platform Support
Currently **cpp-tutor** supports Linux. It was tested with the following setups:
  * Linux 4.19.2 + clang-7.0/GCC-8.2 + CMake 3.12.4 (my host)
  * Linux 4.4.0 + clang-6.0/GCC-7 + CMake 3.9.2 (TravisCI)

## Build
TODO

Content
--------
The items covered in this tutorial so far:
* Strings
  * C-strings vs `std::string` vs `std::string_view`
  * the underlying data-representation
  * SSO ([Short String Optimisation](https://akrzemi1.wordpress.com/2014/04/14/common-optimizations/))
  * benchmarking `std::string` vs `std::string_view`
  * source files:
    * `string.cpp`, `strings_1_main.cpp`, `strings_2_main.cpp` and `strings_3_main.cpp`
* Dynamic memory allocation
  * all forms of `new` and `delete` (for plain datatypes and classes)
  * dynamic array of dynamic objects (a.k.a. 2-dimensional dynamical arrays)
  * memory leaks caused by mismatch in `new` and `delete` used
  * deep vs shallow copy
  * a basic memory manager with the aid of `placement new`
  * source files:
    * `pointers.cpp`, strings_object.cpp`, `strings_object.hpp`,
      `strings_object_main.cpp`, `tests_strings_object.cpp`,
      `deep_vs_shallow.{hpp|cpp}`, `deep_vs_shallow_main.cpp`
