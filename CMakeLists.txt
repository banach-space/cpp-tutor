cmake_minimum_required(VERSION 3.4.3 FATAL_ERROR)

project(cpp-tutor)

set(CMAKE_CXX_STANDARD 14 CACHE STRING "")

# COMPILER FLAGS
# ==============
# Note that warnings are expected:
#   * the code deliberately doesn't follow the best coding practices, but
#     instead focuses on highlighting corner cases which indeed trigger warnings
#   * as part of the tutorial, compiler diagnostics (and indeed warnings) are
#     used to identify problematic code
# For this reason we don't want to suppress or fix the warnings and we don't
# use `-Werror` (or /WX for MSVC). Also, don't use `-Wall` as that would
# enable too many checks.
set(cpp-tutor_COMPILER_OPTIONS_CLANG -fcolor-diagnostics)
set(cpp-tutor_COMPILER_OPTIONS_GNU -fdiagnostics-color=always)
set(cpp-tutor_COMPILER_OPTIONS_MSVC)

# TARGETS AND THE CORRESPONDING SOURCE FILES
# ==============================================
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
    static_assert
    delete_vs_default
    init_stack_vs_global_vars
    init_aggregate
    init_types_of
    init_brace_elision
    init_list_gotchas
  )

set(cppTutorUT_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/strings_reverse.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/strings_object.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/cpp_tutor_ut_main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/tests_strings.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/tests_strings_object.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/src/gtest-all.cc)

set(strings_1_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/strings_reverse.cpp
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

set(static_assert_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/static_assert_main.cpp)

set(delete_vs_default_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/delete_vs_default_main.cpp)

set(init_stack_vs_global_vars_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/init_stack_vs_global_vars_main.cpp)

set(init_aggregate_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/init_aggregate_main.cpp)

set(init_brace_elision_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/init_brace_elision_main.cpp)

set(init_types_of_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/init_types_of_main.cpp)

set(init_list_gotchas_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/init_list_gotchas_main.cpp)


# EXECUTABLES AND THE INCLUDE DIRECTORIES FOR TARGETS
# ===================================================
foreach( executable ${cppTutor_EXECUTABLES} )
    add_executable( ${executable} 
      ${${executable}_SOURCES} 
      ${CMAKE_CURRENT_SOURCE_DIR}/src/cppt_tools.cpp
      )

    target_include_directories(${executable} PRIVATE SYSTEM
      ${PROJECT_BINARY_DIR}/include/
      ${CMAKE_CURRENT_SOURCE_DIR}/include
      )

target_compile_options(${executable} PRIVATE
  "$<$<CXX_COMPILER_ID:Clang>:${cpp-tutor_COMPILER_OPTIONS_CLANG}>"
  "$<$<CXX_COMPILER_ID:AppleClang>:${cpp-tutor_COMPILER_OPTIONS_CLANG}>"
  "$<$<CXX_COMPILER_ID:GNU>:${cpp-tutor_COMPILER_OPTIONS_GNU}>"
  "$<$<CXX_COMPILER_ID:MSVC>:${cpp-tutor_COMPILER_OPTIONS_MSVC}>")
endforeach()


# EXTRA SET-UP FOR UNIT TESTS
# ===========================
target_include_directories(cppTutorUT PRIVATE SYSTEM
  ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/
  ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include
)

if(UNIX)
  target_link_libraries(cppTutorUT PRIVATE pthread)
endif()


# CONFIGURE THE CPP_TUTOR.H HEADER FILE
# =====================================
option(MEMORY_LEAK "Use the implementation exhibiting memory leaks" OFF)
option(COMPILATION_ERROR "Enable code that leads to compilation errors" OFF)
option(DANGLING_REF_OR_PTR "Enable code that leads to dandling refs/ptrs" OFF)
option(RUNTIME_ERROR "Enable code that leads to run-time errors (e.g. UB)." OFF)

configure_file(
  ${PROJECT_SOURCE_DIR}/include/cppt_ag.hpp.in
  ${PROJECT_BINARY_DIR}/include/cppt_ag.hpp
  )
