#include "Allocator/Core.h"

#include "Allocator/Allocator.h"
#include "List.h"

namespace All {
	template<typename Type>
	inline List<Type>::List(Allocator& allocator, const size_t& capacity, const size_t& size, const float& increaseMultiplier)
		: m_Allocator(&allocator), m_Capacity(capacity), m_Size(size), m_IncreaseCapacityMultiplier(increaseMultiplier)
	{
		m_Data = m_Allocator->Allocate<Type>(m_Capacity);
	}

	template<typename Type>
	List<Type>::List(Allocator& allocator, const size_t& size)
		: List<Type>(allocator, static_cast<size_t>(size), static_cast<size_t>(size))
	{
	}

	template<typename Type>
	List<Type>::List(Allocator& allocator, const uint32_t& capacity)
		: List<Type>(allocator, capacity)
	{
	}

	template<typename Type>
	inline List<Type>::List(const List<Type>& other)
	{
		m_Data = other.m_Data;
		m_Allocator = other.m_Allocator;
		m_Size = other.m_Size;
		m_Capacity = other.m_Capacity;
		m_IncreaseCapacityMultiplier = other.m_IncreaseCapacityMultiplier;
	}

	template<typename Type>
	inline List<Type>::List(List<Type>&& other)
	{
		m_Data = other.m_Data;
		m_Allocator = other.m_Allocator;
		m_Size = other.m_Size;
		m_Capacity = other.m_Capacity;
		m_IncreaseCapacityMultiplier = other.m_IncreaseCapacityMultiplier;

		other.m_Data = nullptr;
		other.m_Allocator = nullptr;
		other.m_Size = 0;
		other.m_Capacity = 0;
		other.m_IncreaseCapacityMultiplier = 0;
	}

	template<typename Type>
	inline List<Type>::~List()
	{
		m_Allocator->Free(m_Data, m_Capacity * sizeof(Type));
	}

	template<typename Type>
	template<typename... Args>
	inline void List<Type>::Add(Args&&... args)
	{
		Add(Type(std::forward<Args>(args)...));
	}

	template<typename Type>
	inline void List<Type>::Add(Type&& element)
	{
		if (m_Size == m_Capacity)
			IncreaseCapacity();
		m_Data[m_Size] = std::move(element);
		m_Size++;
	}

	template<typename Type>
	void List<Type>::Insert(const uint64_t index, Type&& element)
	{
		ALL_ASSERT(index < m_Size);
		m_Data[index] = std::move(element);
	}

	template<typename Type>
	template<typename... Args>
	void List<Type>::Insert(const uint64_t index, Args&&... args)
	{
		Insert(index, Type(std::forward<Args>(args)...));
	}

	template<typename Type>
	inline void List<Type>::Remove(const uint64_t& index)
	{
		//ALL_ASSERT(index < m_Size);
		//memcpy(m_Data + index, m_Data + index + 1, (--m_Size - index) * sizeof(Type));
		Remove(index, 1);
	}

	template<typename Type>
	void List<Type>::Remove(const uint64_t& index, const size_t& count)
	{
		ALL_ASSERT(index < m_Size);
		ALL_ASSERT(count > 0);
		memcpy(m_Data + index, m_Data + index + count, (m_Size - index + 1 - count) * sizeof(Type));
		m_Size -= count;
	}

	template<typename Type>
	void List<Type>::Remove(const Iterator start, const Iterator end)
	{
		uint64_t index = start - begin();
		size_t count = end - start;

		Remove(index, count);
	}

	template<typename Type>
	inline void List<Type>::SetCapacity(const size_t& newCapacity)
	{
		Type* newData = m_Allocator->Allocate<Type>(newCapacity);
		if (newCapacity < m_Capacity)
		{
			memcpy(newData, m_Data, newCapacity * sizeof(Type));
			m_Size = m_Size > newCapacity ? newCapacity : m_Size;
		}
		else
		{
			memcpy(newData, m_Data, m_Capacity * sizeof(Type));
		}

		Type* temp = m_Data;
		uint64_t oldCapacity = m_Capacity;
		m_Data = newData;
		m_Capacity = newCapacity;
		m_Allocator->Free(temp, oldCapacity * sizeof(Type));
		newData = nullptr;
		temp = nullptr;
	}

	template<typename Type>
	inline void List<Type>::IncreaseCapacity()
	{
		size_t newCapacity = m_Capacity * m_IncreaseCapacityMultiplier;
		SetCapacity(newCapacity);
	}

	template<typename Type>
	void List<Type>::Resize(const size_t& newSize)
	{
		if (newSize > m_Capacity)
			SetCapacity(newSize);
		m_Size = newSize;
	}

	template<typename Type>
	inline List<Type>::Iterator List<Type>::begin() const
	{
		return Iterator(m_Data);
	}

	template<typename Type>
	inline List<Type>::Iterator List<Type>::end() const
	{
		return Iterator(m_Data + m_Size);
	}

	template<typename Type>
	inline const List<Type>::Iterator& List<Type>::cbegin() const
	{
		return begin();
	}

	template<typename Type>
	inline const List<Type>::Iterator& List<Type>::cend() const
	{
		return end();
	}
	template<typename Type>
	inline List<Type>::Reference List<Type>::operator[](const uint64_t& index)
	{
		ALL_ASSERT(index < m_Size);
		return m_Data[index];
	}
	template<typename Type>
	inline List<Type>::ConstRef List<Type>::operator[](const uint64_t& index) const
	{
		return List<Type>::operator[](index);
	}

	template<typename Type>
	void List<Type>::operator=(const List<Type>& other)
	{
		m_Data = other.m_Data;
		m_Capacity = other.m_Capacity;
		m_Size = other.m_Size;
		m_Allocator = other.m_Allocator;
		m_IncreaseCapacityMultiplier = other.m_IncreaseCapacityMultiplier;
	}

	template<typename Type>
	void List<Type>::operator=(List<Type>&& other)
	{
		m_Data = other.m_Data;
		m_Capacity = other.m_Capacity;
		m_Size = other.m_Size;
		m_Allocator = other.m_Allocator;
		m_IncreaseCapacityMultiplier = other.m_IncreaseCapacityMultiplier;

		other.m_Data = nullptr;
		other.m_Capacity = 0;
		other.m_Size = 0;
		other.m_Allocator = nullptr;
		other.m_IncreaseCapacityMultiplier = 0;
	}

	template<typename Type>
	bool List<Type>::operator==(const List<Type>& other)
	{
		return m_Data == other.m_Data && m_Size == other.m_Size && m_Capacity == other.m_Capacity && m_Allocator == other.m_Allocator && m_IncreaseCapacityMultiplier = other.m_IncreaseCapacityMultiplier;
	}

	template<typename Type>
	bool List<Type>::operator!=(const List<Type>& other)
	{
		return !(List<Type>::operator==(other));
	}
}