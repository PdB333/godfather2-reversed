// FUNC_NAME: DynamicArray::reserve

// Function 0x0098e0f0: Resizes the internal buffer of a dynamic array to accommodate at least 'newCapacity' elements.
// Element size is 0x14 (20 bytes). Each element has a destructor function pointer at offset 0x0C.
// The array structure: [0] = buffer pointer, [1] = count, [2] = capacity.

void __thiscall DynamicArray::reserve(int* this, uint newCapacity) {
    int oldBuffer;
    int oldCount;
    int newBuffer;
    int elementOffset;
    int* oldElementPtr;
    uint i;
    int* newElementPtr;

    if ((uint)this[2] < newCapacity) {
        // Allocate new buffer with enough space for 'newCapacity' elements
        newBuffer = allocate(newCapacity * 0x14);
        oldCount = this[1];
        elementOffset = 0;
        if (this[0] != 0) {
            i = 0;
            newElementPtr = (int*)newBuffer;
            if (oldCount != 0) {
                do {
                    // Copy an element from old buffer to new buffer
                    oldElementPtr = (int*)(this[0] + elementOffset);
                    if (newElementPtr != 0) {
                        // Copy first 16 bytes (offsets 0x00-0x0F) using copy constructor/assignment
                        Element::copy(oldElementPtr, newElementPtr);
                        // Copy the last field (offset 0x10) manually
                        newElementPtr[4] = oldElementPtr[4];
                    }
                    // Call destructor on the old element if its first pointer is non-null
                    if (*oldElementPtr != 0) {
                        // Function pointer at offset 0x0C (oldElementPtr[3]) is the destructor
                        (*(void (*)(int))oldElementPtr[3])(*oldElementPtr);
                    }
                    i++;
                    elementOffset += 0x14;
                    newElementPtr += 5; // advance by 20 bytes (5 ints)
                } while (i < (uint)oldCount);
            }
            // Free old buffer
            deallocate(this[0]);
        }
        this[0] = newBuffer;
        this[2] = newCapacity;
    }
    // Note: the count remains unchanged
}