//========================================================================
// FILE:
//    vector_main_2.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    This file compares the efficiency of std::vector vs llvm::SmallVector in
//    terms of memory allocation.
//
//    The default size of llvm::SmallVector is 64 bytes, see:
//      * https://github.com/llvm/llvm-project/blob/release/20.x/llvm/include/llvm/ADT/SmallVector.h#L1137
//    The default number of inline elements (i.e. not requiring allocation) will
//    depend on the width of the underlying element type and is calculated
//    here:
//      * https://github.com/llvm/llvm-project/blob/release/20.x/llvm/include/llvm/ADT/SmallVector.h#L1172
//
//    AFAIK, std::vector, no matter the number of elements (nor the element
//    bit-width), will allways require memory allocation (i.e. there no inline
//    elements).
//
//    The optimization implemented in llvm::SmallVector is also known as Small
//    Object Optimiztion.
//
// License: MIT
//========================================================================
#include <dlfcn.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/ADT/StringRef.h>

#include <atomic>
#include <chrono>
#include <cppt_ag.hpp>
#include <cppt_tools.hpp>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

//==============================================================================
// alloc_counter - helper hooks to count alloc-like invocations
//==============================================================================
namespace alloc_counter {
std::atomic<size_t> malloc_count{0};
std::atomic<size_t> calloc_count{0};
std::atomic<size_t> realloc_count{0};
std::atomic<size_t> free_count{0};

// Use this to lock the counters to make sure we are not counting something
// unrelated to what is being benchmarked. Without this being toggled, we could
// be (for example) be measuring memory allocation for temporary string
// creation when calling `print_summary`.
std::atomic<bool> counters_locked = false;

void reset_counters() {
  malloc_count = 0;
  calloc_count = 0;
  realloc_count = 0;
  free_count = 0;
}

void lock_counters() { counters_locked = true; }

void unlock_counters() { counters_locked = false; }

void print_summary(std::string&& calls_of_what) {
  static size_t sub_sec_num = 0;

  std::cout << "  " << sub_sec_num++ << ". Count of alloc calls ("
            << calls_of_what << "):" << std::endl;
  std::cout << "   " << "malloc  : " << malloc_count.load() << std::endl;
  std::cout << "   " << "calloc  : " << calloc_count.load() << std::endl;
  std::cout << "   " << "realloc : " << realloc_count.load() << std::endl;
  std::cout << "   " << "free    : " << free_count.load() << std::endl;
}
}  // namespace alloc_counter

//==============================================================================
// Override C allocators
//==============================================================================
extern "C" {

void* malloc(size_t size) {
  if (!alloc_counter::counters_locked) alloc_counter::malloc_count++;

  // `malloc` function type
  using malloc_fn = void* (*)(size_t);

  // Give me the next definition of `malloc` after this one in the shared
  // library resolution chain. This should be the libc `malloc`.
  static malloc_fn real_malloc = (malloc_fn)dlsym(RTLD_NEXT, "malloc");
  return real_malloc(size);
}

void* calloc(size_t nmemb, size_t size) {
  if (!alloc_counter::counters_locked) alloc_counter::calloc_count++;

  // `calloc` function type
  using calloc_fn = void* (*)(size_t, size_t);

  // Give me the next definition of `calloc` after this one in the shared
  // library resolution chain. This should be the libc `malloc`.
  static calloc_fn real_calloc = (calloc_fn)dlsym(RTLD_NEXT, "calloc");
  return real_calloc(nmemb, size);
}

void* realloc(void* ptr, size_t size) {
  if (!alloc_counter::counters_locked) alloc_counter::realloc_count++;

  // `realloc` function type
  using realloc_fn = void* (*)(void*, size_t);

  // Give me the next definition of `realloc` after this one in the shared
  // library resolution chain. This should be the libc `malloc`.
  static realloc_fn real_realloc = (realloc_fn)dlsym(RTLD_NEXT, "realloc");
  return real_realloc(ptr, size);
}

void free(void* ptr) {
  if (!alloc_counter::counters_locked) alloc_counter::free_count++;

  // `free` function type
  using free_fn = void (*)(void*);

  // Give me the next definition of `free` after this one in the shared library
  // resolution chain. This should be the libc `malloc`.
  static free_fn real_free = (free_fn)dlsym(RTLD_NEXT, "free");
  real_free(ptr);
}
}

template <class T>
void populate_vector(T vector, size_t N) {
  for (auto j = 0; j < N; j++) vector.push_back(j);
}

//========================================================================
// main
//========================================================================
int main(int argc, const char** argv) {
  cppt::header(argv[0]);

  size_t sec_num = 1;
  // This is the number of inline int32_t elements in llvm::SmallVector. For
  // int64_t, this will already trigger an allocation (12 * 8 bytes > 64 bytes).
  const size_t k_num_elems = 12;

  //-------------------------------------------------------------------------
  // BASIC DEMO
  //-------------------------------------------------------------------------
  std::cout << sec_num++ << ". BASIC DEMO:" << std::endl;

  alloc_counter::reset_counters();
  alloc_counter::unlock_counters();
  std::vector<int32_t> vec_i32(k_num_elems);
  alloc_counter::lock_counters();
  alloc_counter::print_summary("Single std::vector, 0 elements, int32_t");

  alloc_counter::reset_counters();
  alloc_counter::unlock_counters();
  std::vector<int64_t> vec_i64(k_num_elems);
  alloc_counter::lock_counters();
  alloc_counter::print_summary("Single std::vector, 0 elements, int64_t");

  alloc_counter::reset_counters();
  alloc_counter::unlock_counters();
  llvm::SmallVector<int32_t> small_vec_i32(k_num_elems);
  alloc_counter::lock_counters();
  alloc_counter::print_summary("Single llvm::SmallVector, 0 elements, int32_t");

  alloc_counter::reset_counters();
  alloc_counter::unlock_counters();
  llvm::SmallVector<int64_t> small_vec_i64(k_num_elems);
  alloc_counter::lock_counters();
  alloc_counter::print_summary("Single llvm::SmallVector, 0 elements, int64_t");

  //-------------------------------------------------------------------------
  // BENCHMARKING
  //-------------------------------------------------------------------------
  std::cout << sec_num++ << ". BENCHMARKING:" << std::endl;
  std::vector<int32_t> array_v[100];
  llvm::SmallVector<int32_t> array_sv[100];

  // Array of 10 std::vector
  alloc_counter::reset_counters();
  auto start = std::chrono::steady_clock::now();
  alloc_counter::unlock_counters();
  for (auto i = 0; i < 10; i++) {
    array_v[i] = std::vector<int32_t>(0);
    populate_vector(array_v[i], k_num_elems);
  }
  std::chrono::duration<double> duration_v_10 =
      std::chrono::steady_clock::now() - start;
  alloc_counter::lock_counters();
  alloc_counter::print_summary("Array of 10 std::vector");

  // Array of 100 std::vector
  alloc_counter::reset_counters();
  start = std::chrono::steady_clock::now();
  alloc_counter::unlock_counters();
  for (auto i = 0; i < 100; i++) {
    array_v[i] = std::vector<int32_t>(0);
    populate_vector(array_v[i], k_num_elems);
  }
  std::chrono::duration<double> duration_v_100 =
      std::chrono::steady_clock::now() - start;
  alloc_counter::lock_counters();
  alloc_counter::print_summary("Array of 100 std::vector");

  // Array of 10 SmallVector
  alloc_counter::reset_counters();
  start = std::chrono::steady_clock::now();
  alloc_counter::unlock_counters();
  for (auto i = 0; i < 10; i++) {
    array_sv[i] = llvm::SmallVector<int32_t>(0);
    populate_vector(array_sv[i], k_num_elems);
  }
  std::chrono::duration<double> duration_sv_10 =
      std::chrono::steady_clock::now() - start;
  alloc_counter::lock_counters();
  alloc_counter::print_summary("Array of 10 SmallVector");

  // Array of 100 SmallVector
  alloc_counter::reset_counters();
  start = std::chrono::steady_clock::now();
  alloc_counter::unlock_counters();
  for (auto i = 0; i < 100; i++) {
    array_sv[i] = llvm::SmallVector<int32_t>(0);
    populate_vector(array_sv[i], k_num_elems);
  }
  std::chrono::duration<double> duration_sv_100 =
      std::chrono::steady_clock::now() - start;
  alloc_counter::lock_counters();
  alloc_counter::print_summary("Array of 100 SmallVector");

  //-------------------------------------------------------------------------
  // PRINT RESULTS
  //-------------------------------------------------------------------------
  std::cout << sec_num++
            << ". CUMMULATIVE ALLOCATION + ASSIGNMENT TIMES:" << std::endl;
  std::cout << "std::vector (10):         " << duration_v_10.count()
            << " seconds" << std::endl;
  std::cout << "std::vector (100):        " << duration_v_100.count()
            << " seconds" << std::endl;
  std::cout << "llvm::SmallVector (10):   " << duration_sv_10.count()
            << " seconds" << std::endl;
  std::cout << "llvm::SmallVector (100):  " << duration_sv_100.count()
            << " seconds" << std::endl;

  std::cout << std::endl;

  cppt::footer(argv[0]);
}
