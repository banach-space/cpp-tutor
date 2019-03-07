cmake_minimum_required(VERSION 3.4.3 FATAL_ERROR)

project(cpp-tutor)

set(CMAKE_CXX_STANDARD 17)

set(cpp-tutor_COMPILER_OPTIONS_CLANG -fcolor-diagnostics)
set(cpp-tutor_COMPILER_OPTIONS_GNU -fdiagnostics-color=always)

set(cppTutor_EXECUTABLES
    cppTutorUT
    strings_1
    strings_2
    strings_3
    pointers
    smart_pointers
    strings_object
    deep_vs_shallow
    memory_block
    rvalue_vs_lvalue
    type_casting
    const_vs_constexpr
    rvo
    auto_vs_decltype
    noexcept
    override_final
    null_vs_nullptr
  )

set(cppTutorUT_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/strings.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/strings_object.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/cpp_tutor_ut_main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/tests_strings_1.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/tests_strings_object.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/src/gtest-all.cc)

set(strings_1_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/strings.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/strings_1_main.cpp)

set(strings_2_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/strings_2_main.cpp)

set(strings_3_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/strings_3_main.cpp)

set(pointers_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/pointers.cpp)

set(smart_pointers_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/smart_pointers_main.cpp)

set(strings_object_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/strings_object_main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/strings_object.cpp)

set(deep_vs_shallow_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/deep_vs_shallow.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/deep_vs_shallow_main.cpp)

set(memory_block_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_block.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_block_main.cpp)

set(rvalue_vs_lvalue_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rvalue_vs_lvalue_main.cpp)

set(type_casting_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/type_casting_main.cpp)

set(const_vs_constexpr_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/const_vs_constexpr_main.cpp)

set(rvo_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rvo_main.cpp)

set(auto_vs_decltype_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/auto_vs_decltype_main.cpp)

set(noexcept_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/noexcept_main.cpp)

set(override_final_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/override_final_main.cpp)

set(null_vs_nullptr_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/null_vs_nullptr_main.cpp)

# Define executables and set the include directories
foreach( executable ${cppTutor_EXECUTABLES} )
    add_executable( ${executable} ${${executable}_SOURCES} )

    target_include_directories(${executable} PRIVATE SYSTEM
      ${PROJECT_BINARY_DIR}/include/
      ${CMAKE_CURRENT_SOURCE_DIR}/include
      )

target_compile_options(${executable} PRIVATE
  "$<$<CXX_COMPILER_ID:Clang>:${cpp-tutor_COMPILER_OPTIONS_CLANG}>"
  "$<$<CXX_COMPILER_ID:AppleClang>:${cpp-tutor_COMPILER_OPTIONS_CLANG}>"
  "$<$<CXX_COMPILER_ID:GNU>:${cpp-tutor_COMPILER_OPTIONS_GNU}>")
endforeach()

# Additional set-up for unit tests
target_include_directories(cppTutorUT PRIVATE SYSTEM
  ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/
  ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include
)

if(UNIX)
  target_link_libraries(cppTutorUT PRIVATE pthread)
endif()

# Configure the cpp_tutor.h header file
option(MEMORY_LEAK "Use the implementation exhibiting memory leaks" OFF)
option(COMPILATION_ERROR "Enable code that leads to compilation errors" OFF)

configure_file(
  ${PROJECT_SOURCE_DIR}/include/cpp_tutor.h.in
  ${PROJECT_BINARY_DIR}/include/cpp_tutor.h
  )
