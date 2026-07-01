// FUNC_NAME: DynamicArray::pushBack
// Function address: 0x00921510
// Pushes an 8-byte element (two 32-bit values) into a dynamic array.
// The array structure: [0] = data pointer, [1] = current size (count of elements), [2] = capacity (max elements)
// Growth: if size == capacity, double capacity (or set to 1 if capacity was 0).

typedef unsigned int uint32;
typedef int int32;

// External resize function (likely reallocates the data buffer)
void DynamicArray_resize(uint32 newCapacity); // Address: 0x00920b90

void __thiscall DynamicArray::pushBack(int* thisPtr, uint32* element)
{
    uint32 size = thisPtr[1];      // +0x04: current element count
    uint32 capacity = thisPtr[2];  // +0x08: current capacity

    if (size == capacity)
    {
        if (capacity == 0)
            capacity = 1;
        else
            capacity *= 2;

        DynamicArray_resize(capacity);
    }

    uint32* newElementPtr = (uint32*)(thisPtr[0] + size * 8);
    thisPtr[1] = size + 1;

    if (newElementPtr != nullptr)
    {
        newElementPtr[0] = element[0];
        newElementPtr[1] = element[1];
    }

    return;
}