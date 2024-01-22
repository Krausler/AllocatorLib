#pragma once

#include "Allocator/Types/ListIterator.h"

namespace All {
	class Allocator;

	const size_t c_DefaultListSize = 10;
	const float c_DefaultIncreaseMultiplier = 1.5f;

	template<typename Type>
	class List
	{
	private:
		using Pointer = Type*;
		using Reference = Type&;
		using ConstRef = const Reference;
		using Iterator = ListIterator<Type>;

	public:
		List(Allocator& allocator, const size_t& capacity = c_DefaultListSize, const size_t& size = 0, const float& increaseMultiplier = c_DefaultIncreaseMultiplier);
		List(Allocator& allocator, const size_t& size);
		List(Allocator& allocator, const uint32_t& capacity);
		List(const List<Type>& other);
		List(List<Type>&& other);
		~List();

		template<typename... Args>
		void Add(Args&&... args);
		void Add(Type&& element);

		void Insert(const uint64_t index, Type&& element);
		template<typename... Args>
		void Insert(const uint64_t index, Args&&... args);

		void Remove(const uint64_t& index);
		void Remove(const uint64_t& index, const size_t& count);
		void Remove(const Iterator start, const Iterator end);

		void SetCapacity(const size_t& newCapacity);
		void IncreaseCapacity();
		void Resize(const size_t& newSize);

		Iterator begin() const;
		Iterator end() const;
		const Iterator& cbegin() const;
		const Iterator& cend() const;

		Reference operator[](const uint64_t& index);
		ConstRef operator[](const uint64_t& index) const;
		void operator=(const List<Type>& other);
		void operator=(List<Type>&& other);
		bool operator==(const List<Type>& other);
		bool operator!=(const List<Type>& other);

		const size_t& GetSize() const { return m_Size; }
		const size_t& GetCapacity() const { return m_Capacity; }
		const void* GetData() const { return (void*)m_Data; }
		void* GetData() { return (void*)m_Data; }

	private:
		Pointer m_Data;
		Allocator* m_Allocator;
		size_t m_Size;
		size_t m_Capacity;

		float m_IncreaseCapacityMultiplier;
	};
}

#include "List.cpp"