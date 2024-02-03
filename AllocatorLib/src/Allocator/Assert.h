#pragma once

#if defined(ALL_DEBUG) || defined(ALL_ENABLE_ASSERT)

#include "Logger.h"
#include "Platform.h"
#include <filesystem>

#define ALL_IMPL_ASSERT_MSG(check, msg) if(!(check)) { ALL_LOG_ERROR(msg); ALL_DEBUGBREAK(); }
#define ALL_IMPL_ASSERT_NO_MSG(check) ALL_IMPL_ASSERT_MSG(check, ALL_FORMAT("Assertion '%s' failed in file %s at line %zu.", #check, std::filesystem::path(__FILE__).filename().string(), __LINE__))

#define ALL_IMPL_CHOOSE_ASSERT_TYPE_MACRO_NAME(_0, _1, macro, ...) macro
#define ALL_IMPL_CHOOSE_ASSERT_TYPE(...) ALL_EXPAND_MACRO( ALL_IMPL_CHOOSE_ASSERT_TYPE_MACRO_NAME(__VA_ARGS__, ALL_IMPL_ASSERT_MSG, ALL_IMPL_ASSERT_NO_MSG) )

#define ALL_ASSERT(...) ALL_EXPAND_MACRO( ALL_IMPL_CHOOSE_ASSERT_TYPE(__VA_ARGS__)(__VA_ARGS__) )

#else
#define ALL_ASSERT(...)
#endif