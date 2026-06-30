// FUNC_NAME: Vector::pushBack
// Reconstructed from Ghidra at 0x0068ec60
// Member function of a dynamic array class (similar to std::vector)
// Fields: +0x00 data pointer (int*), +0x04 size (int), +0x08 capacity (int)

void __thiscall Vector::pushBack(int* dataPtr, int* valuePtr)
{
    int currentCapacity = dataPtr[2]; // capacity at +0x08
    int currentSize = dataPtr[1];     // size at +0x04

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
        // FUN_0068e500 is the internal resize/grow function
        resizeArray(newCapacity);
    }

    // Write the value into the array at the current end
    int* slot = (int*)(dataPtr[0] + currentSize * 4);
    dataPtr[1] = currentSize + 1; // increment size

    if (slot != nullptr)
    {
        *slot = *valuePtr;
    }
}