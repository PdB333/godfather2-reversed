// FUNC_NAME: InternalVector::insertElements
// Address: 0x005da1d0
// This function inserts `count` elements of size 0x28 (40 bytes) at the position `insertPos`
// inside a dynamic array (vector) managed by the object at `this` (ESI).
// The vector layout (offsets from this in bytes):
//   +0x08 : mData       (pointer to start of allocated memory)
//   +0x0c : mEnd        (pointer to one past the last constructed element)
//   +0x10 : mCapacityEnd (pointer to one past the end of allocated storage)
// Element size = 0x28, capacity = (mCapacityEnd - mData) / 0x28, size = (mEnd - mData) / 0x28.
// Growth factor is 1.5x, capped at kMaxElements (0x6666666), which likely corresponds to
// a maximum number of elements (e.g., 0x7FFFFFFF / 40, but here a hard-coded limit).

#include <cstdint>

// Forward declarations of callees (likely internal helpers)
void* growAndReallocate(void* data, uint32_t newCapacity);           // FUN_005d9ed0
uint32_t computeNewCapacity(uint32_t current, uint32_t required);    // FUN_005d9a60
void* allocateMemory(uint32_t sizeInBytes);                          // FUN_005da050
void* memcpyElements(void* dest, const void* src, uint32_t count);   // FUN_005dab00 (dest, src, count)
void memmoveElements(void* dest, const void* src, uint32_t count);   // FUN_005da830 (like memmove with alignment)
void* shiftElementsRight(void* from, uint32_t deltaBytes);           // FUN_005da6d0 (make room by moving elements after insertion point)
void destructElements(void* ptr, uint32_t count);                    // FUN_005da8a0 (destroy elements at ptr)
void shiftElementsLeft(void* dest, const void* src, uint32_t count); // FUN_005da710 (move elements left)

static const uint32_t kElementSize = 0x28;
static const uint32_t kMaxElements = 0x6666666; // Max number of elements

void __thiscall InternalVector::insertElements(uint32_t count, void* insertPos)
{
    // Extract vector pointers
    uint8_t* mData = (uint8_t*)this[2];          // +0x08
    uint8_t* mEnd = (uint8_t*)this[3];           // +0x0c
    uint8_t* mCapacityEnd = (uint8_t*)this[4];   // +0x10

    // Current capacity in elements
    uint32_t capacity = (mCapacityEnd - mData) / kElementSize;
    // Current size in elements
    uint32_t size = (mEnd - mData) / kElementSize;

    if (count == 0)
        return;

    // Check if reallocation is needed
    if (capacity == 0)
    {
        // If no memory allocated, size and capacity are both 0, but size should be 0.
        // This branch handles the case where the vector is empty.
    }

    // Compute the number of elements before the insertPos
    uint32_t indexBeforeInsert = (insertPos - mData) / kElementSize;

    if (count > capacity - size)
    {
        // Not enough capacity, must reallocate
        // Check if the new total size would exceed the absolute maximum
        uint32_t newTotal = size + count;
        if (kMaxElements - indexBeforeInsert < count)
        {
            // Exceeds max, abort (likely throws or returns)
            growAndReallocate(nullptr, 0); // placeholder for error handling
            return;
        }

        // Compute new capacity (grow by 1.5x, bounded by kMaxElements)
        uint32_t newCapacity = capacity;
        if (kMaxElements - (newCapacity >> 1) < newCapacity)
            newCapacity = 0;
        else
            newCapacity = newCapacity + (newCapacity >> 1);

        // Ensure new capacity is at least the required size
        if (newCapacity < indexBeforeInsert + count)
        {
            // If 1.5x growth still insufficient, force to required size
            newCapacity = indexBeforeInsert + count;
        }

        // Allocate new memory
        uint8_t* newData = (uint8_t*)allocateMemory(newCapacity * kElementSize);

        // Copy old data to new memory (before insertion point)
        uint8_t* dest = newData;
        // Copy elements before insertPos
        memcpyElements(dest, mData, indexBeforeInsert);
        dest += indexBeforeInsert * kElementSize;

        // Copy the source data (insertPos points to the source array? Actually here insertPos is used as source)
        // In the original code, after reallocation they call FUN_005dab00(insertPos, count, count) which likely
        // copies 'count' elements from address 'insertPos' into the new buffer.
        // This implies that 'insertPos' points to the source data to insert when reallocation occurs.
        // This is inconsistent with the normal case where insertPos is a position inside the vector.
        // For reconstruction, we assume that after reallocation the source data is passed via insertPos.
        memcpyElements(dest, insertPos, count);
        dest += count * kElementSize;

        // Copy elements after insertion point (from old data)
        uint32_t afterCount = size - indexBeforeInsert;
        memcpyElements(dest, mData + indexBeforeInsert * kElementSize, afterCount);

        // Destroy old elements (if destructor needed)
        destructElements(mData, size);

        // Update vector pointers
        this[2] = newData;
        this[3] = newData + (size + count) * kElementSize;
        this[4] = newData + newCapacity * kElementSize;
        return;
    }

    // No reallocation needed; we have space between mEnd and mCapacityEnd
    // Check if there is enough empty space after the insertion point (i.e., between insertPos and mCapacityEnd)
    uint32_t spaceAfterInsert = (mCapacityEnd - insertPos) / kElementSize;
    if (spaceAfterInsert < count)
    {
        // Not enough space after insertPos, need to make room by moving elements to the end of allocated storage
        // Shift elements after the insertion point to the right by the required amount
        uint8_t* shiftStart = mEnd;
        uint32_t shiftDelta = count * kElementSize;
        uint8_t* newEnd = shiftStart + shiftDelta;
        // Move the elements from insertPos to mEnd to a new location (make gap)
        shiftElementsRight(shiftStart, (uint8_t*)insertPos + shiftDelta); // actually this may be memmove
        // Copy the new elements into the gap
        memmoveElements((uint8_t*)insertPos, shiftStart, count);
        // Update mEnd
        mEnd = newEnd;
        // Destroy the source data? (destroyElements(insertPos, count) called)
        destructElements(insertPos, count);
    }
    else
    {
        // There is enough space after insertPos; shift elements after insertPos to the right by 'count' positions
        uint8_t* gapStart = (uint8_t*)insertPos + count * kElementSize;
        uint32_t moveCount = (mEnd - (uint8_t*)insertPos) / kElementSize;
        shiftElementsLeft(gapStart, (uint8_t*)insertPos, moveCount);
        // Now insert new elements into the gap (source is assumed to be at 'insertPos' but that's now overwritten)
        // In the original code, after shifting they call destructElements(insertPos) then something else.
        // This likely means the source data is elsewhere; we'll copy from a temporary.
        // For simplicity, we assume new elements are constructed in place.
        // (Actual game code would construct or copy from a source array not shown.)
        // Update mEnd
        mEnd += count * kElementSize;
        // Destroy source (if needed)
        destructElements(insertPos, count);
    }

    // Update vector's end pointer (already done in branches)
    this[3] = mEnd;
}