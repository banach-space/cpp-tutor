//========================================================================
// FILE:
//    vector_main_2.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//
// License: MIT
//========================================================================
#include <cppt_ag.hpp>
#include <cppt_tools.hpp>

#include <llvm/ADT/StringRef.h>
#include <llvm/ADT/SmallVector.h>

#include <iostream>
#include <vector>


int main(int argc, const char** argv) {
  cppt::header(argv[0]);

  //-------------------------------------------------------------------------
  // BENCHMARKING
  //-------------------------------------------------------------------------
  std::vector<int32_t> array_v[100];
  llvm::SmallVector<int32_t> array_sv[100];
  size_t k_num_elems = 12;

  // Array of 10 std::vector
  auto start = std::chrono::steady_clock::now();
  for (auto i = 0; i < 10; i++) {
    array_v[i] = std::vector<int32_t>(0);
    for (auto j = 0; j < k_num_elems; j++)
      array_v[i].push_back(i);
  }
  std::chrono::duration<double> duration_v_10 =
      std::chrono::steady_clock::now() - start;

  // Array of 100 std::vector
  start = std::chrono::steady_clock::now();
  for (auto i = 0; i < 100; i++) {
    array_v[i] = std::vector<int32_t>(0);
    for (auto j = 0; j < k_num_elems; j++)
      array_v[i].push_back(i);
  }
  std::chrono::duration<double> duration_v_100 =
      std::chrono::steady_clock::now() - start;

  // Array of 10 SmallVector
  start = std::chrono::steady_clock::now();
  for (auto i = 0; i < 10; i++) {
    array_sv[i] = llvm::SmallVector<int32_t>(0);
    for (auto j = 0; j < k_num_elems; j++)
      array_sv[i].push_back(i);
  }
  std::chrono::duration<double> duration_sv_10 =
      std::chrono::steady_clock::now() - start;

  // Array of 100 SmallVector
  start = std::chrono::steady_clock::now();
  for (auto i = 0; i < 100; i++) {
    array_sv[i] = llvm::SmallVector<int32_t>(0);
    for (auto j = 0; j < k_num_elems; j++)
      array_sv[i].push_back(i);
  }
  std::chrono::duration<double> duration_sv_100 =
      std::chrono::steady_clock::now() - start;

  //-------------------------------------------------------------------------
  // PRINT RESULTS
  //-------------------------------------------------------------------------
  std::cout << "Average access times:     " << std::endl;
  std::cout << "std::vector (10):         " << duration_v_10.count()
            << " seconds" << std::endl;
  std::cout << "std::vector (100):        " << duration_v_100.count()
            << " seconds" << std::endl;
  std::cout << "llvm::SmallVector (10):   " << duration_sv_10.count() << " seconds"
            << std::endl;
  std::cout << "llvm::SmallVector (100):  " << duration_sv_100.count() << " seconds"
            << std::endl;

  std::cout << std::endl;

  cppt::footer(argv[0]);
}
