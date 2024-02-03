#include "LinkedListIterator.h"

namespace All {
	template<typename Type>
	inline LinkedListIterator<Type>::LinkedListIterator(TNode* ptr)
		: m_Ptr(ptr)
	{
	}

	template<typename Type>
	inline LinkedListIterator<Type>::Reference LinkedListIterator<Type>::operator*()
	{
		ALL_ASSERT(m_Ptr);
		return m_Ptr->Element;
	}

	template<typename Type>
	inline LinkedListIterator<Type>::Pointer LinkedListIterator<Type>::operator->()
	{
		ALL_ASSERT(m_Ptr);
		return &m_Ptr->Element;
	}

	template<typename Type>
	inline bool LinkedListIterator<Type>::operator==(const LinkedListIterator<Type>& other) const
	{
		return m_Ptr == other.m_Ptr;
	}

	template<typename Type>
	inline bool LinkedListIterator<Type>::operator!=(const LinkedListIterator<Type>& other) const
	{
		return !(m_Ptr == other.m_Ptr);
	}

	template<typename Type>
	inline LinkedListIterator<Type>& LinkedListIterator<Type>::operator++()
	{
		ALL_ASSERT(m_Ptr);
		ALL_ASSERT(m_Ptr->Next);
		m_Ptr = m_Ptr->Next;
		return *this;
	}

	template<typename Type>
	inline LinkedListIterator<Type>& LinkedListIterator<Type>::operator++(int)
	{
		ALL_ASSERT(m_Ptr);
		ALL_ASSERT(m_Ptr->Next);
		LinkedListIterator temp = *this;
		m_Ptr = m_Ptr->Next;
		return temp;
	}

	template<typename Type>
	inline LinkedListIterator<Type>& LinkedListIterator<Type>::operator--()
	{
		ALL_ASSERT(m_Ptr);
		ALL_ASSERT(m_Ptr->Previous);
		m_Ptr = m_Ptr->Previous;
		return *this;
	}

	template<typename Type>
	inline LinkedListIterator<Type>& LinkedListIterator<Type>::operator--(int)
	{
		ALL_ASSERT(m_Ptr);
		ALL_ASSERT(m_Ptr->Previous);
		LinkedListIterator temp = *this;
		m_Ptr = m_Ptr->Previous;
		return temp;
	}

	template<typename Type>
	inline LinkedListIterator<Type>& LinkedListIterator<Type>::operator+=(const uint32_t value)
	{
		ALL_ASSERT(m_Ptr);
		for (int i = 0; i < value; i++)
		{
			ALL_ASSERT(m_Ptr->Next);
			m_Ptr = m_Ptr->Next;
		}
		return *this;
	}

	template<typename Type>
	inline LinkedListIterator<Type>& LinkedListIterator<Type>::operator-=(const uint32_t value)
	{
		ALL_ASSERT(m_Ptr);
		for (int i = 0; i < value; i++)
		{
			ALL_ASSERT(m_Ptr->Previous);
			m_Ptr = m_Ptr->Previous;
		}
		return *this;
	}

	template<typename Type>
	inline LinkedListIterator<Type>& LinkedListIterator<Type>::operator+(const uint32_t value) const
	{
		ALL_ASSERT(m_Ptr);
		LinkedListIterator temp = *this;
		temp += value;
		return temp;
	}

	template<typename Type>
	inline LinkedListIterator<Type>& LinkedListIterator<Type>::operator-(const uint32_t value) const
	{
		ALL_ASSERT(m_Ptr);
		LinkedListIterator temp = *this;
		temp -= value;
		return temp;
	}
}