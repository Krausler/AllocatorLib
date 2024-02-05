#include "Logger.h"

#include <cstdarg>

namespace All {
	Logger::LoggingFunc Logger::m_Callback;

	inline std::string LogLevelToString(LogLevel level)
	{
		switch (level)
		{
		case LogLevel::Info:
			return "Info";
		case LogLevel::Warning:
			return "Warn";
		case LogLevel::Error:
			return "Error";
		default:
			return "The hack happend here";
		}
	}

	inline void Logger::Log(LogLevel level, const std::string& msg)
	{
		if (!m_Callback)
			return;

		m_Callback(level, msg);
	}

	inline void Logger::LogInfo(const std::string& msg)
	{
		Log(LogLevel::Info, msg);
	}

	inline void Logger::LogWarning(const std::string& msg)
	{
		Log(LogLevel::Warning, msg);
	}

	inline void Logger::LogError(const std::string& msg)
	{
		Log(LogLevel::Error, msg);
	}

	template<typename ...Args>
	inline std::string Logger::Format(const std::string& msg, Args&&... args)
	{
		char* buffer = new char[250];
		std::sprintf(buffer, msg.data(), std::forward<Args>(args)...);
		return buffer;
	}
}