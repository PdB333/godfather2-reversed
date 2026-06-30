// FUNC_NAME: Vector::pushBack
// Function address: 0x005f7250
// Role: Inserts an element at the end of a dynamic array (vector) with automatic growth.
// The class structure is assumed: this+0x4 = data pointer (int*), this+0x8 = current size, this+0xC = capacity.
// The return value is a packed combination of the new size's high 24 bits and a success flag (low byte = 1).

uint32_t __thiscall Vector::pushBack(uint32_t value)
{
    int currentSize = *(int *)(this + 0x8);       // size
    int currentCapacity = *(int *)(this + 0xC);   // capacity

    if (currentSize == currentCapacity)
    {
        int newCapacity;
        if (currentCapacity == 0)
        {
            newCapacity = 1;
        }
        else
        {
            newCapacity = currentCapacity * 2;
        }
        // grow is an internal function that reallocates the data array (e.g., FUN_005fa9a0)
        grow(newCapacity);
    }

    // Store the new element at the end of the array
    int *dataPtr = *(int **)(this + 0x4);
    dataPtr[currentSize] = value;

    // Increment size
    int newSize = currentSize + 1;
    *(int *)(this + 0x8) = newSize;

    // Return packed value: ((uint32_t)newSize & 0xFFFFFF00) | 0x01
    return ( (uint32_t)newSize & 0xFFFFFF00 ) | 0x01;
}