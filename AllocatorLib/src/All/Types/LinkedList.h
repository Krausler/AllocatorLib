#pragma once

#include "../Core.h"
#include "../Allocator.h"

#include "LinkedListIterator.h"
#include "Node.h"

namespace All {
	template<typename Type>
	class LinkedList
	{
	private:
		using TNode = Node<Type>;

		using Reference = Type&;
		using ConstRef = const Reference;

		using Iterator = LinkedListIterator<Type>;
	public:
		LinkedList(Allocator& allocator);
		LinkedList(const LinkedList<Type>& other);
		LinkedList(LinkedList<Type>&& other);
		~LinkedList();

		template<typename... Args>
		void Add(Args&&... args);
		void Add(Type&& element);

		template<typename... Args>
		void Insert(const uint64_t& index, Args&&... args);
		void Insert(const uint64_t& index, Type&& element);

		void Remove(const uint64_t& index);

		TNode* FindNode(const uint64_t& index);

		const size_t& GetSize() const { return m_Size; }

		Iterator begin() const { return Iterator(m_First); }
		Iterator end() const { return Iterator(m_Last); }
		const Iterator cbegin() const { return begin(); }
		const Iterator cend() const { return end(); }

		Reference operator[](const uint64_t& index);
		ConstRef operator[](const uint64_t& index) const;
		void operator=(const LinkedList<Type>& other);
		void operator=(LinkedList<Type>&& other);
		bool operator==(const LinkedList<Type>& other) const;
		bool operator!=(const LinkedList<Type>& other) const;

	private:
		TNode* CreateNode(Type&& element, TNode* prev, TNode* next);

		void LinkFirst(Type&& element);
		void LinkLast(Type&& element);
		void LinkBefore(Type&& element, TNode* nodeToLinkBefore);
		void LinkAfter(Type&& element, TNode* nodeToLinkAfter);

	private:
		Allocator* m_Allocator;

		TNode* m_First = nullptr;
		TNode* m_Last = nullptr;

		size_t m_Size;
	};
}

#include "LinkedList.cpp"