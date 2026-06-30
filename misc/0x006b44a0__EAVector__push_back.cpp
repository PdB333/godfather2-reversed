// FUNC_NAME: EAVector::push_back
// Function address: 0x006b44a0
// Role: Appends a 4-byte value to a dynamic array, growing capacity if needed.
// Structure: this[0] = buffer pointer, this[1] = size, this[2] = capacity

void __thiscall EAVector::push_back(int* thisPtr, undefined4* value)
{
    int currentSize = thisPtr[1];
    int capacity = thisPtr[2];

    if (currentSize == capacity)
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
        // Reallocate to accommodate new capacity (function at 0x006b1e10)
        reallocate(newCapacity);
    }

    // Write value at the end of the buffer
    undefined4* bufferEnd = (undefined4*)(thisPtr[0] + currentSize * 4);
    thisPtr[1] = currentSize + 1;
    if (bufferEnd != (undefined4*)0x0)
    {
        *bufferEnd = *value;
    }
}