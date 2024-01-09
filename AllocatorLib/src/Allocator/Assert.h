#pragma once

#include "Allocator/Core.h"
#include <filesystem>

//#if defined(ALL_DEBUG) && !defined(ALL_NO_ASSERT)

#define ALL_ASSERT_MSG(condition, msg) if(!(condition)) { ALL_LOG_ERROR(msg); __debugbreak(); }
#define ALL_ASSERT_NO_MSG(condition) if(!(condition)) { ALL_LOG_FORMAT_ERROR("Assertion failed in file %s at line %zu.", std::filesystem::path(__FILE__).filename().string(), __LINE__); __debugbreak(); }

#define ALL_IMPL_CHOOSE_ASSERT_TYPE_MACRO_NAME(_0, _1, macro, ...) macro
#define ALL_IMPL_CHOOSE_ASSERT_TYPE(...) ALL_EXPAND_MACRO( ALL_IMPL_CHOOSE_ASSERT_TYPE_MACRO_NAME(__VA_ARGS__, ALL_ASSERT_MSG, ALL_ASSERT_NO_MSG) )
#define ALL_ASSERT(...) ALL_EXPAND_MACRO(ALL_IMPL_CHOOSE_ASSERT_TYPE(__VA_ARGS__)(__VA_ARGS__))

//#else
//#define ALL_ASSERT(...)
//#endif