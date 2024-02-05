#include "gtest/gtest.h"

#define ALL_ENABLE_ASSERT
#define ALL_ENABLE_LOGGING
#include "All/All.h"
#include "ArrayList.h"

#include <string>

using namespace All;

All::Allocator allocator = All::Allocator();

#define LIST() ArrayList<SomeStuff> list(allocator)
#define LIST_SIZE(size) ArrayList<SomeStuff> list(allocator, size)

struct SomeStuff
{
	uint32_t n;
	bool c;
	char s;

	bool operator==(const SomeStuff& other) const
	{
		return n == other.n && c == other.c && s == other.s;
	}
};

TEST(ArrayList, Adding_Removing)
{
	// Testing adding to a vector
	LIST();
	list.Add({ 0, true, 'h' });
	list.Add({ 2, true, 'e' });
	list.Add({ 5, true, 'l' });
	list.Add({ 9, false, 'l' });
	list.Add({ 42, false, 'o' });
	list.Add({ 42, true, 's' });
	list.Add({ 42, false, 't' });

	// Checking whether objects are inserted at the correct position
	EXPECT_EQ(list.GetSize(), 7);
	SomeStuff t = { 42, true, 's' };
	EXPECT_EQ(true, list[5] == t);

	// Removing
	uint32_t count = 0;
	for (int i = 5; i > -1; i--)
	{
		count++;
		list.Remove(i);
		EXPECT_EQ(list.GetSize(), 7 - count);
	}

	EXPECT_EQ(list.GetSize(), 1);
}

TEST(ArrayList, Resizing_Shrinking)
{
	// Filling list till size
	LIST_SIZE(5);
	list[0] = { 0, true, 'h' };
	list[1] = { 2, true, 'e' };
	list[2] = { 5, true, 'l' };
	list[3] = { 9, false, 'l' };
	list[4] = { 42, false, 'o' };

	EXPECT_EQ(list.GetSize(), 5);

	// Resizing caused by adding of full list
	list.Add({ 42, false, 'o' });
	EXPECT_EQ(list.GetSize(), 6);
	EXPECT_EQ(list.GetCapacity(), 8);

	// Resizing to a bigger value
	list.Resize(20);
	EXPECT_EQ(list.GetSize(), 20);
	EXPECT_EQ(list.GetCapacity(), 20);

	//Resizing to a smaller size
	list.Resize(15);
	EXPECT_EQ(list.GetSize(), 15);
	EXPECT_EQ(list.GetCapacity(), 20);
}

TEST(ArrayList, Iterators)
{
	LIST();
	list.Add({ 0, true, 'h' });
	list.Add({ 2, true, 'e' });
	list.Add({ 5, true, 'l' });
	list.Add({ 9, false, 'l' });
	list.Add({ 42, false, 'o' });

	uint32_t count = 0;
	for (SomeStuff& s : list)
	{
		EXPECT_EQ(true, s == list[count]);
		count++;
	}
}

TEST(ArrayList, Stress_Test)
{
	// Adding 500.000 elements to a list
	ArrayList<uint32_t> list(allocator);

	for (int i = 0; i < 500000; i++)
	{
		list.Add(i);
	}

	// Iterating over 500.000 values and adding one to them
	for (uint32_t& i : list)
	{
		i++;
	}

	list.Remove(499998);
	list.Resize(499999);
}