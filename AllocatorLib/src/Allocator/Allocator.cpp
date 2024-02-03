#include "Allocator.h"

#include "Types/ArrayList.h"

namespace All {
	inline Allocator::Allocator(const AllocatorSpecification& spec)
		: m_Spec(spec)
	{
		ALL_ASSERT(spec.ResizeIncrease > 0.0f, "ResizeIncrease must be bigger then 0!");
		ALL_ASSERT(spec.Size > 0, "Size must be bigger then 0!");

		m_Buffer = (char*)::operator new(spec.Size);
		m_AllocData = { spec.Size, spec.Size, 0, 0 };
		m_FreedBlocks = AllocateInitialized<ArrayList<Block>>(*this);

		ALL_LOG_FORMAT_INFO("Allocated 'Heap' of buffer size %zu.", m_AllocData.Capacity);
	}

	inline Allocator::~Allocator()
	{
		::operator delete(m_Buffer);
	}

	inline void* Allocator::Allocate(const size_t& size)
	{
		// Checking whether there is enough space for this allocation
		ALL_ASSERT(m_AllocData.Capacity - m_AllocData.Pointer >= size);

		// Handling allocations from freed blocks
		void* p = FreedBlockAllocation(size);

		if (!p)
		{
			p = m_Buffer + m_AllocData.Pointer;
			m_AllocData.Pointer += size;
		}

		m_AllocData.FreeSpace -= size;
		m_AllocData.AllocationCount++;
		ALL_LOG_FORMAT_INFO("Allocated memory of size %zu.", size);

		return p;
	}

	inline void Allocator::Free(void* ptr, const size_t& size)
	{
		int64_t offsetInBuffer = (char*)ptr - m_Buffer;
		ALL_ASSERT(offsetInBuffer <= m_AllocData.Pointer && offsetInBuffer >= 0);

		if (offsetInBuffer + size < m_AllocData.Pointer)
		{
			m_FreedBlocks->Add({ ptr, size });
			TryMerge(m_FreedBlocks->GetSize() - 1);
		}
		else
		{
			m_AllocData.Pointer -= size;
		}

		m_AllocData.AllocationCount--;
		m_AllocData.FreeSpace += size;
		ALL_LOG_FORMAT_INFO("Deallocated memory of size %zu.", size);
	}

	inline void Allocator::Resize()
	{
		size_t newCapacity = m_AllocData.Capacity * m_Spec.ResizeIncrease;
		char* newBuffer = new char[newCapacity];

		memcpy(newBuffer, m_Buffer, m_AllocData.Capacity);

		delete[] m_Buffer;
		m_Buffer = newBuffer;
		newBuffer = nullptr;

		m_AllocData.FreeSpace += newCapacity - m_AllocData.Capacity;
		m_AllocData.Capacity = newCapacity;
	}

	inline void* Allocator::FreedBlockAllocation(const size_t& size)
	{
		if (m_AllocData.AllocationCount < 2)
			return nullptr;

		if (m_FreedBlocks->GetSize() == 0)
			return nullptr;

		for (uint32_t i = 0; i < m_FreedBlocks->GetSize(); i++)
		{
			void* result = SimpleFreedBlockAllocation(i, size);
			if (result)
				return result;
		}
		return nullptr;
	}

	inline void* Allocator::SimpleFreedBlockAllocation(const uint64_t& blockIndex, const size_t& size)
	{
		ALL_ASSERT(blockIndex < m_FreedBlocks->GetSize());

		Block& block = m_FreedBlocks->operator[](blockIndex);
		int32_t sizeDiffrence = block.Size - size;
		if (sizeDiffrence == 0)
		{
			void* p = block.Pointer;
			m_FreedBlocks->Remove(blockIndex);
			return p;
		}
		else if (sizeDiffrence > 0)
		{
			void* p = block.Pointer;
			block.Pointer = (char*)block.Pointer + size;
			block.Size = sizeDiffrence;
			return p;
		}
		return nullptr;
	}

	inline void Allocator::TryMerge(uint64_t blockIndex)
	{
		ALL_ASSERT(blockIndex < m_FreedBlocks->GetSize());
		Block& block = m_FreedBlocks->operator[](blockIndex);

		for (int i = 0; i < m_FreedBlocks->GetSize(); i++)
		{
			if (i == blockIndex)
				continue;

			Block& block2 = m_FreedBlocks->operator[](i);

			if (((char*)block2.Pointer + block2.Size) == block.Pointer)
			{
				block.Pointer = block2.Pointer;
				block.Size += block2.Size;
				m_FreedBlocks->Remove(i);
			}
			else if (((char*)block.Pointer + block.Size) == block2.Pointer)
			{
				block.Size += block2.Size;
				m_FreedBlocks->Remove(i);
			}
		}
	}
}