namespace All {
	// Map

	template<typename Key, typename Value, typename HashMapStoreValueType>
	inline Map<Key, Value, HashMapStoreValueType>::Map(Allocator& allocator, const size_t& capacity)
		: m_Allocator(allocator), m_Capacity(capacity), m_Values(m_Allocator, m_Capacity)
	{
	}

	template<typename Key, typename Value, typename HashMapStoreValueType>
	inline Map<Key, Value, HashMapStoreValueType>::Map(const Map& other)
		: m_Allocator(other.m_Allocator), m_Capacity(other.m_Capacity), m_Values(other.m_Values)
	{
	}

	template<typename Key, typename Value, typename HashMapStoreValueType>
	inline Map<Key, Value, HashMapStoreValueType>::Map(Map&& other)
		: m_Allocator(other.m_Allocator), m_Capacity(other.m_Capacity), m_Values(other.m_Values)
	{
		m_Capacity = 0;
		m_Values = nullptr;
	}

	template<typename Key, typename Value, typename HashMapStoreValueType>
	inline void Map<Key, Value, HashMapStoreValueType>::SetCapacity(const size_t& newSize)
	{
		m_Values.Resize(newSize);
	}

	template<typename Key, typename Value, typename HashMapStoreValueType>
	inline void Map<Key, Value, HashMapStoreValueType>::IncreaseCapacity()
	{
		SetCapacity(m_Values.GetSize() * c_HashMapIncreaseMultiplier);
	}

	template<typename Key, typename Value, typename HashMapStoreValueType>
	inline void Map<Key, Value, HashMapStoreValueType>::operator=(const Map& other)
	{
		m_Allocator = other.m_Allocator;
		m_Capacity = other.m_Capacity;
		m_Values = other.m_Values;
	}

	template<typename Key, typename Value, typename HashMapStoreValueType>
	inline void Map<Key, Value, HashMapStoreValueType>::operator=(Map&& other)
	{
		m_Allocator = other.m_Allocator;
		m_Capacity = other.m_Capacity;
		m_Values = other.m_Values;

		other.m_Capacity = 0;
		other.m_Values = nullptr;
	}

	template<typename Key, typename Value, typename HashMapStoreValueType>
	inline bool Map<Key, Value, HashMapStoreValueType>::operator==(const Map& other) const
	{
		return m_Allocator == other.m_Allocator && m_Capacity == other.m_Capacity && m_Values == other.m_Values;
	}

	template<typename Key, typename Value, typename HashMapStoreValueType>
	inline bool Map<Key, Value, HashMapStoreValueType>::operator!=(const Map& other) const
	{
		return !(*this == other);
	}

	// HashMap

	template<typename Key, typename Value, typename Hash>
	inline HashMap<Key, Value, Hash>::HashMap(Allocator& allocator, const size_t& capacity)
		: Map<Key, Value, LinkedList<Pair<Key, Value>>>(allocator, capacity)
	{
	}

	template<typename Key, typename Value, typename Hash>
	inline HashMap<Key, Value, Hash>::HashMap(const HashMap& other)
		: Map<Key, Value, LinkedList<Pair<Key, Value>>>(other)
	{
	}

	template<typename Key, typename Value, typename Hash>
	inline HashMap<Key, Value, Hash>::HashMap(HashMap&& other)
		: Map<Key, Value, LinkedList<Pair<Key, Value>>>(other)
	{
	}

	template<typename Key, typename Value, typename Hash>
	void HashMap<Key, Value, Hash>::Put(const Key& key, Value&& type)
	{
		uint32_t index = GetIndex(key);

		ALL_ASSERT(!m_Values[index], "What the hack");
	}

	template<typename Key, typename Value, typename Hash>
	template<typename... Args>
	void HashMap<Key, Value, Hash>::Emplace(const Key& key, Args&&... args)
	{
	}

	template<typename Key, typename Value, typename Hash>
	void HashMap<Key, Value, Hash>::Remove(const Key& key)
	{
	}

	template<typename Key, typename Value, typename Hash>
	uint64_t HashMap<Key, Value, Hash>::GetIndex(const Key& key)
	{
		size_t hash = Hash()(key);
		return hash % this->m_Capacity;
	}

	/*template<typename Key, typename Value, typename Hash>
	Map<Key, Value, LinkedList<Pair<Key, Value>>>::Reference HashMap<Key, Value, Hash>::operator[](const Key& key)
	{
		return this->m_Values[0][0].first;
	}*/
}