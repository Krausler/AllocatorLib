#pragma once

#include "../Core.h"
#include "../Allocator.h"

#include "ListIterator.h"

namespace All {
	const size_t c_DefaultListCapacity = 10;
	const float c_ListIncreaseMultiplier = 1.5f;

	template<typename Type>
	class ArrayList
	{
	private:
		using Pointer = Type*;
		using Reference = Type&;
		using ConstRef = const Reference;

		using Iterator = ListIterator<Type>;
	public:
		ArrayList(Allocator& allocator);
		ArrayList(Allocator& allocator, const size_t& size);
		ArrayList(const ArrayList<Type>& other);
		ArrayList(ArrayList<Type>&& other);
		~ArrayList();

		template<typename... Args>
		void Add(Args&&... args);
		void Add(Type&& element);

		void Insert(const uint64_t index, Type&& element);
		template<typename... Args>
		void Insert(const uint64_t index, Args&&... args);

		void Remove(const uint64_t& index);
		void Remove(const uint64_t& index, const size_t& count);
		void Remove(const Iterator start, const Iterator end);

		void SetIncreaseCapacityMultiplier(const float& increaseMultiplier) { m_IncreaseCapacityMultiplier = increaseMultiplier; }
		void SetCapacity(const size_t& newCapacity);
		void IncreaseCapacity();
		void Resize(const size_t& newSize);

		const size_t& GetSize() const { return m_Size; }
		const size_t& GetCapacity() const { return m_Capacity; }
		const void* GetData() const { return (void*)m_Data; }
		void* GetData() { return (void*)m_Data; }

		Iterator begin() const { return Iterator(m_Data); }
		Iterator end() const { return Iterator(m_Data + m_Size); }
		const Iterator cbegin() const { return begin(); }
		const Iterator cend() const { return end(); }

		Reference operator[](const uint64_t& index);
		ConstRef operator[](const uint64_t& index) const;
		void operator=(const ArrayList<Type>& other);
		void operator=(ArrayList<Type>&& other);
		bool operator==(const ArrayList<Type>& other) const;
		bool operator!=(const ArrayList<Type>& other) const;

	private:
		Pointer m_Data;
		Allocator* m_Allocator;
		size_t m_Size;
		size_t m_Capacity;

		float m_IncreaseCapacityMultiplier;
	};
}

#include "ArrayList.cpp"