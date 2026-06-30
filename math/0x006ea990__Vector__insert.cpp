// FUNC_NAME: Vector::insert
// Address: 0x006ea990
// Description: Inserts an element at the specified index, shifting subsequent elements right. Reallocates if capacity is exceeded.

undefined4* __thiscall Vector::insert(int* thisPtr, uint index)
{
    undefined4* insertedSlot;
    uint currentSize;
    int capacity;

    capacity = thisPtr[2]; // +8: capacity
    if (thisPtr[1] == capacity) { // +4: size == capacity
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        // Reallocate the internal array to new capacity
        FUN_006ea5e0(capacity);
    }

    currentSize = thisPtr[1]; // +4: size
    insertedSlot = (undefined4*)(*thisPtr + currentSize * 4); // Address of the new element at the end (temporary)

    if (index == currentSize) {
        // Appending to the end: just increment size
        thisPtr[1] = currentSize + 1;
        return insertedSlot;
    }

    // Inserting in the middle: shift elements right from index to end
    if (insertedSlot != (undefined4*)0x0) {
        *insertedSlot = insertedSlot[-1]; // Copy the last element one position right (overwrites uninitialized? Actually shifting)
    }

    currentSize = thisPtr[1];
    while (currentSize = currentSize - 1, index < currentSize) {
        // Shift each element right by one
        *(undefined4*)(*thisPtr + currentSize * 4) = *(undefined4*)(*thisPtr + (currentSize - 1) * 4);
    }

    // Increment size after insertion
    thisPtr[1] = thisPtr[1] + 1;

    // Return pointer to the insertion slot
    return (undefined4*)(*thisPtr + index * 4);
}