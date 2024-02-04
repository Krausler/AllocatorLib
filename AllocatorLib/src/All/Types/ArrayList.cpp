#include "ArrayList.h"

#include <cmath>

namespace All {
	template<typename Type>
	inline ArrayList<Type>::ArrayList(Allocator& allocator)
		: m_Allocator(&allocator), m_Capacity(c_DefaultListCapacity), m_Size(0), m_IncreaseCapacityMultiplier(c_DefaultIncreaseMultiplier)
	{
		m_Data = m_Allocator->Allocate<Type>(m_Capacity);
	}

	template<typename Type>
	inline ArrayList<Type>::ArrayList(Allocator& allocator, const size_t& size)
		: m_Capacity(size), m_Size(size), m_IncreaseCapacityMultiplier(c_DefaultIncreaseMultiplier)
	{
		m_Data = m_Allocator->Allocate<Type>(m_Capacity);
	}

	template<typename Type>
	inline ArrayList<Type>::ArrayList(const ArrayList<Type>& other)
	{
		m_Data = other.m_Data;
		m_Allocator = other.m_Allocator;
		m_Size = other.m_Size;
		m_Capacity = other.m_Capacity;
		m_IncreaseCapacityMultiplier = other.m_IncreaseCapacityMultiplier;
	}

	template<typename Type>
	inline ArrayList<Type>::ArrayList(ArrayList<Type>&& other)
		: m_Data(other.m_Data), m_Allocator(other.m_Allocator), m_Size(other.m_Size), m_Capacity(other.m_Capacity), m_IncreaseCapacityMultiplier(other.m_IncreaseCapacityMultiplier)
	{
		other.m_Size = 0;
		other.m_Capacity = 0;
		other.m_IncreaseCapacityMultiplier = 0;
		other.m_Data = nullptr;
	}

	template<typename Type>
	inline ArrayList<Type>::~ArrayList()
	{
		m_Allocator->Free(m_Data, m_Capacity * sizeof(Type));
	}

	template<typename Type>
	template<typename... Args>
	inline void ArrayList<Type>::Add(Args&&... args)
	{
		Add(Type(std::forward<Args>(args)...));
	}

	template<typename Type>
	inline void ArrayList<Type>::Add(Type&& element)
	{
		if (m_Size == m_Capacity)
			IncreaseCapacity();
		m_Data[m_Size] = std::move(element);
		m_Size++;
	}

	template<typename Type>
	void ArrayList<Type>::Insert(const uint64_t index, Type&& element)
	{
		ALL_ASSERT(index < m_Size);
		m_Data[index] = std::move(element);
	}

	template<typename Type>
	template<typename... Args>
	void ArrayList<Type>::Insert(const uint64_t index, Args&&... args)
	{
		Insert(index, Type(std::forward<Args>(args)...));
	}

	template<typename Type>
	inline void ArrayList<Type>::Remove(const uint64_t& index)
	{
		Remove(index, 1);
	}

	template<typename Type>
	void ArrayList<Type>::Remove(const uint64_t& index, const size_t& count)
	{
		ALL_ASSERT(index < m_Size);
		ALL_ASSERT(count > 0);
		memcpy(m_Data + index, m_Data + index + count, (m_Size - index + 1 - count) * sizeof(Type));
		m_Size -= count;
	}

	template<typename Type>
	void ArrayList<Type>::Remove(const Iterator start, const Iterator end)
	{
		uint64_t index = start - begin();
		size_t count = end - start;

		Remove(index, count);
	}

	template<typename Type>
	inline void ArrayList<Type>::SetCapacity(const size_t& newCapacity)
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
	inline void ArrayList<Type>::IncreaseCapacity()
	{
		size_t newCapacity = (size_t)std::ceil(m_Capacity * m_IncreaseCapacityMultiplier);
		SetCapacity(newCapacity);
	}

	template<typename Type>
	void ArrayList<Type>::Resize(const size_t& newSize)
	{
		if (newSize > m_Capacity)
			SetCapacity(newSize);
		m_Size = newSize;
	}

	template<typename Type>
	inline ArrayList<Type>::Reference ArrayList<Type>::operator[](const uint64_t& index)
	{
		ALL_ASSERT(index < m_Size);
		return m_Data[index];
	}
	template<typename Type>
	inline ArrayList<Type>::ConstRef ArrayList<Type>::operator[](const uint64_t& index) const
	{
		return ArrayList<Type>::operator[](index);
	}

	template<typename Type>
	void ArrayList<Type>::operator=(const ArrayList<Type>& other)
	{
		m_Data = other.m_Data;
		m_Capacity = other.m_Capacity;
		m_Size = other.m_Size;
		m_Allocator = other.m_Allocator;
		m_IncreaseCapacityMultiplier = other.m_IncreaseCapacityMultiplier;
	}

	template<typename Type>
	void ArrayList<Type>::operator=(ArrayList<Type>&& other)
	{
		m_Data = other.m_Data;
		m_Capacity = other.m_Capacity;
		m_Size = other.m_Size;
		m_Allocator = other.m_Allocator;
		m_IncreaseCapacityMultiplier = other.m_IncreaseCapacityMultiplier;

		other.m_Capacity = 0;
		other.m_Size = 0;
		other.m_IncreaseCapacityMultiplier = 0;
	}

	template<typename Type>
	bool ArrayList<Type>::operator==(const ArrayList<Type>& other)
	{
		return m_Data == other.m_Data && m_Size == other.m_Size && m_Capacity == other.m_Capacity && m_Allocator == other.m_Allocator && m_IncreaseCapacityMultiplier = other.m_IncreaseCapacityMultiplier;
	}

	template<typename Type>
	bool ArrayList<Type>::operator!=(const ArrayList<Type>& other)
	{
		return !(*this == other);
	}
}