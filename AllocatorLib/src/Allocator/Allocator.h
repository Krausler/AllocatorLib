#pragma once

#include <stdint.h>
#include <iostream>
#include <functional>
#include <string>
#include <vector>

namespace All {
	template<typename Type>
	class List;

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
		struct Block
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

		struct BlockList
		{
			Allocator::Block* Data;
			uint64_t Size;
			uint64_t Capacity;

			bool Add(Block&& block)
			{
				Data[Size] = block;
			}
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

		const size_t& GetAllocationCount() { return m_AllocData.AllocationCount; }
		const size_t& GetCapacity() { return m_AllocData.Capacity; }
		const size_t& GetFreeSpace() { return m_AllocData.FreeSpace; }
		const uint64_t& GetHeapInternalPointer() { return m_AllocData.Pointer; }
	private:
		void* FreedBlockAllocation(const size_t& size);
		void* SimpleFreedBlockAllocation(const uint64_t& blockIndex, const size_t& size);
		void TryMerge(uint64_t blockIndex);
	private:
		char* m_Buffer;
		List<Block>* m_FreedBlocks;

		AllocationData m_AllocData;
		AllocatorSpecification m_Spec;
	};
}
