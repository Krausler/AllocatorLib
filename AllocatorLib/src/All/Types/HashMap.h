#pragma once

#include "../Core.h"
#include "../Allocator.h"
#include "LinkedList.h"

#include <xhash>

namespace All {
	const uint64_t c_DefaultHashMapSize = 10;
	const float c_FreeComparedToUsedSpaceResizeThreshold = 0.7;

	template<typename F, typename S>
	using Pair = std::pair<F, S>;

	template<typename Key, typename Value, typename Hash = std::hash<Key>>
	class Map
	{
	private:
		using Reference = Value&;
		using ConstRef = const Reference;
	public:
		Map(Allocator& allocator, const size_t& capacity = c_DefaultHashMapSize);
		virtual ~Map() = 0;

		virtual void Put(const Key& key, Value&& type) = 0;
		template<typename... Args>
		virtual void Emplace(const Key& key, Args&&... args) = 0;

		virtual void Remove(const Key& key) = 0;
	};

	template<typename Key, typename Value, typename Hash = std::hash<Key>>
	class HashMap
	{
	private:
		using Reference = Value&;
		using ConstRef = const Reference;
	public:
		HashMap(Allocator& allocator, const size_t& capacity = c_DefaultHashMapSize);
		HashMap(const HashMap<Key, Value, Hash>& other);
		HashMap(HashMap<Key, Value, Hash>&& other);

		void Put(const Key& key, Value&& type);
		template<typename... Args>
		void Emplace(const Key& key, Args&&... args);

		Reference operator[](const uint64_t& index);
		ConstRef operator[](const uint64_t& index) const;
		void operator=(HashMap<Key, Value, Hash>&& other);
		void operator=(const HashMap<Key, Value, Hash>& other);
		bool operator==(const HashMap<Key, Value, Hash>& other);
		bool operator!=(const HashMap<Key, Value, Hash>& other);
	private:
		ArrayList<LinkedList<Pair<Key, Value>>> m_Values;
		size_t m_Capacity;
		size_t m_Size;

		Allocator* m_Allocator;
	};
}

#include "HashMap.cpp"