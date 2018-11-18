cpp-tutor
=========
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
that are against good coding practices. 

Status
--------
**WORK-IN-PROGRESS**

## Platform Support
Currently **cpp-tutor** supports Linux. It was tested with the following setups:
  * Linux 4.19.2 + clang-7.0/GCC-8.2 + CMake 3.12.4

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
  * the relevant files:
    * `string.cpp`, `strings_1_main.cpp`, `strings_2_main.cpp` and `strings_3_main.cpp`
* Dynamic memory allocation
