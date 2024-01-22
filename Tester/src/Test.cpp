#include <vector>
#include <iostream>

#define ALL_NO_LOGGING
#include "Allocator/Allocator.h"
#include "Allocator/Types/List.h"

#include "StopWatch.h"

void AllocatorLogFunction(All::LogLevel level, const std::string& msg)
{
	std::cout << "[" << All::LogLevelToString(level) << "] Allocator: " << msg << std::endl;
}

int main()
{
	All::Logger::SetLoggingFunc(ALL_BIND_LOGGING_FUNC(AllocatorLogFunction));
	All::Allocator allocator;

	All::List<uint64_t> vectorLoopTimes(allocator);
	All::List<uint64_t> listInsertTimes(allocator);
	All::List<uint64_t> listLoopTimes(allocator);
	All::List<uint64_t> vectorInsertTimes(allocator);

	for (int i = 0; i < 20; i++)
	{
		StopWatch watch("vector test insert", true, false);

		std::vector<uint32_t> vec;

		for (int i = 0; i < 50000; i++)
		{
			vec.push_back(i);
		}

		watch.Stop();
		vectorInsertTimes.Add(watch.GetElapsedTimeNanoSeconds());
	}

	for (int i = 0; i < 20; i++)
	{
		std::vector<uint32_t> vec;

		for (int i = 0; i < 50000; i++)
		{
			vec.push_back(i);
		}
		StopWatch watch("vector test for loop", true, false);

		for (uint32_t& i : vec)
			i++;

		watch.Stop();
		vectorLoopTimes.Add(watch.GetElapsedTimeNanoSeconds());
	}

	for (int i = 0; i < 20; i++)
	{
		StopWatch watch("List test insert", true, false);

		All::List<uint32_t> list(allocator);

		for (int i = 0; i < 50000; i++)
			list.Add(i);

		watch.Stop();
		listInsertTimes.Add(watch.GetElapsedTimeNanoSeconds());
	}

	for (int i = 0; i < 20; i++)
	{
		All::List<uint32_t> list(allocator);

		for (int i = 0; i < 50000; i++)
			list.Add(i);
		StopWatch watch("List test for loop", true, false);

		for (uint32_t& i : list)
			i++;
		watch.Stop();
		listLoopTimes.Add(watch.GetElapsedTimeNanoSeconds());
	}

	uint64_t vectorResult = 0;
	uint64_t listResult = 0;
	uint64_t vectorLoopResult = 0;
	uint64_t listLoopResult = 0;
	for (int i = 0; i < 20; i++)
	{
		vectorResult += vectorInsertTimes[i];
		listResult += listInsertTimes[i];

		vectorLoopResult += vectorLoopTimes[i];
		listLoopResult += listLoopTimes[i];
	}

	std::cout << "vector result: " << vectorResult / 20 << std::endl;
	std::cout << "list result: " << listResult / 20 << std::endl;
	std::cout << "vector loop result: " << vectorLoopResult / 20 << std::endl;
	std::cout << "list loop result: " << listLoopResult / 20 << std::endl;
}