#pragma once

#include "../Core.h"
#include "../Allocator.h"
#include "LinkedList.h"

#include <xhash>

namespace All {
	const uint64_t c_DefaultHashMapSize = 10;
	const float c_HashMapIncreaseMultiplier = 1.5f;
	const float c_FreeComparedToUsedSpaceResizeThreshold = 0.7f;

	template<typename F, typename S>
	using Pair = std::pair<F, S>;

	template<typename Key, typename Value, typename HashMapStoreValueType>
	class Map
	{
	protected:
		using Reference = Value&;
		using ConstRef = const Reference;
	public:
		Map(Allocator& allocator, const size_t& capacity);
		Map(const Map& other);
		Map(Map&& other);
		virtual ~Map() = default;

		virtual void Put(const Key& key, Value&& type) = 0;

		virtual void Remove(const Key& key) = 0;

		void SetCapacity(const size_t& newSize);
		void IncreaseCapacity();

		const size_t& GetCapacity() const { return m_Capacity; }

		//virtual Reference operator[](const Key& index) = 0;
		ConstRef operator[](const uint64_t& index) const { return Map::operator[](index); }
		void operator=(Map&& other);
		void operator=(const Map& other);
		bool operator==(const Map& other) const;
		bool operator!=(const Map& other) const;
	protected:
		ArrayList<HashMapStoreValueType> m_Values;
		size_t m_Capacity;

		Allocator& m_Allocator;
	};

	template<typename Key, typename Value, typename Hash = std::hash<Key>>
	class HashMap : public Map<Key, Value, LinkedList<Pair<Key, Value>>>
	{
	public:
		HashMap(Allocator& allocator, const size_t& capacity = c_DefaultHashMapSize);
		HashMap(const HashMap& other);
		HashMap(HashMap&& other);

		virtual void Put(const Key& key, Value&& type) override;
		template<typename... Args>
		void Emplace(const Key& key, Args&&... args);

		virtual void Remove(const Key& key) override;

		//virtual typename Map<Key, Value, LinkedList<Pair<Key, Value>>>::Reference operator[](const Key& index) override;

	private:
		uint64_t GetIndex(const Key& key);
	};
}

#include "HashMap.cpp"