#include <vector>
#include <iostream>

#include "Allocator/Allocator.h"
#include "Allocator/Logger.h"
#include "Allocator/Types/List.h"

#include "StopWatch.h"

void AllocatorLogFunction(All::LogLevel level, const std::string& msg)
{
	//std::cout << "[" << All::LogLevelToString(level) << "] Allocator: " << msg << std::endl;
}

int main()
{
	All::Logger::SetLoggingFunc(ALL_BIND_LOGGING_FUNC(AllocatorLogFunction));
	All::Allocator allocator;

	{
		StopWatch watch("vector test insert");

		std::vector<uint32_t> vec;

		for (int i = 0; i < 50000; i++)
		{
			vec.push_back(i);
		}
	}

	{
		std::vector<uint32_t> vec;

		for (int i = 0; i < 50000; i++)
		{
			vec.push_back(i);
		}
		StopWatch watch("vector test for loop");

		for (uint32_t& i : vec)
			i += 1;
	}

	{
		StopWatch watch("List test insert");

		All::List<uint32_t> list(&allocator);

		for (int i = 0; i < 50000; i++)
			list.Add(i);
	}

	{
		All::List<uint32_t> list(&allocator);

		for (int i = 0; i < 50000; i++)
			list.Add(i);
		StopWatch watch("List test for loop");

		for (uint32_t& i : list)
			i += 1;
	}
}