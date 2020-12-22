cpp-tutor
=========
[![Build Status](https://travis-ci.org/banach-space/cpp-tutor.svg?branch=master)](https://travis-ci.org/banach-space/cpp-tutor)
[![Build status](https://ci.appveyor.com/api/projects/status/axf91gjs67eoms4s/branch/add_appveyor?svg=true)](https://ci.appveyor.com/project/banach-space/cpp-tutor/branch/add_appveyor)
[![Build Status](https://github.com/banach-space/cpp-tutor/workflows/x86/badge.svg)](https://github.com/banach-space/cpp-tutor/actions?query=workflow%3Ax86)

Code examples for tutoring modern C++.

### tl;dr
Study by reading the source files, building the executable and running them to
see the output.

Summary
-------
The intent of this tutorial is to give a quick overview of some of the most
important and interesting features of C++, and to do so in a form of complete
and self-contained examples. It focuses on modern C++ (C++11/C++14/C++17), but
there are also some pre C++11 and C-specific examples for comparison. It's by
no means complete - quite the contrary. It aim is to be:
  * **Concise**: the examples are short, yet complete - to the point. There's a
    source file implementing the `main` function for each [items](#items) and
    you can study it in complete isolation from other items.
  * **Selective**: the examples emphasise features and corner cases most likely
    encountered when _just_ starting with modern C++. They focus on key points
    rather then presenting the complete picture. Less is more.
  * **Clear**: the examples sacrifice code quality in favour of code clarity
    and readability, e.g. in some cases there's more comments than code. Also,
    see the [disclaimer](#disclaimer)

It is assumed that you already know some basic C++ and are familiar with
object-oriented programming. These code samples will be helpful if you're
switching to C++ from a different object oriented language, are preparing for
an interview, or, like myself, are mentoring junior C++ developers.

Disclaimer
----------
The examples presented here are meant to highlight (and sometimes exploit) the
specifics and quirks of the language. To this end, the presented examples may
exhibit undefined or implementation specific behaviour, or implement solutions
that are against good coding practices. This is done for educational purposes
only and always thoroughly documented.

This repository is self-published and has not been peer-reviewed in the
traditional sense.

Status
------
**WORK-IN-PROGRESS**

Platform Support
----------------
The only requirement for **cpp-tutor** is a C++17 compliant compiler and
`CMake-3.4.3` or newer. It is supported on Linux, Mac OS X and Windows, and is
regularly tested against the following configurations (extracted from the CI
files: `.travis.yml` and `appveyor.yml`):
  * Linux Ubuntu 16.04 (GCC-7 and LLVM-7)
  * Windows (Visual Studio 2015)
  * Mac OS X 10.13 (Apple LLVM 10)

Please refer to the CI logs (links at the top of the page) for reference
setups.

Usage
-----
The [items](#items) covered in this tutorial are independent and you can be
studied in any order that works for you. Once you choose an item that's of
interest to you, go through the links and code samples available below. Next,
[build](#build-instructions) and run it.  Most executables print to `stdout`.
Make sure that you understand where the output comes from, what it means and
that it matches the comments in the code.

Some examples implement undefined behaviour, contain compiler errors or code
that leads to memory leaks. Such _broken_ or _problematic_ parts of the code
are guarded off with preprocessor symbolic constants:
  * `COMPILATION_ERROR`
  * `MEMORY_LEAK`
  * `DANGLING_REF_OR_PTR`
  * `RUNTIME_ERROR` 

Be default all symbolic constants are undefined and hence there are neither
compilation errors nor memory leaks. Play around by defining them (one at a
time), recompiling and re-running the examples. Make sure that the generated
output (or compiler errors) makes sense. Comments in the corresponding source
files might be instrumental in understanding those.

Remember to re-build and re-run the examples  _before_ and _after_
defining `MEMORY_LEAK`/`DANGLING_REF_OR_PTR`/`RUNTIME_ERROR` (defining
`COMPILATION_ERROR` will prevent the code from compiling, so it's not really
relevant here).

### Memory leaks
If you're developing on Linux, you can use [Valgrind](http://valgrind.org/) to
get a better grasp of memory leaks implemented in some of the examples, e.g.:
```bash
$ cd <build_dir>
$ valgrind smart_pointers
```
(`<build_dir>` is the build directory used when [building](#build-instructions)
the project).

On other platforms, you can use
[AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html). This has
already been integrated for you, but currently only for
[clang](https://clang.llvm.org/) and [gcc](https://gcc.gnu.org/).  In order to
use the address sanitizer, set the [build type](#build-types) to `ASAN`, and
run your example like this:
```bash
$ ASAN_OPTIONS=detect_leaks=1 strings_pool
```

### Runtime errors
The special case of runtime errors requires additional explanation. In most
cases the code guarded with `RUNTIME_ERRORS` exhibits undefined behaviour, and
as a result anything can happen. Although often the actual behaviour can be
predicted with a good amount of accuracy (because compilers, runtimes and
operating systems are relatively stable), do bare in mind that the output
will depend on the system that you use.

Build Instructions
------------------
It is assumed that **cpp-tutor** will be built in `<build-dir>` and that the
top-level source directory is `<source-dir>`. For brevity, the build
instructions are presented for Linux only.

First, you will need to clone Google Test inside `<source-dir>`:
```bash
$ cd <source_dir>
$ git clone https://github.com/google/googletest.git
```

Next, you can build all the examples as follows:
```bash
$ cd <build-dir>
$ cmake <source_dir>
$ make
```
This will generate all the targets implemented for this project. If you want to
(re-)build a particular example, run:
```bash
$ make <example_name>
```

### Build types
Set the `CMAKE_BUILD_TYPE` variable to:
  * `Release` to generate optimised code
  * `ASAN` to generate build unoptimised code, with plenty of good debug info and
    configured to be run with address sanitzer

### Switching between C++ standards
The default C++ standard for the whole project is set to C++14. In order to
rebuild using `C++11` or `C++17`, use `CMAKE_CXX_STANDARD`. For example, to
build in `C++17` mode:
```bash
$ cd <build-dir>
$ cmake -DCMAKE_CXX_STANDARD=17 <source_dir>
$ make
```
This will be very helpful when looking at how certain constructs have evolved
with the language.

### Disabled code
As explained [elsewhere](#usage) in this README.md, some of the examples
contain code disabled with preprocessor symbols. In order to enable one of
such blocks, define the corresponding preprocessor symbol by re-running CMake
like this:
```bash
$ cmake -D<PREPROCESSOR_SYMBOL>=1 .
```

in which `PREPROCESSOR_SYMBOL` is one of:
  * `COMPILATION_ERROR`
  * `MEMORY_LEAK`
  * `DANGLING_REF_OR_PTR`
  * `RUNTIME_ERROR` 

This will update `<build_dir>/include/cppt_ag.hpp`, the CMake auto-generated
header file that will be updated with the required definition. Next, re-build
and re-run your example.

Items
-----
The items covered in this tutorial so far (with some relevant links):
1. [Strings](http://cs.stmarys.ca/~porter/csc/ref/c_cpp_strings.html) (even more
   [strings](https://embeddedartistry.com/blog/2017/7/24/stdstring-vs-c-strings))
   * C-strings vs `std::string` vs `std::string_view`
   * the underlying data-representation
   * SSO ([Short String Optimisation](https://akrzemi1.wordpress.com/2014/04/14/common-optimizations/))
   * `std::string` vs `std::string_view` (performance comparison)
   * source files:
     * `strings_1_main.cpp` and `strings_reverse.cpp`
     * `strings_2_main.cpp`
     * `strings_3_main.cpp`
2. [Dynamic memory allocation](https://en.wikipedia.org/wiki/C_dynamic_memory_allocation)
   * all forms of `new` and `delete` (for plain datatypes and classes)
   * dynamic array of dynamic objects (a.k.a. 2-dimensional dynamical arrays)
   * memory leaks caused by mismatch in `new` and `delete`
   * deep vs shallow copy
   * a basic memory manager implemented in terms of `placement new`
   * source files:
     * `pointers_main.cpp`
     * `deep_vs_shallow.{hpp|cpp}`, `deep_vs_shallow_main.cpp`
     * `strings_pool_main.cpp`, `strings_pool.{cpp|hpp}`, `tests_strings_pool.cpp`,
3. [C++ Unit testing](https://github.com/google/googletest)
   * GTest and test fixtures
   * embedding GTest tests into the build system
   * source files:
     * `cpp_tutor_ut_main.cpp`, `CMakeLists.txt`, `tests_strings_object.cpp`, `tests_strings.cpp`
4. [Smart pointers](https://docs.microsoft.com/en-us/cpp/cpp/smart-pointers-modern-cpp?view=vs-2017)
   * `std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`
   * `std::make_unqiue` and `std::make_shared`
   * source files:
     * `smart_pointers_main.cpp`
5. [L-value and R-value](https://eli.thegreenplace.net/2011/12/15/understanding-lvalues-and-rvalues-in-c-and-c/)
   * l-value vs r-value
   * l-value reference vs l-value to const reference vs r-value reference
   * `std::move` vs `std::forward`
   * source files:
     * `rvalue_vs_lvalue_main.cpp`
6. [Move semantics](https://www.cprogramming.com/c++11/rvalue-references-and-move-semantics-in-c++11.html)
   * move constructor and move assign operator
   * source files
     * `memory_block.cpp`, `memory_block_main.cpp`
7. [Return Value Optimisation](https://en.wikipedia.org/wiki/Copy_elision#Return_value_optimization)
   * (N)RVO
   * guaranteed copy elision (C++17)
   * source files:
     * `rvo_main.cpp`
8. [New kewords in C++11](https://www.codeproject.com/Articles/570638/Ten-Cplusplus11-Features-Every-Cplusplus-Developer)
   and [beyond](https://github.com/AnthonyCalandra/modern-cpp-features)
   * `const` vs `constexpr`, `nullptr`, `auto`, `decltype`
   * source files:
     * `const_vs_constexpr_main.cpp`, `null_vs_nullptr_main.cpp`,
       `auto_vs_decltype_main.cpp`
9. [Explicit type conversion](https://www.learncpp.com/cpp-tutorial/4-4a-explicit-type-conversion-casting/) (a.k.a. casting):
    * explicit vs implicit type conversion
    * C vs C++ style casts (`static_cast`, `dynamic_cast`, `reinterpret_cast`,
      `const_cast`)
    * source files:
      * `type_casting_main.cpp`
10. [Initialization in modern C++](https://www.youtube.com/watch?v=SCoewvXablk)
   (is [bonkers](https://blog.tartanllama.xyz/initialization-is-bonkers/))
    * init values for variables with automatic and static storage duration
    * types of initialization (direct, copy, value, list)
    * brace elistion in list initialization
    * initializing aggregate types
    * various gotchas when using initilizer lists
    * source files:
      * `init_stack_vs_global_vars_main.cpp`, `init_aggregate_main.cpp`,
        `init_brace_elision_main.cpp`, `init_types_of_main.cpp`,
        `init_list_gotchas_main.cpp`

License
--------
The MIT License (MIT)

Copyright (c) 2018-2019 Andrzej Warzyński

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
