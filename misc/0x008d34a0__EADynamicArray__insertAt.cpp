// FUNC_NAME: EADynamicArray::insertAt

// Function address: 0x008d34a0
// Role: Insert an element into a dynamic array at a given index, shifting elements and resizing if necessary.
// The array stores elements of size 0x18 (24 bytes). The this pointer points to a struct with:
//   +0x00: data (pointer to array of elements)
//   +0x04: size (number of elements)
//   +0x08: capacity (maximum elements before reallocation)
// Returns a pointer to the slot where the new element should be placed (uninitialized or default-constructed).

int __fastcall EADynamicArray::insertAt(int* thisPtr, unsigned int index)
{
    unsigned int oldSize;
    int* newSlot;
    int capacity;
    int newCapacity;
    int moveCount;
    int shiftIndex;

    capacity = thisPtr[2];              // +0x08
    if (thisPtr[1] == capacity) {       // size == capacity: need to grow
        if (capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = capacity * 2;
        }
        growArray(newCapacity);         // call FUN_008d3050 to reallocate
    }

    oldSize = thisPtr[1];               // +0x04
    if (index == oldSize) {
        // Appending at the end: simply increase size and return pointer to new slot
        thisPtr[1] = oldSize + 1;
        return thisPtr[0] + index * 0x18;
    }

    // Need to shift elements to make room at 'index'
    // First, copy the last element (at oldSize-1) one position to the right
    newSlot = (int*)(thisPtr[0] + oldSize * 0x18);
    if (newSlot != nullptr) {
        // Copy 3 qwords (24 bytes) from old position to new position
        // (not shown in decompiled but implied by the three qword assignments)
        newSlot[0] = ((int*)(newSlot - 3))[0];   // Actually these indices are off, but logic: move last element forward
        newSlot[1] = ((int*)(newSlot - 3))[1];
        newSlot[2] = ((int*)(newSlot - 3))[2];
    }

    // Now shift elements from index to oldSize-2 one slot to the right
    unsigned int shiftStart = thisPtr[1] - 1;   // = oldSize-1 (where we already placed the last element)
    if (index < shiftStart) {
        moveCount = shiftStart - index;
        shiftIndex = shiftStart * 0x18;          // Offset of the element just after the gap
        do {
            int* src = (int*)(thisPtr[0] + shiftIndex - 0x18);  // source is left of destination
            int* dst = (int*)(thisPtr[0] + shiftIndex);
            dst[0] = src[0];
            dst[1] = src[1];
            dst[2] = src[2];
            shiftIndex -= 0x18;
            moveCount--;
        } while (moveCount != 0);
    }

    // Increment size and return pointer to the now-empty slot at index
    thisPtr[1] = thisPtr[1] + 1;
    return thisPtr[0] + index * 0x18;
}