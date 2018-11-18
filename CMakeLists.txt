cmake_minimum_required(VERSION 3.4.3 FATAL_ERROR)

project(cpp-tutor)

set(cpp-tutor_COMPILER_OPTIONS_CLANG -fcolor-diagnostics -std=c++17)
set(cpp-tutor_COMPILER_OPTIONS_GNU -fdiagnostics-color=always -std=c++17)

add_executable(cppTutorUT
  ${CMAKE_CURRENT_SOURCE_DIR}/src/strings.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/cpp_tutor_ut_main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/tests_strings_1.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/src/gtest-all.cc)

add_executable(strings_1
  ${CMAKE_CURRENT_SOURCE_DIR}/src/strings.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/strings_1_main.cpp)

add_executable(strings_2
  ${CMAKE_CURRENT_SOURCE_DIR}/src/strings_2_main.cpp)

add_executable(strings_3
  ${CMAKE_CURRENT_SOURCE_DIR}/src/strings_3_main.cpp)

target_include_directories(strings_1 PRIVATE SYSTEM
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(cppTutorUT PRIVATE SYSTEM
  ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/
  ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(executables cppTutorUT)

target_compile_options(cppTutorUT PRIVATE
  "$<$<CXX_COMPILER_ID:Clang>:${cpp-tutor_COMPILER_OPTIONS_CLANG}>")

target_compile_options(strings_1 PRIVATE
  "$<$<CXX_COMPILER_ID:Clang>:${cpp-tutor_COMPILER_OPTIONS_CLANG}>"
  "$<$<CXX_COMPILER_ID:GNU>:${cpp-tutor_COMPILER_OPTIONS_GNU}>")

target_compile_options(strings_2 PRIVATE
  "$<$<CXX_COMPILER_ID:Clang>:${cpp-tutor_COMPILER_OPTIONS_CLANG}>"
  "$<$<CXX_COMPILER_ID:GNU>:${cpp-tutor_COMPILER_OPTIONS_GNU}>")

target_compile_options(strings_3 PRIVATE
  "$<$<CXX_COMPILER_ID:Clang>:${cpp-tutor_COMPILER_OPTIONS_CLANG}>"
  "$<$<CXX_COMPILER_ID:GNU>:${cpp-tutor_COMPILER_OPTIONS_GNU}>")

if(UNIX)
  target_link_libraries(cppTutorUT PRIVATE pthread)
endif()
