// FUNC_NAME: DynamicArray::pushBack
// Function address: 0x00792820
// Role: Adds an element to a dynamic array, growing capacity if needed.
// Class layout (offsets relative to this):
//   +0x08: data pointer (array of 4-byte elements)
//   +0x0C: current size (number of elements)
//   +0x10: capacity (allocated slots)

void __thiscall DynamicArray::pushBack(int this, int element)
{
    int capacity = *(int *)(this + 0x10);
    int size = *(int *)(this + 0x0C);

    // If the array is full, grow the capacity
    if (size == capacity)
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
        // Reallocate internal buffer to new capacity (function at 0x006b1e10)
        FUN_006b1e10(newCapacity);
    }

    // Store the element at the current end position
    int *slot = (int *)(*(int *)(this + 0x08) + size * 4);
    *(int *)(this + 0x0C) = size + 1;  // increment size
    if (slot != (int *)0x0)
    {
        *slot = element;
    }
    return;
}