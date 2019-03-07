cpp-tutor
=========
[![Build Status](https://travis-ci.org/banach-space/cpp-tutor.svg?branch=master)](https://travis-ci.org/banach-space/cpp-tutor)
[![Build status](https://ci.appveyor.com/api/projects/status/axf91gjs67eoms4s/branch/add_appveyor?svg=true)](https://ci.appveyor.com/project/banach-space/cpp-tutor/branch/add_appveyor)

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

Platform Support
--------
The only requirement for **cpp-tutor** is a C++17 compliant compiler. It is
supported on Linux, Mac OS X and Windows and regularly tested on the following
configurations (extracted from the CI files: `.travis.yml` and `appveyor.yml`):
  * Linux Ubuntu 16.04 (GCC-7 and LLVM-7)
  * Windows (Visual Studio 2015)
  * Mac OS X 10.13 (Apple LLVM 10)

Please refer to the instructions

Build Instructions
--------
It is assumed that **cpp-tutor** will be built in `<build-dir>` and that the
top-level source directory is `<source-dir>`. For brevity, the build
instructions are presented for Linux only.

First, you will need to clone Google Test inside `<source-dir>`:
```
$ cd <source_dir>
$ git clone https://github.com/abseil/googletest.git
```

Next, you can build as follows:
```
$ cd <build-dir>
$ cmake <source_dir>
$ make
```
This will generate all the targets implemented for this project.

Content
--------
The items covered in this tutorial so far (with some relevant links):
1. Strings
   * C-strings vs `std::string` vs `std::string_view`
   * the underlying data-representation
   * SSO ([Short String Optimisation](https://akrzemi1.wordpress.com/2014/04/14/common-optimizations/))
   * benchmarking `std::string` vs `std::string_view`
   * source files:
     * `string.cpp`, `strings_1_main.cpp`, `strings_2_main.cpp` and `strings_3_main.cpp`
2. [Dynamic memory allocation](https://en.wikipedia.org/wiki/C_dynamic_memory_allocation)
   * TODO: `malloc\calloc\realloc\free`
   * all forms of `new` and `delete` (for plain datatypes and classes)
   * dynamic array of dynamic objects (a.k.a. 2-dimensional dynamical arrays)
   * memory leaks caused by mismatch in `new` and `delete` used
   * deep vs shallow copy
   * a basic memory manager with the aid of `placement new`
   * source files:
     * `pointers.cpp`, `strings_object.cpp`, `strings_object.hpp`,
       `strings_object_main.cpp`, `tests_strings_object.cpp`,
       `deep_vs_shallow.{hpp|cpp}`, `deep_vs_shallow_main.cpp`
3. [Smart pointers](https://docs.microsoft.com/en-us/cpp/cpp/smart-pointers-modern-cpp?view=vs-2017)
   * `std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`
   * `std::make_unqiue` and `std::make_shared`
   * source files:
     * `smart_pointers_main.cpp`
4. [L-value and R-value](https://eli.thegreenplace.net/2011/12/15/understanding-lvalues-and-rvalues-in-c-and-c/)
   * l-value vs r-value
   * l-value reference vs l-value to const reference vs r-value reference
   * `std::move` vs `std::forward`
   * source files:
     * `rvalue_vs_lvalue_main.cpp`
5. Move semantics
   * move constructor and move assign operator
   * source files
     * `memory_block.cpp`, `memory_block_main.cpp`
6. [Return Value Optimisation](https://en.wikipedia.org/wiki/Copy_elision#Return_value_optimization)
   * (N)RVO
   * guaranteed copy elision (C++17)
   * source files:
     * `rvo_main.cpp`
7. New kewords in modern C++:
   * `const` vs `constexpr`, `nullptr`, `auto`, `decltype`
   * source files:
     * `const_vs_constexpr_main.cpp`, `null_vs_nullptr_main.cpp`,
       `auto_vs_decltype_main.cpp`

License
--------
The MIT License (MIT)

Copyright (c) 2018 Andrzej Warzyński

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
