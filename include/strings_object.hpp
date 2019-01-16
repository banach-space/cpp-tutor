//========================================================================
// FILE:
//    strings_object.hpp
//
// AUTHOR:
//    banach-space@github
//
// DESCRIPTION:
//    A basic memory manager/container for std::string inside a preallocated
//    memory pool to ilustrate `placement new`. Assumes that only small strings
//    (falling into SSO) are stored, so that there's no dynamic memory
//    allocation within std::string taking place. Once built you could run it
//    as follows:
//        ./strings_object woof miau muu bee
//    Originally obtained from:
//        https://gitlab.com/fbb-git/cppannotations/blob/master/annotations/yo/memory/examples/strings.cc
//    The credit goes to: Frank B. Brokken (https://github.com/fbb-git)
//
// License: MIT
//========================================================================
#include <string>

//========================================================================
// The Strings class
//
// Represents a container for std::string that stores strings in internally
// mamneged memory pool. Every string is stored in a dynamicall allocated
// memory. This memory is allocated using `placement new` within the memory
// pool managed by the class.
//========================================================================
class Strings {
 public:
    Strings();
    Strings(char const *const *c_strings, size_t n);
    ~Strings();

    // Non-default destructor. The following special functions either need to
    // be defined or deleted.
    Strings(const Strings&) = delete;
    Strings(Strings&&) = delete;
    Strings operator=(Strings) = delete;
    Strings operator=(Strings&&) = delete;

    // Get the string at index `idx`
    std::string const &at(size_t idx) const {return d_memory[idx]; }
    // Reserve space for "request" strings
    void reserve(size_t request);
    // Add string
    void append(std::string const &next);
    // Get the number of strings currently stored
    size_t size() const {return d_size;}

 private:
    void reserve();
    void destroy();

    // Number of strings currently stored
    size_t d_size = 0;
    // Number of strings that can be stored inside d_memory (assumming that
    // only string's internal character buffer is used)
    size_t d_capacity = 0;
    // The raw memory pool used for storing strings
    std::string *d_memory = nullptr;
};
