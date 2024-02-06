#include <vector>
#include <iostream>
#include <unordered_map>

#include "All/All.h"
#include "ArrayList.h"
#include "LinkedList.h"
#include "HashMap.h"

#include "StopWatch.h"

void AllocatorLogFunction(All::LogLevel level, const std::string& msg)
{
	std::cout << "[" << All::LogLevelToString(level) << "] Allocator: " << msg << std::endl;
}

int main()
{
	using namespace All;
	Logger::SetLoggingFunc(AllocatorLogFunction);
	Allocator allocator;

	HashMap<uint32_t, double> map(allocator);
}