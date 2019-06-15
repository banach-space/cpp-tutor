//==============================================================================
// FILE:
//    strings_3_main.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Content:
//    - performance comparison of std::string and std::string_view
//
//    This experiment uses the substr method of std::string and
//    std::string_view to investigate whether one is faster than the other.
//
//    Make sure to build this example with different compiler optimisations
//    (e.g. -O0 vs -O3). This can be achieved by playing with the
//    CMAKE_BUILD_TYPE CMake variable (switch between Debug and Release), or by
//    invoking the compiler directly (with -O0 for no optimisations and -O3 for
//    very optimised code).
//
//    Key takeaway:
//    - Because std::string_view never triggers dynamic allocation, performance
//      wise is far superior when compared to std::string.
//
//
// License: MIT
//==============================================================================
#include "cppt_ag.hpp"
#include "cppt_tools.hpp"

#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#if __cplusplus >= 201703L
#include <string_view>
#endif

//==============================================================================
// Config for the experiment
//==============================================================================
static const int k_substr_len = 30;
static const int k_num_accesses = 1e7;

//==============================================================================
// main
//==============================================================================
int main(int argc, const char** argv) {
  cppt::header(argv[0]);

  //-------------------------------------------------------------------------
  // SET-UP
  //-------------------------------------------------------------------------
  // Read the sample text file (it's _very_ long)
  std::ifstream in_file("../src/test.txt");
  std::stringstream str_stream;
  str_stream << in_file.rdbuf();

  // Generate a std::string and std::string_view with the contents of the
  // text file
  std::string text = str_stream.str();
  size_t size = text.size();
#if __cplusplus >= 201703L
  std::string_view text_sv{text.c_str(), size};
#endif

  std::cout << "Number of characters: " << size << std::endl;
  std::cout << std::endl;

  // Generate random initial position for the substrings
  std::random_device seed;
  std::mt19937 engine(seed());
  std::uniform_int_distribution<> uniform_dist(0, size - k_substr_len - 2);

  std::vector<int> random_positions;
  random_positions.resize(k_num_accesses);
  for (auto i = 0; i < k_num_accesses; ++i) {
    random_positions.push_back(uniform_dist(engine));
  }

  //-------------------------------------------------------------------------
  // BENCHMARKING
  //-------------------------------------------------------------------------
  // First std::string
  auto start = std::chrono::steady_clock::now();
  for (auto i = 0; i < k_num_accesses; ++i) {
    text.substr(random_positions[i], k_substr_len);
  }
  std::chrono::duration<double> duration_str =
      std::chrono::steady_clock::now() - start;

  // Second std::string_view
  start = std::chrono::steady_clock::now();
  for (auto i = 0; i < k_num_accesses; ++i) {
#if __cplusplus >= 201703L
    text_sv.substr(random_positions[i], k_substr_len);
#endif
  }
  std::chrono::duration<double> duration_sv =
      std::chrono::steady_clock::now() - start;

  //-------------------------------------------------------------------------
  // PRINT RESULTS
  //-------------------------------------------------------------------------
  std::cout << "Average access times: " << std::endl;
  std::cout << "std::string::substr:      " << duration_str.count()
            << " seconds" << std::endl;
  std::cout << "std::string_view::substr: " << duration_sv.count() << " seconds"
            << std::endl;

  std::cout << std::endl;

  std::cout << "std::string/std::string_view "
            << duration_str.count() / duration_sv.count() << std::endl;

  cppt::footer(argv[0]);
}
