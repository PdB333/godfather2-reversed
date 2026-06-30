// FUNC_NAME: BufferAllocator::reallocateSlot
// Address: 0x0066b960
// Description: Allocates a 256-byte buffer, XORs with existing data from the object, updates the output slot (tagged pointer with count).
// The first parameter (thisPtr) is likely a pointer to a struct with at least:
//   offset 0: int m_currentSize;   // current number of ints used
//   offset 12: int* m_data;        // pointer to existing XOR data
// The second parameter (slot) is a 16-byte slot storing:
//   slot[0] : low 64 bits – contains a magic constant 0x4000000000 and also stores the count in low 32 bits on input
//   slot[1] : high 64 bits – stores the buffer pointer in its high 32 bits (shifted left 32) on output

int BufferAllocator::reallocateSlot(int *thisPtr, unsigned long long *slot)
{
    int *thisObj = thisPtr;           // 'this' pointer
    int newCount;                     // number of ints to XOR
    void *newBuf;                     // newly allocated buffer
    int i;                            // loop counter
    int result;                       // result from sub-function
    unsigned long long oldSlotVal;    // original slot[0] (count stored in low 32 bits)
    void *oldPtr;                     // original buffer pointer from slot[1] high 32 bits

    // Determine the count: use the smaller of current object size and the value pointed by thisPtr (parameter)
    // Note: In the original code, *thisObj and *thisPtr are compared; this is likely comparing m_currentSize against some external size.
    if (*thisObj < *thisPtr) {
        newCount = *thisObj;
    } else {
        newCount = *thisPtr;
        // In the decompiled else branch, thisObj is reassigned to thisPtr (side effect), possibly to update the object's size?
        thisObj = thisPtr;
    }

    // Allocate a buffer of 256 bytes (4 * 0x40 = 256, i.e., 64 ints)
    newBuf = calloc(4, 0x40);
    if (newBuf == nullptr) {
        return -2; // Allocation failure
    }

    // Call a sub-function (likely initializes the buffer or checks something)
    result = FUN_00665ce0();
    if (result != 0) {
        // Note: In the original code, no free of newBuf here; possibly the sub-function handles it.
        return result;
    }

    // XOR the new buffer with existing data from this object (offset 12, i.e., thisObj[3] is a pointer to int array)
    for (i = 0; i < newCount; i++) {
        ((unsigned int *)newBuf)[i] ^= ((unsigned int *)thisObj[3])[i];
    }

    // Save original slot contents before overwriting
    oldSlotVal = *slot;                         // Original low 64-bit (count in low 32 bits)
    oldPtr = (void *)(slot[1] >> 32);           // Original pointer from high 32 bits of second 64-bit

    // Update the slot with new values:
    // slot[0] = 0x4000000000 (magic constant; low 32 bits = 0, high 32 bits = 0x40)
    *slot = 0x4000000000;
    // slot[1] = pointer shifted left 32 (pointer stored in high 32 bits)
    slot[1] = ((unsigned long long)(uintptr_t)newBuf) << 32;

    // If there was an old buffer, zero it and free it
    if (oldPtr != nullptr) {
        memset(oldPtr, 0, (int)oldSlotVal * 4); // Clear based on stored count (each int = 4 bytes)
        free(oldPtr);
    }

    return 0; // Success
}