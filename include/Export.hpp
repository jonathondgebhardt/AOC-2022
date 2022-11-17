#pragma once

// clang-format off
#if defined(_MSC_VER)
    //  Microsoft
    #define UTILITIES_EXPORT __declspec(dllexport)
    #define UTILITIES_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
    //  GCC
    #define UTILITIES_EXPORT __attribute__((visibility("default")))
    #define UTILITIES_IMPORT
#else
    //  do nothing and hope for the best?
    #define UTILITIES_EXPORT
    #define UTILITIES_IMPORT
    #pragma warning Unknown dynamic link import / export semantics.
#endif
