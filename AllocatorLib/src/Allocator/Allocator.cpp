#include "Allocator.h"

#include "Allocator/Core.h"
#include "Allocator/Types/List.h"

#include <array>

namespace All {
	Allocator::Allocator(const AllocatorSpecification& spec)
		: m_Buffer((char*)::operator new(spec.Size)), m_Spec(spec), m_AllocData({ spec.Size, spec.Size, 0, 0 }), m_FreedBlocks(this)
	{
		ALL_ASSERT(spec.ResizeIncrease > 0.0f, "ResizeIncrease must be bigger then 0!");
		ALL_ASSERT(spec.Size > 0, "Size must be bigger then 0!");

		ALL_LOG_FORMAT_INFO("Allocated 'Heap' of buffer size %zu.", m_AllocData.Capacity);
	}

	Allocator::~Allocator()
	{
		::operator delete(m_Buffer);
	}

	void* Allocator::Allocate(const size_t& size)
	{
		// Checking whether there is enough space for this allocation
		if (m_AllocData.FreeSpace < size)
			Resize();

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

	void Allocator::Free(void* ptr, const size_t& size)
	{
		uint64_t offsetInBuffer = (char*)ptr - m_Buffer;

		if (offsetInBuffer < m_AllocData.Pointer)
		{
			m_FreedBlocks.Add({ ptr, size });
		}
		else
		{
			m_AllocData.Pointer -= size;
		}

		m_AllocData.AllocationCount--;
		m_AllocData.FreeSpace += size;
		ALL_LOG_FORMAT_INFO("Deallocated memory of size %zu.", size);
	}

	void Allocator::Resize()
	{
		size_t newCapacity = m_AllocData.Capacity * m_Spec.ResizeIncrease;
		char* newBuffer = new char[newCapacity];

		std::memcpy(newBuffer, m_Buffer, m_AllocData.Capacity);

		delete[] m_Buffer;
		m_Buffer = newBuffer;
		newBuffer = nullptr;

		m_AllocData.FreeSpace += newCapacity - m_AllocData.Capacity;
		m_AllocData.Capacity = newCapacity;
	}

	void* Allocator::FreedBlockAllocation(const size_t& size)
	{
		if (m_FreedBlocks.GetSize() == 0)
			return nullptr;

		for (uint32_t i = 0; i < m_FreedBlocks.GetSize(); i++)
		{
			void* result = SimpleFreedBlockAllocation(i, size);
			if (result)
				return result;

			if (m_FreedBlocks.GetSize() > 1)
			{
				FreedBlock& block = m_FreedBlocks[i];
				FreedBlock& previousBlock = m_FreedBlocks[i - 1];
				if ((char*)previousBlock.Pointer + previousBlock.Size == block.Pointer && previousBlock.Size + block.Size >= size)
				{
					previousBlock.Pointer = previousBlock.Pointer;
					previousBlock.Size = previousBlock.Size + block.Size;

					m_FreedBlocks.Remove(i);

					return SimpleFreedBlockAllocation(i - 1, size);
				}
			}
		}
		return nullptr;
	}

	void* Allocator::SimpleFreedBlockAllocation(const uint32_t& blockIndex, const size_t& size)
	{
		FreedBlock& block = m_FreedBlocks[blockIndex];
		int32_t sizeDiffrence = block.Size - size;
		if (sizeDiffrence == 0)
		{
			void* p = block.Pointer;
			m_FreedBlocks.Remove(blockIndex);
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
}