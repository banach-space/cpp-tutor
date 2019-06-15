//==============================================================================
// FILE:
//  cppt_tools.hpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    Prototypes for helper functions and definitions required by pretty much
//    every file in the project.
//
// License: MIT
//==============================================================================
// A workaround for GCC-9 on MacOS, as described here:
//   https://github.com/Homebrew/homebrew-core/issues/40676
// TODO Remove once fixed in HomeBrew or GCC
#ifdef __APPLE__
 #if __GNUC__ >= 9
 #include <sys/cdefs.h>
#endif
#endif
 
namespace cppt{
void header(const char* filename);
void footer(const char* filename);
}
