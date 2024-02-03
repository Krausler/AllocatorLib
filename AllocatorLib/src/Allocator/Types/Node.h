#pragma once

namespace All {
	template<typename Type>
	struct Node
	{
		Node(Type&& element, Node* prev, Node* next)
			: Element(std::move(element)), Previous(prev), Next(next)
		{
		}

		Type Element;

		Node* Previous;
		Node* Next;
	};
}