#pragma once

//
// TargetConditionals
//
#if defined(__APPLE__) && defined(__MACH__)
#include <TargetConditionals.h>
#elif defined(_WIN32)
#define TARGET_OS_WIN32		1
#endif

//
// inttypes.h and stdint.h
//
#if TARGET_OS_WIN32
#include <msinttypes/inttypes.h>
#include <windows.h>
#else
#include <inttypes.h>
#endif

typedef void*           naHANDLE;

typedef unsigned short  naUTF16;
typedef char            naUTF8;

#include <string>
#include <stdarg.h>

#if TARGET_OS_WIN32
#define va_copy(dest, src) (dest = src)
#endif

#ifndef OUT
#define OUT
#endif

#ifndef IN
#define IN
#endif

#define naIS_INVALID_HANDLE(h)      ((h == NULL) || (h == (naHANDLE) -1))

#define RAPIDJSON_NO_INT64DEFINE
