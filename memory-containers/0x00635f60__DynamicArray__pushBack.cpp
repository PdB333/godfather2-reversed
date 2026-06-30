// FUNC_NAME: DynamicArray::pushBack
// Function address: 0x00635f60
// This function inserts a pair of ints into a dynamic array. The array stores elements as two consecutive ints.
// Offsets:
//   +0x08: mCurrent (write pointer to next free slot, in bytes from buffer start)
//   +0x18: mEnd (pointer to the end of allocated buffer, used for capacity checks)
//   +0x1c: mBuffer (base pointer to allocated memory)
//   +0x20: mCapacity (element count capacity, based on which new capacity is computed)
// The input parameter param_1 is a pointer to a 2-int element. Depending on the first int (type),
// the actual data to push is either obtained from a static pool or a default element.
// If remaining space is less than 9 bytes (< two ints + margin), the buffer is grown.
// After growth, elements are shifted if necessary to maintain order (loop may be for front insertion).

void DynamicArray::pushBack(int *aData) {
    int *origData = aData;                         // save original input pointer

    // Determine data source based on type field (first int)
    if (*aData == 5 || *aData == 7) {
        aData = (int *)GetStaticPool();            // FUN_00637f90 - returns pointer to a static element
    } else {
        aData = &g_DefaultElement;                 // DAT_00e2a93c - global default element
    }

    int *oldBuffer = mBuffer;                      // offset +0x1c

    // Debug/log if the type is not 6
    if (*aData != 6) {
        DebugLog(&g_SomeDebugGlobal);              // FUN_006336f0 - logs to some debug structure
    }

    // Shift existing elements to make room for insertion at the position pointed by origData.
    // This loop is active only when origData (the original caller data pointer) is inside the current buffer.
    // It moves elements one slot (2 ints) to the right from the end down to the insertion point.
    // This effectively implements an "insert at given index" operation, with the index derived from origData.
    // If origData is outside the buffer (typical for push_back), the loop body does not execute.
    for (int *ptr = mCurrent; origData < ptr; ptr -= 2) {
        *ptr = ptr[-2];
        ptr[1] = ptr[-1];
    }

    // Check if we have enough space for 2 ints (8 bytes). If remaining capacity < 9 bytes, grow.
    if (mEnd - mCurrent < 9) {
        int oldCap = mCapacity;                    // offset +0x20
        int newCap = oldCap * 2;
        if (oldCap < 1) {
            newCap = oldCap + 0x15;                // ensure minimum growth
        }

        // Reallocate buffer: old size = oldCap * 8 bytes, new size = newCap * 8 bytes.
        int *newBuffer = (int *)Reallocate(oldCap * 8, newCap * 8);  // FUN_006279a0

        // Update buffer pointer
        mBuffer = newBuffer;                       // offset +0x1c
        // Update end pointer: new buffer + (newCap * 8) - 0xa8 (0xa8 = header size? possibly for alignment)
        mEnd = newBuffer + newCap * 8 - 0xa8;      // offset +0x18
        mCapacity = newCap;                        // offset +0x20

        PostReallocate();                          // FUN_00635b50 - update internal state after realloc
    }

    // Advance write pointer by 8 bytes (one element)
    mCurrent += 8;                                 // offset +0x08

    // Compute actual write position in the buffer, adjusting pointer for possible buffer relocation
    int *writePos = origData + (mBuffer - oldBuffer);

    // Write the two ints from the (possibly resolved) source data
    *writePos = *aData;
    writePos[1] = aData[1];
}