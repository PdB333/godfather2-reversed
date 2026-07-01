// FUNC_NAME: Vector::pushBack

void __thiscall Vector::pushBack(int *this, int *elementPtr)
{
    int currentSize = this[1];          // +0x04: current number of elements
    int currentCapacity = this[2];      // +0x08: allocated capacity (in elements)

    // If the vector is full, grow the capacity
    if (currentSize == currentCapacity) {
        int newCapacity;
        if (currentCapacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = currentCapacity * 2;
        }
        // Reallocate internal buffer to new capacity
        FUN_0082b640(newCapacity);
    }

    // Pointer to the slot where the new element will be placed
    int *slot = (int *)(this[0] + currentSize * 4);   // +0x00: base pointer to element array
    this[1] = currentSize + 1;

    // Copy the element into the vector (null safety check)
    if (slot != (int *)0x0) {
        *slot = *elementPtr;
    }
    return;
}