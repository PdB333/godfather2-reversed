// FUNC_NAME: DynamicArray::pushBack
// Address: 0x009387e0
// Role: Adds a new element (size 0x10) to a dynamic array, growing if necessary.
// Structure offsets: +0x00 = m_pData (pointer to element array), +0x04 = m_size (current count), +0x08 = m_capacity (allocated slots)

void __fastcall DynamicArray::pushBack(int *thisPtr)
{
    int oldSize = thisPtr[1];          // m_size
    int capacity = thisPtr[2];         // m_capacity

    // Grow if full
    if (oldSize == capacity) {
        int newCapacity;
        if (capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = capacity * 2;
        }
        // Reallocate array to new capacity (FUN_00407880 likely allocates memory)
        growArray(newCapacity);
    }

    int newSize = oldSize + 1;
    thisPtr[1] = newSize;              // m_size++

    // Check if the slot for the new element is valid (non-null pointer)
    // The element size is 0x10 bytes, so address = m_pData + oldSize * 0x10
    if (thisPtr[0] + oldSize * 0x10 != 0) {
        // If valid, call a handler (FUN_004d3b50) – possibly debug/log or error?
        onAddFailed();
        return;
    }
    // Otherwise, the slot is considered empty and the add succeeds (no further action)
    return;
}