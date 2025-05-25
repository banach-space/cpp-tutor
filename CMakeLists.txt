cmake_minimum_required(VERSION 3.20)

project(cpp-tutor)

set(CMAKE_CXX_STANDARD 17 CACHE STRING "")

#===============================================================================
# 1. VERIFY LLVM INSTALLATION DIR
# This is just a bit of a sanity checking.
#===============================================================================
set(CT_LLVM_INSTALL_DIR "" CACHE PATH "LLVM installation directory")

# 1.1 Check the "include" directory
set(CT_LLVM_INCLUDE_DIR "${CT_LLVM_INSTALL_DIR}/include/llvm")
if(NOT EXISTS "${CT_LLVM_INCLUDE_DIR}")
message(FATAL_ERROR
  " CT_LLVM_INSTALL_DIR (${CT_LLVM_INCLUDE_DIR}) is invalid.")
endif()

# 1.2 Check that the LLVMConfig.cmake file exists (the location depends on the
# OS)
set(CT_VALID_INSTALLATION FALSE)

# Ubuntu + Darwin
if(EXISTS "${CT_LLVM_INSTALL_DIR}/lib/cmake/llvm/LLVMConfig.cmake")
  set(CT_VALID_INSTALLATION TRUE)
endif()

# Fedora
if(EXISTS "${CT_LLVM_INSTALL_DIR}/lib64/cmake/llvm/LLVMConfig.cmake")
  set(CT_VALID_INSTALLATION TRUE)
endif()

if(NOT ${CT_VALID_INSTALLATION})
  message(FATAL_ERROR
    "LLVM installation directory, (${CT_LLVM_INSTALL_DIR}), is invalid. Couldn't
    find LLVMConfig.cmake.")
endif()

#===============================================================================
# 2. LOAD LLVM CONFIGURATION
#    For more: http://llvm.org/docs/CMake.html#embedding-llvm-in-your-project
#===============================================================================
# Add the location of LLVMConfig.cmake to CMake search paths (so that
# find_package can locate it)
# Note: On Fedora, when using the pre-compiled binaries installed with `dnf`,
# LLVMConfig.cmake is located in "/usr/lib64/cmake/llvm". But this path is
# among other paths that will be checked by default when using
# `find_package(llvm)`. So there's no need to add it here.
list(APPEND CMAKE_PREFIX_PATH "${CT_LLVM_INSTALL_DIR}/lib/cmake/llvm/")

# The way LLVMConfigVersion.cmake is set up, it will only match MAJOR.MINOR
# exactly, even if we do not specify "REQUIRED" in the statement below.
# So we accept any version and do the proper ranged check below.
find_package(LLVM CONFIG)

# We defer the version checking to this statement
if("${LLVM_VERSION_MAJOR}" VERSION_LESS 18)
  message(FATAL_ERROR "Found LLVM ${LLVM_VERSION_MAJOR}, but need LLVM 18 or above")
endif()

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${CT_LLVM_INSTALL_DIR}")

message("LLVM STATUS:
  Definitions ${LLVM_DEFINITIONS}
  Includes    ${LLVM_INCLUDE_DIRS}
  Libraries   ${LLVM_LIBRARY_DIRS}
  Targets     ${LLVM_TARGETS_TO_BUILD}"
)

# Set the LLVM header and library paths
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# APPEND COMPILER FLAGS
# =====================
# Note that warnings are _expected_:
#   * the code deliberately doesn't follow the best coding practices, but
#     instead focuses on highlighting corner cases which indeed trigger warnings
#   * as part of the tutorial, compiler diagnostics (and indeed warnings) are
#     used to identify problematic code
# For this reason we don't want to suppress or fix any warninga and we don't
# use `-Werror` (or /WX for MSVC). Also, don't use `-Wall` as that would
# enable too many checks.
set(cpp-tutor_COMPILER_OPTIONS_CLANG -fcolor-diagnostics)
set(cpp-tutor_COMPILER_OPTIONS_GNU -fdiagnostics-color=always)
set(cpp-tutor_COMPILER_OPTIONS_MSVC)

# ADD THE ADDRESS SANITIZER BUILD TYPE
# ====================================
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE}
    CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel asan"
    FORCE)

set(CMAKE_C_FLAGS_ASAN
    "-fsanitize=address -fno-optimize-sibling-calls -fsanitize-address-use-after-scope -fno-omit-frame-pointer -g"
    CACHE STRING "Flags used by the C compiler during AddressSanitizer builds."
    FORCE)
set(CMAKE_CXX_FLAGS_ASAN
    "-fsanitize=address -fno-optimize-sibling-calls -fsanitize-address-use-after-scope -fno-omit-frame-pointer -g"
    CACHE STRING "Flags used by the C++ compiler during AddressSanitizer builds."
    FORCE)


# TARGETS AND THE CORRESPONDING SOURCE FILES
# ==============================================
set(cppTutor_EXECUTABLES
    cppTutorUT
    vector_1
    pointers
    smart_pointers
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
    misc
    copy_and_swap_idiom
  )

if (NOT WIN32)
  # This example leverages some lower-level/POSIX Unix logic that is not
  # available on Windows.
  # TODO: Make this work on Windows. If possible at all.
  list(APPEND cppTutor_EXECUTABLES vector_2)
endif()

set(cppTutorUT_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/strings/strings_reverse.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/strings/strings_pool.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/cpp_tutor_ut_main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/tests_strings.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/tests_strings_pool.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/src/gtest-all.cc)

set(vector_1_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/strings/strings_reverse.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/vector_main_1.cpp)

if (NOT WIN32)
  # This example leverages some lower-level/POSIX Unix logic that is not
  # available on Windows.
  # TODO: Make this work on Windows. If possible at all.
  set(vector_2_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vector_main_2.cpp)
endif()

set(pointers_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/pointers_main.cpp)

set(smart_pointers_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/smart_pointers_main.cpp)

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

set(misc_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/misc_main.cpp)

set(copy_and_swap_idiom_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/copy_and_swap_idiom_main.cpp)


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

target_link_libraries(vector_1
  LLVMSupport
)

if (NOT WIN32)
  # This example leverages some lower-level/POSIX Unix logic that is not
  # available on Windows.
  # TODO: Make this work on Windows. If possible at all.
  target_link_libraries(vector_2
    LLVMSupport
  )
endif()

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

# TODO
# =====================================
add_subdirectory(src)
