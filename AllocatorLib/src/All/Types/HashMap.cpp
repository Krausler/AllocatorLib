#include "HashMap.h"
namespace All {
	template<typename Key, typename Value, typename Hash>
	inline HashMap<Key, Value, Hash>::HashMap(Allocator& allocator, const size_t& capacity)
		: m_Allocator(&allocator), m_Values(allocator, capacity), m_Size(0)
	{
	}
	template<typename Key, typename Value, typename Hash>
	inline HashMap<Key, Value, Hash>::HashMap(const HashMap<Key, Value, Hash>& other)
		: m_Values(other.m_Values), m_Allocator(other.m_Allocator), m_Size(other.m_Size)
	{
	}

	template<typename Key, typename Value, typename Hash>
	inline HashMap<Key, Value, Hash>::HashMap(HashMap<Key, Value, Hash>&& other)
		: m_Values(other.m_Values), m_Allocator(other.m_Allocator), m_Size(other.m_Size)
	{
		m_Size = 0;
	}

	template<typename Key, typename Value, typename hash>
	inline void HashMap<Key, Value, hash>::Put(const Key& key, Value&& type)
	{
		uint64_t hash = Hash()();
		uint64_t index = hash / m_Values.GetCapacity();

		auto t = m_Values[index];
	}

	template<typename Key, typename Value, typename hash>
	template<typename ...Args>
	inline void HashMap<Key, Value, hash>::Emplace(const Key& key, Args && ...args)
	{
	}

	template<typename Key, typename Value, typename Hash>
	HashMap<Key, Value, Hash>::Reference HashMap<Key, Value, Hash>::operator[](const uint64_t& index)
	{
		return Reference();
	}
	template<typename Key, typename Value, typename Hash>
	HashMap<Key, Value, Hash>::ConstRef HashMap<Key, Value, Hash>::operator[](const uint64_t& index) const
	{
		return ConstRef();
	}
	template<typename Key, typename Value, typename Hash>
	void HashMap<Key, Value, Hash>::operator=(HashMap<Key, Value, Hash>&& other)
	{
	}
	template<typename Key, typename Value, typename Hash>
	void HashMap<Key, Value, Hash>::operator=(const HashMap<Key, Value, Hash>& other)
	{
	}
	template<typename Key, typename Value, typename Hash>
	bool HashMap<Key, Value, Hash>::operator==(const HashMap<Key, Value, Hash>& other)
	{
		return false;
	}
	template<typename Key, typename Value, typename Hash>
	bool HashMap<Key, Value, Hash>::operator!=(const HashMap<Key, Value, Hash>& other)
	{
		return false;
	}
}