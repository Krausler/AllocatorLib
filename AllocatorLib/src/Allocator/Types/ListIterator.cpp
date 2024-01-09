#include "ListIterator.h"
namespace All {
	template<typename Type>
	inline ListIterator<Type>::ListIterator(Pointer ptr)
		: m_Ptr(ptr)
	{
	}

	template<typename Type>
	ListIterator<Type>::Reference ListIterator<Type>::operator*()
	{
		return *m_Ptr;
	}

	template<typename Type>
	ListIterator<Type>::Pointer ListIterator<Type>::operator->()
	{
		return m_Ptr;
	}

	template<typename Type>
	inline bool ListIterator<Type>::operator!=(const ListIterator<Type>& other) const
	{
		return !(ListIterator<Type>::operator==(other));
	}
	template<typename Type>
	inline bool ListIterator<Type>::operator==(const ListIterator<Type>& other) const
	{
		return m_Ptr == other.m_Ptr;
	}
	template<typename Type>
	inline ListIterator<Type>& ListIterator<Type>::operator++()
	{
		m_Ptr++;
		return *this;
	}
	template<typename Type>
	inline ListIterator<Type>& ListIterator<Type>::operator++(int)
	{
		ListIterator temp = *this;
		m_Ptr++;
		return temp;
	}

	template<typename Type>
	inline ListIterator<Type>& ListIterator<Type>::operator--()
	{
		m_Ptr--;
		return *this;
	}

	template<typename Type>
	inline ListIterator<Type>& ListIterator<Type>::operator--(int)
	{
		ListIterator temp = *this;
		m_Ptr--;
		return temp;
	}
	template<typename Type>
	inline ListIterator<Type>& ListIterator<Type>::operator+=(const uint32_t value)
	{
		m_Ptr += value;
		return *this;
	}
	template<typename Type>
	inline ListIterator<Type>& ListIterator<Type>::operator-=(const uint32_t value)
	{
		m_Ptr -= value;
		return *this;
	}
	template<typename Type>
	inline ListIterator<Type>& ListIterator<Type>::operator+(const uint32_t value) const
	{
		ListIterator temp = *this;
		temp += value;
		return temp;
	}
	template<typename Type>
	inline ListIterator<Type>& ListIterator<Type>::operator-(const uint32_t value) const
	{
		ListIterator temp = *this;
		temp -= value;
		return temp;
	}
	template<typename Type>
	inline ListIterator<Type>::Reference ListIterator<Type>::operator[](const uint32_t index)
	{
		return m_Ptr[index];
	}
}