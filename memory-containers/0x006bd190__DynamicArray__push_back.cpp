// FUNC_NAME: DynamicArray::push_back

void __thiscall DynamicArray::push_back(int *thisPtr, int *elementPtr)
{
    int currentSize = thisPtr[1]; // +0x04: size
    int currentCapacity = thisPtr[2]; // +0x08: capacity
    int *dataPtr = (int *)thisPtr[0]; // +0x00: data pointer

    if (currentSize == currentCapacity) {
        int newCapacity;
        if (currentCapacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = currentCapacity * 2;
        }
        // Reallocate the array to newCapacity elements (each 4 bytes)
        DynamicArray::reserve(newCapacity); // calls FUN_006bca00
    }

    // Write the new element at the current size position
    if (dataPtr != nullptr) {
        dataPtr[thisPtr[1]] = *elementPtr;
    }
    // Increment size
    thisPtr[1] = thisPtr[1] + 1;
}