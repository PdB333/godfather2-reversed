// FUNC_NAME: DynamicArray::reserve

struct DynamicArray
{
    void*        data;       // +0x00
    unsigned int size;       // +0x04
    unsigned int capacity;   // +0x08
};

void __thiscall DynamicArray::reserve(unsigned int newCapacity)
{
    // Only grow if new capacity is larger than current capacity
    if (capacity < newCapacity)
    {
        // Allocate new block: each element is 4 bytes
        void* newData = heapAllocate(newCapacity * 4);  // FUN_009c8e80

        // Copy existing elements if data was previously allocated
        if (data != nullptr)
        {
            unsigned int count = size;
            // Copy element by element (4 bytes each)
            // Using a loop: for (unsigned int i = 0; i < count; ++i)
            //   ((unsigned int*)newData)[i] = ((unsigned int*)data)[i];
            // But the decompiled code shows pointer arithmetic with puVar3
            // Equivalent to memcpy(newData, data, count * 4);
            // We'll write the explicit loop as in the original
            unsigned int i = 0;
            unsigned int* src = (unsigned int*)data;
            unsigned int* dst = (unsigned int*)newData;
            if (src != nullptr)
            {
                do
                {
                    if (dst != nullptr)
                        *dst = *src;
                    src++;
                    dst++;
                    i++;
                } while (i < size);
            }
            // Free old block
            heapFree(data);  // FUN_009c8f10
        }
        // Update pointers and capacity
        data = newData;
        capacity = newCapacity;
    }
}