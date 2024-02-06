#include "LinkedList.h"

namespace All {
	template<typename Type>
	inline LinkedList<Type>::LinkedList(Allocator& allocator)
		: m_Allocator(&allocator), m_Size(0)
	{
	}

	template<typename Type>
	inline LinkedList<Type>::LinkedList(const LinkedList<Type>& other)
		: m_Allocator(other.m_Allocator), m_Size(other.m_Size), m_First(other.m_First), m_Last(other.m_Last)
	{
	}

	template<typename Type>
	inline LinkedList<Type>::LinkedList(LinkedList<Type>&& other)
		: m_Allocator(other.m_Allocator), m_Size(other.m_Size), m_First(other.m_First), m_Last(other.m_Last)
	{
		other.m_Size = 0;
		m_First = nullptr;
		m_Last = nullptr;
	}

	template<typename Type>
	inline LinkedList<Type>::~LinkedList()
	{
		for (TNode* n = m_First; n != nullptr; n = n->Next)
		{
			m_Allocator->Free(n);
		}
	}

	template<typename Type>
	inline void LinkedList<Type>::Add(Type&& element)
	{
		TNode* node = CreateNode(std::move(element), m_Last, nullptr);
		m_Last = node;

		if (m_First == nullptr)
			m_First = node;
	}

	template<typename Type>
	template<typename ...Args>
	inline void LinkedList<Type>::Add(Args&& ...args)
	{
		Add(Type(std::forward<Args>(args)...));
	}

	template<typename Type>
	void LinkedList<Type>::Insert(const uint64_t& index, Type&& element)
	{
		ALL_ASSERT(index <= m_Size && index >= 0);

		if (index == m_Size)
			LinkLast(element);
		else
			LinkBefore(element, FindNode(index));
	}

	template<typename Type>
	template<typename ...Args>
	void LinkedList<Type>::Insert(const uint64_t& index, Args&&... args)
	{
		Insert(index, std::forward<Args>(args)...);
	}

	template<typename Type>
	inline void LinkedList<Type>::Remove(const uint64_t& index)
	{
		TNode* node = FindNode(index);
		TNode* prev = node->Previous;
		TNode* next = node->Next;

		if (!prev)
		{
			next->Previous = nullptr;
			m_First = next;
		}
		else
		{
			prev = next;
		}

		if (!next)
		{
			prev->Next = nullptr;
			m_Last = prev;
		}
		else
		{
			m_Last = prev;
		}

		m_Allocator->Free<Type>(node);
	}

	template<typename Type>
	inline LinkedList<Type>::TNode* LinkedList<Type>::FindNode(const uint64_t& index)
	{
		ALL_ASSERT(index < m_Size);

		if (m_First == nullptr)
			return nullptr;

		TNode* node = m_First;
		for (uint64_t i = 1; i < index; i++)
		{
			node = node->Next;
		}

		return node;
	}

	template<typename Type>
	void LinkedList<Type>::LinkFirst(Type&& element)
	{
		TNode* next = m_First;

		TNode* first = CreateNode(std::move(element), nullptr, next);
		m_First = first;

		if (m_Last == nullptr)
			m_Last = m_First;
	}

	template<typename Type>
	void LinkedList<Type>::LinkLast(Type&& element)
	{
		TNode* prev = m_Last;

		TNode* last = CreateNode(std::move(element), prev, nullptr);
		m_Last = last;

		if (m_First == nullptr)
			m_First = m_Last;
	}

	template<typename Type>
	void LinkedList<Type>::LinkBefore(Type&& element, TNode* nodeToLinkBefore)
	{
		TNode* prev = nodeToLinkBefore->Previous;
		TNode* node = CreateNode(element, prev, nodeToLinkBefore);

		if (prev)
			prev->Next = node;
		else
			m_First = node;
		nodeToLinkBefore->Previous = node;
	}

	template<typename Type>
	void LinkedList<Type>::LinkAfter(Type&& element, TNode* nodeToLinkAfter)
	{
		TNode* next = nodeToLinkAfter->Next;
		TNode* node = CreateNode(element, nodeToLinkAfter, next);

		if (next)
			next->Previous = node;
		else
			m_Last = node;

		nodeToLinkAfter->Next = node;
	}

	template<typename Type>
	inline LinkedList<Type>::TNode* LinkedList<Type>::CreateNode(Type&& element, TNode* prev, TNode* next)
	{
		TNode* node = m_Allocator->AllocateInitialized<TNode>(std::move(element), prev, next);
		return node;
	}

	template<typename Type>
	inline LinkedList<Type>::Reference LinkedList<Type>::operator[](const uint64_t& index)
	{
		return FindNode(index);
	}

	template<typename Type>
	inline LinkedList<Type>::ConstRef LinkedList<Type>::operator[](const uint64_t& index) const
	{
		return LinkedList<Type>::operator[](index);
	}

	template<typename Type>
	inline void LinkedList<Type>::operator=(const LinkedList<Type>& other)
	{
		m_Allocator = other.m_Allocator;
		m_First = other.m_First;
		m_Last = other.m_Last;
		m_Size = other.m_Size;
	}

	template<typename Type>
	inline void LinkedList<Type>::operator=(LinkedList<Type>&& other)
	{
		m_Allocator = other.m_Allocator;
		m_First = other.m_First;
		m_Last = other.m_Last;
		m_Size = other.m_Size;

		other.m_First = nullptr;
		other.m_Last = nullptr;
		other.m_Size = 0;
	}

	template<typename Type>
	inline bool LinkedList<Type>::operator==(const LinkedList<Type>& other) const
	{
		return m_Allocator == other.m_Allocator && m_First == other.m_First && m_Last == other.m_Last && m_Size == other.m_Size;
	}

	template<typename Type>
	inline bool LinkedList<Type>::operator!=(const LinkedList<Type>& other) const
	{
		return !(*this == other);
	}
}