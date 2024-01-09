#include "Logger.h"

#include <cstdarg>

namespace All {
	std::string LogLevelToString(LogLevel level)
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

	Logger::LoggingFunc Logger::m_Callback;

	void Logger::Log(LogLevel level, const std::string& msg)
	{
		if (!m_Callback)
			return;

		m_Callback(level, msg);
	}

	void Logger::LogInfo(const std::string& msg)
	{
		Log(LogLevel::Info, msg);
	}

	void Logger::LogWarning(const std::string& msg)
	{
		Log(LogLevel::Warning, msg);
	}

	void Logger::LogError(const std::string& msg)
	{
		Log(LogLevel::Error, msg);
	}
}