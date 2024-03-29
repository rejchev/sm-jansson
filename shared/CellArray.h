#ifndef _INCLUDE_SOURCEMOD_CELLARRAY_1H_
#define _INCLUDE_SOURCEMOD_CELLARRAY_1H_

#include <stdlib.h>
#include <string.h>
#include <sp_vm_types.h>
#include <ICellArray.h>
#include <amtl/am-bits.h>

class CellArray : public SourceMod::ICellArray
{
public:
    CellArray(size_t blocksize) : m_Data(nullptr), m_BlockSize(blocksize), m_AllocSize(0), m_Size(0)
	{
	}

	~CellArray()
	{
		free(m_Data);
	}

	/**
	* @brief Creates a cell array object.
	*
	* @param blocksize  The number of cells each member of the array can
	*                   hold.  For example, 32 cells is equivalent to:
	*                   new Array[X][32]
	* @return			A new ICellArray object.
	*/
	static ICellArray *New(size_t blocksize)
	{
		return new CellArray(blocksize);
	}

	/**
	* @brief Releases a cell array's resources.
	*
	* @param pack		An ICellArray object to release.
	*/
	static void Free(ICellArray *arr)
	{
		delete arr;
	}

	// ICellArray
public:
	size_t size() const
	{
		return m_Size;
	}

	cell_t *push()
	{
		if (!GrowIfNeeded(1))
		{
			return nullptr;
		}
		cell_t *arr = &m_Data[m_Size * m_BlockSize];
		m_Size++;
		return arr;
	}

	cell_t *at(size_t b) const
	{
		return &m_Data[b * m_BlockSize];
	}

	size_t blocksize() const
	{
		return m_BlockSize;
	}

	void clear()
	{
		m_Size = 0;
	}

	bool swap(size_t item1, size_t item2)
	{
		/* Make sure there is extra space available */
		if (!GrowIfNeeded(1))
		{
			return false;
		}

		cell_t *pri = at(item1);
		cell_t *alt = at(item2);

		/* Get our temporary array 1 after the limit */
		cell_t *temp = &m_Data[m_Size * m_BlockSize];

		memcpy(temp, pri, sizeof(cell_t) * m_BlockSize);
		memcpy(pri, alt, sizeof(cell_t) * m_BlockSize);
		memcpy(alt, temp, sizeof(cell_t) * m_BlockSize);

		return true;
	}

	void remove(size_t index)
	{
		/* If we're at the end, take the easy way out */
		if (index == m_Size - 1)
		{
			m_Size--;
			return;
		}

		/* Otherwise, it's time to move stuff! */
		size_t remaining_indexes = (m_Size - 1) - index;
		cell_t *src = at(index + 1);
		cell_t *dest = at(index);
		memmove(dest, src, sizeof(cell_t) * m_BlockSize * remaining_indexes);

		m_Size--;
	}

	cell_t *insert_at(size_t index)
	{
		/* Make sure it'll fit */
		if (!GrowIfNeeded(1))
		{
			return NULL;
		}

		/* move everything up */
		cell_t *src = at(index);
		cell_t *dst = at(index + 1);
		memmove(dst, src, sizeof(cell_t) * m_BlockSize * (m_Size-index));

		m_Size++;

		return src;
	}

	bool resize(size_t count)
	{
		if (count <= m_Size)
		{
			m_Size = count;
			return true;
		}

		if (!GrowIfNeeded(count - m_Size))
		{
			return false;
		}

		m_Size = count;
		return true;
	}

	ICellArray *clone()
	{
        CellArray *array = new CellArray(m_BlockSize);
		array->m_AllocSize = m_AllocSize;
		array->m_Size = m_Size;
		array->m_Data = (cell_t *)malloc(sizeof(cell_t) * m_BlockSize * m_AllocSize);
		if (!array->m_Data)
		{
			delete array;
			return NULL;
		}
		
		memcpy(array->m_Data, m_Data, sizeof(cell_t) * m_BlockSize * m_Size);
		return array;
	}

	cell_t *base()
	{
		return m_Data;
	}

	size_t mem_usage()
	{
		return m_AllocSize * m_BlockSize * sizeof(cell_t);
	}

private:
	bool GrowIfNeeded(size_t count)
	{
		/* Shortcut out if we can store this */
		if (m_Size + count <= m_AllocSize)
		{
			return true;
		}
		size_t newAllocSize = m_AllocSize;
		/* Set a base allocation size of 8 items */
		if (!newAllocSize)
		{
			newAllocSize = 8;
		}
		if (!ke::IsUintPtrAddSafe(m_Size, count))
		{
			return false;
		}
		/* If it's not enough, keep doubling */
		while (m_Size + count > newAllocSize)
		{
			if (!ke::IsUintPtrMultiplySafe(newAllocSize, 2))
			{
				return false;
			}
			newAllocSize *= 2;
		}
		/* finally, allocate the new block */
		cell_t *data = static_cast<cell_t*>(realloc(m_Data, sizeof(cell_t) * m_BlockSize * newAllocSize));
		/* Update state if allocation was successful */
		if (data)
		{
			m_AllocSize = newAllocSize;
			m_Data = data;
		}
		return (data != nullptr);
	}
private:
	cell_t *m_Data;
	size_t m_BlockSize;
	size_t m_AllocSize;
	size_t m_Size;
};

#endif /* _INCLUDE_SOURCEMOD_CELLARRAY_H_ */

