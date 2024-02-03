#pragma once

#include "Core.h"

#include <string>
#include <functional>

namespace All {
	enum class LogLevel
	{
		Info,
		Warning,
		Error
	};

	std::string LogLevelToString(LogLevel level);

	class Logger
	{
	public:
		using LoggingFunc = std::function<void(LogLevel, const std::string&)>;
	public:

		static void Log(LogLevel level, const std::string& msg);
		static void LogInfo(const std::string& msg);
		static void LogWarning(const std::string& msg);
		static void LogError(const std::string& msg);

		static void SetLoggingFunc(const LoggingFunc& func) { m_Callback = func; }

		template<typename... Args>
		static std::string Format(const std::string& msg, Args&&... args);

	private:
		static LoggingFunc m_Callback;
	};
}
#ifdef ALL_IMPLEMENTATION
#include "Logger.cpp"
#endif

#define ALL_BIND_LOGGING_FUNC(func) std::bind(func, std::placeholders::_1, std::placeholders::_2)

#ifndef ALL_NO_LOGGING
#define ALL_FORMAT(...) Logger::Format(__VA_ARGS__)

#define ALL_LOG_INFO(msg) Logger::LogInfo(msg)
#define ALL_LOG_WARN(msg) Logger::LogWarning(msg)
#define ALL_LOG_ERROR(msg) Logger::LogError(msg)

#define ALL_LOG_FORMAT_INFO(...) ALL_LOG_INFO(ALL_FORMAT(__VA_ARGS__))

#define ALL_LOG_FORMAT_WARN(...)  ALL_LOG_WARN(ALL_FORMAT(__VA_ARGS__))

#define ALL_LOG_FORMAT_ERROR(...) ALL_LOG_ERROR(ALL_FORMAT(__VA_ARGS__))

#else
#define ALL_FORMAT(...)

#define ALL_LOG_INFO(msg)
#define ALL_LOG_WARN(msg)
#define ALL_LOG_ERROR(msg)

#define ALL_LOG_FORMAT_INFO(msg)
#define ALL_LOG_FORMAT_WARN(msg)
#define ALL_LOG_FORMAT_ERROR(msg)
#endif