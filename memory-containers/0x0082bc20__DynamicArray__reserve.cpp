// FUNC_NAME: DynamicArray::reserve
// Address: 0x0082bc20
// Role: Reallocate internal storage to a new capacity, copying existing elements.

// Struct representing a dynamic array of 4-byte elements (e.g., int32).
struct DynamicArray {
    int* data;       // +0x00: pointer to allocated array
    int  size;       // +0x04: number of elements currently stored
    int  capacity;   // +0x08: allocated capacity (in elements)
};

// Custom memory functions (from the game's allocator).
void* GameMemoryAllocate(uint size);
void  GameMemoryFree(void* ptr);

void __thiscall DynamicArray::reserve(uint newCapacity)
{
    if ((uint)capacity < newCapacity)
    {
        // Allocate new buffer (size in bytes = newCapacity * sizeof(int))
        undefined4* newData = (undefined4*)GameMemoryAllocate(newCapacity * 4);

        if (data != nullptr)
        {
            uint i = 0;
            undefined4* dst = newData;
            if (size != 0)
            {
                do {
                    if (dst != nullptr) {   // safety check (newData could be null?)
                        *dst = *(undefined4*)(data + i);
                    }
                    i++;
                    dst++;
                } while (i < (uint)size);
            }
            // Free old array
            GameMemoryFree(data);
        }

        // Update pointer and capacity
        data = (int*)newData;
        capacity = newCapacity;
    }
}