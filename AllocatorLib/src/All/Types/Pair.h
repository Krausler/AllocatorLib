#pragma once

#include "../Core.h"

namespace All {
	template<typename First, typename Second>
	struct Pair
	{
		Pair(First&& first, Second&& second)
			: m_First(std::move(first)), m_Second(std::move(second))
		{
		}
		Pair(const Pair<First, Second>& other)
			: m_First(other.m_First), m_Second(other.m_Second)
		{
		}

		First m_First;
		Second m_Second;
	};
}