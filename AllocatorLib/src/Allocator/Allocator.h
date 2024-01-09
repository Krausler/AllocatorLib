#pragma once

#include <stdint.h>
#include <iostream>
#include <functional>
#include <string>

#include "Allocator/Types/List.h"

namespace All {
	const uint32_t FREEDBLOCK_LIST_SIZE = 1024;

	struct AllocatorSpecification
	{
		size_t Size;
		size_t FreedMemArraySize;
		float ResizeIncrease;

		static AllocatorSpecification Default()
		{
			AllocatorSpecification spec = {};
			spec.Size = 1024 * 1024 * 5;
			spec.FreedMemArraySize = 30;
			spec.ResizeIncrease = 1.5f;

			return spec;
		}
	};

	class Allocator
	{
	private:
		struct FreedBlock
		{
			void* Pointer;
			size_t Size;
		};

		struct AllocatedBlock
		{
			void* Pointer;
			size_t Size;
		};

		struct AllocationData
		{
			size_t Capacity;
			size_t FreeSpace;

			size_t AllocationCount;
			uint64_t Pointer;
		};
	public:
		Allocator(const AllocatorSpecification& spec = AllocatorSpecification::Default());
		~Allocator();

		void* Allocate(const size_t& size);
		template<typename T>
		T* Allocate()
		{
			return (T*)Allocate(sizeof(T));
		}
		template<typename T>
		T* Allocate(const size_t& count)
		{
			return (T*)Allocate(count * sizeof(T));
		}

		template<typename T, typename... Args>
		T* AllocateInitialized(Args&&... args)
		{
			T* t = Allocate<T>();
			t = new (t) T(std::forward<Args>(args)...);
			return t;
		}

		void Free(void* ptr, const size_t& size);
		template<typename T>
		void Free(T* ptr)
		{
			Free(ptr, sizeof(T));
		}

		void Resize();
	private:
		void* FreedBlockAllocation(const size_t& size);
		void* SimpleFreedBlockAllocation(const uint32_t& blockIndex, const size_t& size);
	private:
		char* m_Buffer;
		List<FreedBlock> m_FreedBlocks;

		AllocationData m_AllocData;
		AllocatorSpecification m_Spec;
	};
}
