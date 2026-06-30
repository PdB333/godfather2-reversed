// FUNC_NAME: DynamicArray::reserve
// Address: 0x00412af0
// Role: Reserves capacity for a dynamic array of 8-byte elements (pairs).
// Adapts the internal buffer to fit at least newCapacity elements, copying existing data.

#include <cstdint>

// Forward declarations for memory management functions (EA EARS allocator)
extern void* AllocateMemory(size_t size);
extern void  FreeMemory(void* ptr);

// Element type stored in the array: a pair of 32-bit values (8 bytes total)
struct Pair {
    int32_t first;   // +0x0
    int32_t second;  // +0x4
};

// Dynamic array class maintaining a flat buffer of Pairs
class DynamicArray {
public:
    // +0x00: pointer to the allocated buffer
    Pair*   mData;
    // +0x04: number of elements currently stored
    uint32_t mSize;
    // +0x08: capacity of the buffer (number of elements it can hold)
    uint32_t mCapacity;

    // Reserves internal storage so that at least newCapacity elements can be stored.
    // If the current capacity is already sufficient, nothing is done.
    void reserve(uint32_t newCapacity);
};

void DynamicArray::reserve(uint32_t newCapacity)
{
    // Only reallocate if requested capacity is larger than current capacity
    if (mCapacity < newCapacity)
    {
        // Allocate new buffer (each element is 8 bytes: sizeof(Pair))
        Pair* newData = (Pair*)AllocateMemory(newCapacity * sizeof(Pair));

        // If old buffer exists, copy existing elements to new buffer
        if (mData != nullptr)
        {
            for (uint32_t i = 0; i < mSize; ++i)
            {
                // Copy each element (8-byte structure) piecewise
                newData[i].first  = mData[i].first;
                newData[i].second = mData[i].second;
            }
            // Free the old buffer
            FreeMemory(mData);
        }

        // Update pointer and capacity
        mData     = newData;
        mCapacity = newCapacity;
    }
}