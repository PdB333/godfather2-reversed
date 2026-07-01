// FUNC_NAME: GrowingArray::add
// Function address: 0x0091a6a0
// Role: Adds an element to a dynamically growing array (vector-like container).
// Offsets: +0x4c = data pointer, +0x50 = size, +0x54 = capacity
// Calls FUN_00917930 which likely reallocates the internal buffer when capacity is full.

void __thiscall GrowingArray::add(int thisPtr, unsigned int element)
{
    int capacity = *(int *)(thisPtr + 0x54);
    int size = *(int *)(thisPtr + 0x50);

    // If size equals capacity, grow the array
    if (size == capacity)
    {
        int newCapacity;
        if (capacity == 0)
            newCapacity = 1;
        else
            newCapacity = capacity * 2;

        // Reallocate internal buffer to new capacity (FUN_00917930)
        resizeBuffer(newCapacity);
    }

    // Get pointer to the current end of the array
    unsigned int *data = *(unsigned int **)(thisPtr + 0x4c);
    unsigned int *slot = data + size; // offset by current size

    // Increment size before storing (post-increment in original assembly)
    *(int *)(thisPtr + 0x50) = size + 1;

    // Store element if slot is valid (defensive)
    if (slot != nullptr)
        *slot = element;
}