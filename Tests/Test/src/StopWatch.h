#pragma once

#include <chrono>
#include <string>

class StopWatch {
public:
	StopWatch(const std::string& name = "StopWatch", bool start = true, bool printResult = true);
	~StopWatch();

	void Start();
	void Stop();

	const uint64_t& GetStartTime() { return m_StartTime; }
	const uint64_t& GetEndTime() { return m_EndTime; }
	const uint64_t& GetElapsedTimeNanoSeconds() { return m_ElapsedTime; }
	uint64_t GetElapsedTimeMilliSeconds() { return m_ElapsedTime * 1E-6; }
	double GetElapsedTimeSeconds() { return m_EndTime * 1E-9; }

private:
	std::string m_Name;
	uint64_t m_StartTime;
	uint64_t m_EndTime;
	uint64_t m_ElapsedTime;

	bool m_Started;
	bool m_PrintResult;
};