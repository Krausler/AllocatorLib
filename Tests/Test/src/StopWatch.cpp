#include "StopWatch.h"

#include <iostream>

StopWatch::StopWatch(const std::string& name, bool start, bool printResult)
	: m_Name(name), m_PrintResult(printResult), m_StartTime(0), m_EndTime(0), m_ElapsedTime(0), m_Started(false)
{
	if (start)
		Start();
}

StopWatch::~StopWatch()
{
	if (m_Started)
		Stop();
}

void StopWatch::Start()
{
	if (m_Started)
		return;
	m_StartTime = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now()).time_since_epoch().count();
	m_Started = true;
}

void StopWatch::Stop()
{
	if (!m_Started)
		return;
	m_EndTime = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now()).time_since_epoch().count();
	m_ElapsedTime = m_EndTime - m_StartTime;
	if (m_PrintResult)
		std::cout << "Stop watch '" << m_Name << "' ended with elapsed time " << GetElapsedTimeNanoSeconds() << " nanoseconds." << std::endl;
	m_Started = false;
}