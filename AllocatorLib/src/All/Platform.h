#pragma once

// Querying platform

#ifdef _WIN32
#ifdef _WIN64
#define ALL_PLATFORM_WINDOWS
#else
#error "x86 not supported"
#endif
#elif defined(__APPLE__) || defined(__MARCH__)
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR == 1
#error "IOS simulator is not supported!"
#elif TARGET_OS_IPHONE == 1
#define ALL_PLATFORM_IOS
#error "IOS is not supported!"
#elif TARGET_OS_MAC == 1
#define ALL_PLATFORM_MACOS
#error "MacOS is not supported!"
#else
#error "Unknown Apple platform!"
#endif

#elif defined(__ANDROID__)
#define ALL_PLATFORM_ANDROID
#error "Android is not supported!"
#elif defined(__linux__)
#define ALL_PLATFORM_LINUX
#else
#error "Unknown platform!"
#endif

// Debug break

#if defined(ALL_PLATFORM_WINDOWS)
#define ALL_DEBUGBREAK() __debugbreak()
#elif defined(ALL_PLATFORM_LINUX)
#include <signal.h>
#define ALL_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif