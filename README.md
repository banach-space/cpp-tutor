cpp-tutor
=========
[![Apple Silicon](https://github.com/banach-space/cpp-tutor/actions/workflows/apple-silicon.yml/badge.svg)](https://github.com/banach-space/cpp-tutor/actions/workflows/apple-silicon.yml)
[![x86-Ubuntu](https://github.com/banach-space/cpp-tutor/actions/workflows/x86-ubuntu.yml/badge.svg)](https://github.com/banach-space/cpp-tutor/actions/workflows/x86-ubuntu.yml)
[![x86-Windows](https://github.com/banach-space/cpp-tutor/actions/workflows/x86-windows.yml/badge.svg)](https://github.com/banach-space/cpp-tutor/actions/workflows/x86-windows.yml)

Code examples for tutoring modern C++ (including **C++ STL** and **[LLVM ADT](https://llvm.org/docs/ProgrammersManual.html#picking-the-right-data-structure-for-a-task)** libraries)

Summary
-------
This tutorial provides a quick overview of various interesting
C++ features, presented through self-contained and runnable examples. It
focuses on modern C++ (>= C++11) and the **C++ STL** and **LLVM ADT**
libraries.

Lessons/examples are split into [items](#items). There is at least one runnable
example per item (i.e. a source file implementing `main`). The provided
examples are:
  * **Concise, yet complete**: while short, most files are runnable. This way,
    you can study the examples by experimenting. 
  * **Selective and opinionated**: emphasis is put on features and corner cases
    most likely encountered when _just starting with modern C++_. Focus is put
    on key points rather then presenting the complete picture.
  * **Clear rather than optimal**: code quality is sacrificed in favour of code
    clarity and readability, e.g. in some cases you will find more comments than
    code. Also, see the [disclaimer](#disclaimer)

It is assumed that you already know some basic C++ and are familiar with
object-oriented programming.

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
The only requirement for **cpp-tutor** is a C++ compiler that support C++17 and
`CMake-3.20` or newer. It is supported on Linux, Mac OS X and Windows, and is
regularly tested against the following configurations:
  * Linux Ubuntu 22.04 (GCC-11.4 and LLVM-14)
  * Windows (FIXME/TODO!)
  * Mac OS X 14.7.5 (AppleClang 15)

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
$ cmake -DCT_LLVM_INSTALL_DIR=<llvm-install-dir> <source_dir>
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
The default C++ standard for the whole project is set to C++17. In order to
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
1. [strings](https://embeddedartistry.com/blog/2017/7/24/stdstring-vs-c-strings)
   * C-strings vs `std::string` vs `std::string_view` vs `llvm::StringeRef`
     * The underlying data-representation for C++ strings.
   * SSO ([Short String Optimisation](https://akrzemi1.wordpress.com/2014/04/14/common-optimizations/))
   * `std::string` vs `std::string_view` vs `llvm::StringRef` 
     * Performance comparison.
   * Source files:
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
11. [std::vector](https://en.cppreference.com/w/cpp/container/vector) vs [llvm::SmallVector](https://llvm.org/docs/ProgrammersManual.html#llvm-adt-smallvector-h)
    * Source files:
        * `vector_main_1.cpp`, `vector_main_2.cpp`.
12. Miscelanous
    * Various items for which I am yet to identify a better place.
    * Source files: `misc_main.cpp`.
