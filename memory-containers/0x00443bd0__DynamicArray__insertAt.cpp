// FUNC_NAME: DynamicArray::insertAt
int* __thiscall DynamicArray::insertAt(int index) {
    // +0x00: buffer (data array pointer)
    // +0x04: size (number of elements)
    // +0x08: capacity (max elements before reallocation)
    // Each element is 20 bytes (5 ints)

    if (size == capacity) {
        int newCapacity;
        if (capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = capacity * 2;
        }
        // Internal grow function (FUN_00444120) reallocates buffer
        resize(newCapacity);
    }

    if (index != size) {
        // Shift elements after the insertion point to make room
        int* insertPos = &buffer[index]; // index * 20 bytes in int* terms
        // Shift the block from index to size-1 one slot up
        memmove(insertPos + 5, insertPos, (size - index) * 20);
        size++; // will be incremented later at the end
    } else {
        // Appending at end
        size++;
    }

    // Fill the new slot with debug sentinel values
    int* newSlot = &buffer[index];
    newSlot[0] = 0xBADBADBA;
    newSlot[1] = 0xBEEFBEEF;
    newSlot[2] = 0xEAC15A55;
    newSlot[3] = 0x91100911;
    // newSlot[4] is left uninitialized (the 5th int of the 20-byte struct)

    return newSlot;
}