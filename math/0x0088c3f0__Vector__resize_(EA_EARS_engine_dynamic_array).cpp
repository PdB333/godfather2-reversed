// FUNC_NAME: Vector::resize (EA EARS engine dynamic array)
// Address: 0x0088c3f0
// Role: Resize a dynamic array container (start, finish, end_of_storage). Handles grow, shrink, and reallocation.

// Struct layout (3 ints, plus possibly a fourth field for internal allocator):
// offset 0x00: int* m_start       // pointer to allocated buffer
// offset 0x04: int* m_finish      // pointer one past last used element
// offset 0x08: int* m_endOfStorage // pointer to end of allocated capacity
// offset 0x0C: (optional) internal allocator data (passed to reallocateToFit)

void __thiscall Vector::resize(int* thisPtr, uint newSize)
{
    int* oldStart;
    int* oldFinish;
    int* newBuffer;
    void* tempBuffer;
    size_t bytesUsed;

    // Special sentinel 0xFFFFFFFF might mean "compact" (shrink to fit)
    if (newSize != 0xFFFFFFFF) {
        // Check if we need to grow the buffer
        uint currentCapacity = (thisPtr[1] - thisPtr[0]) >> 2; // element count capacity
        if (currentCapacity < newSize) {
            // Grow: allocate new buffer with room for newSize elements
            newBuffer = allocNewBuffer(newSize, thisPtr[0], thisPtr[1]);
            if (thisPtr[0] != 0) {
                freeBuffer(thisPtr[0]);
            }
            oldStart = thisPtr[0];
            thisPtr[0] = newBuffer;                         // new start
            thisPtr[1] = newBuffer + ((thisPtr[1] - oldStart) >> 2); // adjust finish (copy of old count)
            thisPtr[2] = newBuffer + newSize;                // new capacity end
            return;
        }
    }

    // Case: not growing (or compact sentinel)
    uint currentCount = (thisPtr[1] - thisPtr[0]) >> 2; // number of used elements
    if (newSize < currentCount && newSize != 0xFFFFFFFF) {
        // Shrink the used count (without freeing memory yet)
        shrinkSize(newSize);
    }

    // Reallocate to exactly fit the (possibly shrunk) current count
    // allocates a new buffer via the allocator stored at &thisPtr[3] and returns pointer
    tempBuffer = reallocateToFit(currentCount, &thisPtr[3]);

    bytesUsed = thisPtr[1] - thisPtr[0]; // size in bytes of used data
    memmove(tempBuffer, (void*)thisPtr[0], bytesUsed);

    oldFinish = thisPtr[1];
    thisPtr[0] = (int*)tempBuffer;                          // new start
    thisPtr[1] = (int*)((int)tempBuffer + (bytesUsed >> 2) * 4); // new finish
    thisPtr[2] = (int*)local_8; // local_8 is uninitialized – likely should be tempBuffer + currentCount
    // Note: The assignment to thisPtr[2] from local_8 seems erroneous in decompilation.
    // In original code, capacity after reallocation should be currentCount, i.e.,
    // thisPtr[2] = (int*)tempBuffer + currentCount;

    // Free old buffer if it existed
    if (oldFinish != 0) {
        freeBuffer(oldFinish); // oldFinish used as base address? Actually should free old start
        // Possibly a decompilation bug: should free thisPtr[0] before assigning new?
    }

    return;
}