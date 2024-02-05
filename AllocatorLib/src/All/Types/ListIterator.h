#pragma once

#include "../Core.h"

namespace All {
	template<typename Type>
	class ListIterator
	{
	private:
		using Pointer = Type*;
		using Reference = Type&;
		using ConstRef = const Reference;
	public:
		ListIterator(Pointer ptr);

		Reference operator*();
		Pointer operator->();
		bool operator!=(const ListIterator<Type>& other) const;
		bool operator==(const ListIterator<Type>& other) const;

		ListIterator<Type>& operator++();
		ListIterator<Type>& operator++(int);
		ListIterator<Type>& operator--();
		ListIterator<Type>& operator--(int);
		ListIterator<Type>& operator+=(const uint32_t value);
		ListIterator<Type>& operator-=(const uint32_t value);

		ListIterator<Type>& operator+(const uint32_t value) const;
		ListIterator<Type>& operator-(const uint32_t value) const;

		Reference operator[](const uint32_t index);
	private:
		Pointer m_Ptr;
	};
}

#include "ListIterator.cpp"