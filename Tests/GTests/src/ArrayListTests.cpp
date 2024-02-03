#include "gtest/gtest.h"

#include "Allocator/Allocator.h"
#include "Allocator/Types/ArrayList.h"

#include <string>

static All::Allocator allocator = All::Allocator();

TEST(ArrayList, Adding_Removing)
{
	using namespace All;

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

	ArrayList<SomeStuff> list(allocator);
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

	for (int i = 0; i < 6; i++)
	{
		list.Remove(i);
		EXPECT_EQ(list.GetSize(), 7 - i - 1);
	}

	EXPECT_EQ(list.GetSize(), 1);
}

TEST(ArrayList, Resizing)
{
}

TEST(ArrayList, Shrinking)
{
}

TEST(ArrayList, Iterators)
{
}