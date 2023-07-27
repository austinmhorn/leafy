#pragma once

////////////////////////////////////////////////////////////
// Define the LEAFY version
////////////////////////////////////////////////////////////
#define LEAFY_VERSION_MAJOR      0
#define LEAFY_VERSION_MINOR      1
#define LEAFY_VERSION_PATCH      0
#define LEAFY_VERSION_IS_RELEASE false


////////////////////////////////////////////////////////////
// Identify the operating system
// see https://sourceforge.net/p/predef/wiki/Home/
////////////////////////////////////////////////////////////
#if defined(_WIN32)

// Windows
#define LEAFY_SYSTEM_WINDOWS
#ifndef NOMINMAX
#define NOMINMAX
#endif

#elif defined(__APPLE__) && defined(__MACH__)

// Apple platform, see which one it is
#include "TargetConditionals.h"

#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR

// iOS
#define LEAFY_SYSTEM_IOS

#elif TARGET_OS_MAC

// macOS
#define LEAFY_SYSTEM_MACOS

#else

// Unsupported Apple system
#error This Apple operating system is not supported by LEAFY library

#endif

#elif defined(__unix__)

// UNIX system, see which one it is
#if defined(__ANDROID__)

// Android
#define LEAFY_SYSTEM_ANDROID

#elif defined(__linux__)

// Linux
#define LEAFY_SYSTEM_LINUX

#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)

// FreeBSD
#define LEAFY_SYSTEM_FREEBSD

#elif defined(__OpenBSD__)

// OpenBSD
#define LEAFY_SYSTEM_OPENBSD

#elif defined(__NetBSD__)

// NetBSD
#define LEAFY_SYSTEM_NETBSD

#else

// Unsupported UNIX system
#error This UNIX operating system is not supported by LEAFY library

#endif

#else

// Unsupported system
#error This operating system is not supported by LEAFY library

#endif


////////////////////////////////////////////////////////////
// Define a portable debug macro
////////////////////////////////////////////////////////////
#if !defined(NDEBUG)

#define LEAFY_DEBUG

#endif


////////////////////////////////////////////////////////////
// Define helpers to create portable import / export macros for each module
////////////////////////////////////////////////////////////
#if !defined(LEAFY_STATIC)

#if defined(LEAFY_SYSTEM_WINDOWS)

// Windows compilers need specific (and different) keywords for export and import
#define LEAFY_API_EXPORT __declspec(dllexport)
#define LEAFY_API_IMPORT __declspec(dllimport)

// For Visual C++ compilers, we also need to turn off this annoying C4251 warning
#ifdef _MSC_VER

#pragma warning(disable : 4251)

#endif

#else // Linux, FreeBSD, macOS

#define LEAFY_API_EXPORT __attribute__((__visibility__("default")))
#define LEAFY_API_IMPORT __attribute__((__visibility__("default")))

#endif

#else

// Static build doesn't need import/export macros
#define LEAFY_API_EXPORT
#define LEAFY_API_IMPORT

#endif
