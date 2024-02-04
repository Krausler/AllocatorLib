#include "gtest/gtest.h"

#define ALL_ENABLE_ASSERT
#define ALL_ENABLE_LOGGING
#include "All/All.h"
#include "ArrayList.h"

#include <string>

using namespace All;

static All::Allocator allocator = All::Allocator();

#define LIST(size) ArrayList<SomeStuff> list(allocator, size)
#define LIST() ArrayList<SomeStuff> list(allocator)

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
	LIST();
	list.Add({ 0, true, 'h' });
	list.Add({ 2, true, 'e' });
	list.Add({ 5, true, 'l' });
	list.Add({ 9, false, 'l' });
	list.Add({ 42, false, 'o' });
	list.Add({ 42, true, 's' });
	list.Add({ 42, false, 't' });

	EXPECT_EQ(list.GetSize(), 7);
	SomeStuff t = { 42, true, 's' };
	EXPECT_EQ(true, list[5] == t);

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
	LIST(5);
	list.Add({ 0, true, 'h' });
	list.Add({ 2, true, 'e' });
	list.Add({ 5, true, 'l' });
	list.Add({ 9, false, 'l' });
	list.Add({ 42, false, 'o' });

	EXPECT_EQ(list.GetSize(), 5);

	list.Resize(20);
	EXPECT_EQ(list.GetSize(), 20);
	EXPECT_EQ(list.GetCapacity(), 20);

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