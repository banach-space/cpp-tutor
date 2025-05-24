# TARGETS AND THE CORRESPONDING SOURCE FILES
# ==============================================
set(cppTutor_strings_EXECUTABLES
    strings_1
    strings_2
    strings_3
    strings_pool
)

set(strings_1_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/strings_reverse.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/strings_1_main.cpp)

set(strings_2_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/strings_2_main.cpp)

set(strings_3_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/strings_3_main.cpp)

set(strings_pool_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/strings_pool_main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/strings_pool.cpp)

# TODO: Turn this into a macro!
foreach( executable ${cppTutor_strings_EXECUTABLES} )
    add_executable( ${executable} 
      ${${executable}_SOURCES} 
      ${CMAKE_CURRENT_SOURCE_DIR}/../cppt_tools.cpp
      )

    target_include_directories(${executable} PRIVATE SYSTEM
      ${PROJECT_BINARY_DIR}/include/
      ${CMAKE_CURRENT_SOURCE_DIR}/../../include
      )

target_compile_options(${executable} PRIVATE
  "$<$<CXX_COMPILER_ID:Clang>:${cpp-tutor_COMPILER_OPTIONS_CLANG}>"
  "$<$<CXX_COMPILER_ID:AppleClang>:${cpp-tutor_COMPILER_OPTIONS_CLANG}>"
  "$<$<CXX_COMPILER_ID:GNU>:${cpp-tutor_COMPILER_OPTIONS_GNU}>"
  "$<$<CXX_COMPILER_ID:MSVC>:${cpp-tutor_COMPILER_OPTIONS_MSVC}>")
endforeach()

target_link_libraries(strings_1
  LLVMSupport
)
