//========================================================================
// FILE:
//  strings_3_main.cpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//  Code samples to help understand:
//    * performance implications of using std::string vs std::string_view
//  It utilizes std::string::substr std::string_view::substr and demonstrates
//  that the latter is much much faster. It's reccomended to build this example
//  with different compiler optimisations (e.g. -O0 vs -O3).
//
//  This file implements a `main` function and is meant to be used as a
//  standalone project.
//
// License: MIT
//========================================================================
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

static const int k_substr_len = 30;
static const int k_num_accesses = 1e7;

int main() {
  //-------------------------------------------------------------------------
  // Set-up
  //-------------------------------------------------------------------------
  // Read the sample text file (it's very long)
  // TODO This assumes particular location - fix this
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
  // Benchmarking
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
  // Print results
  //-------------------------------------------------------------------------
  std::cout << "Average k_num_accesses times: " << std::endl;
  std::cout << "std::string::substr:      " << duration_str.count()
            << " seconds" << std::endl;
  std::cout << "std::string_view::substr: " << duration_sv.count() << " seconds"
            << std::endl;

  std::cout << std::endl;

  std::cout << "std::string/std::string_view "
            << duration_str.count() / duration_sv.count() << std::endl;
}
