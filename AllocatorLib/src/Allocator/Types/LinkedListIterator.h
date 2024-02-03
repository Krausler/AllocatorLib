#pragma once

#include "../Core.h"
#include "Node.h"

namespace All {
	template<typename Type>
	class LinkedListIterator
	{
	private:
		using TNode = Node <Type>;

		using Pointer = Type*;
		using Reference = Type&;
		using ConstRef = const Reference;
	public:
		LinkedListIterator(TNode* ptr);

		Reference operator*();
		Pointer operator->();
		bool operator==(const LinkedListIterator<Type>& other) const;
		bool operator!=(const LinkedListIterator<Type>& other) const;

		LinkedListIterator<Type>& operator++();
		LinkedListIterator<Type>& operator++(int);
		LinkedListIterator<Type>& operator--();
		LinkedListIterator<Type>& operator--(int);
		LinkedListIterator<Type>& operator+=(const uint32_t value);
		LinkedListIterator<Type>& operator-=(const uint32_t value);

		LinkedListIterator<Type>& operator+(const uint32_t value) const;
		LinkedListIterator<Type>& operator-(const uint32_t value) const;

	private:
		TNode* m_Ptr;
	};
}

#include "LinkedListIterator.cpp"