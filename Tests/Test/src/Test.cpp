#include <vector>
#include <iostream>

#define ALL_NO_LOGGING
#include "Allocator/Allocator.h"
#include "Allocator/Types/ArrayList.h"
#include "Allocator/Types/LinkedList.h"

#include "StopWatch.h"

#include <list>

void AllocatorLogFunction(All::LogLevel level, const std::string& msg)
{
	std::cout << "[" << All::LogLevelToString(level) << "] Allocator: " << msg << std::endl;
}

int main()
{
	using namespace All;
	Logger::SetLoggingFunc(AllocatorLogFunction);
	Allocator allocator;

	ArrayList<uint32_t> list(allocator);
	list.Add(5);
	list.Remove(0);
}