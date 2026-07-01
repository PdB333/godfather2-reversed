//FUNC_NAME: DynamicArray::push_back
// Address: 0x0092f240
// Role: Adds an element to a dynamic array, resizing if necessary.
// Structure offsets: +0x4c = m_pData (pointer to array of 4-byte elements), +0x50 = m_count (current number of elements), +0x54 = m_capacity (allocated capacity)

void __thiscall DynamicArray::push_back(int thisPtr, undefined4 element)
{
    int capacity = *(int *)(thisPtr + 0x54);
    int count = *(int *)(thisPtr + 0x50);

    if (count == capacity)
    {
        int newCapacity;
        if (capacity == 0)
        {
            newCapacity = 1;
        }
        else
        {
            newCapacity = capacity * 2;
        }
        // Reallocate the internal array to newCapacity (function at 0x92db60)
        FUN_0092db60(newCapacity);
    }

    // Get pointer to the next slot
    undefined4 *slot = (undefined4 *)(*(int *)(thisPtr + 0x4c) + count * 4);
    // Increment count
    *(int *)(thisPtr + 0x50) = count + 1;

    if (slot != (undefined4 *)0x0)
    {
        *slot = element;
    }
}