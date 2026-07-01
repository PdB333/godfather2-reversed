// FUNC_NAME: eastl::vector<ElementType>::insert
// Reconstructed from 0x0098c2b0 - EASTL vector insertion with 0x10-byte elements
// This inserts a value at a given position, reallocating if needed.
void __thiscall VectorInsert(int* thisPtr, uint elementPtr, uint valuePtr) {
    // thisPtr: pointer to vector struct: [0] = begin, [4] = end, [8] = capacity_end
    uint oldEnd = thisPtr[1];   // end pointer
    uint capacity = thisPtr[2]; // capacity_end pointer

    // If there is room for one more element
    if (oldEnd != capacity) {
        uint insertDest = valuePtr;
        // If the insertion position (elementPtr) is before the value's original location?
        if ((elementPtr <= valuePtr) && (valuePtr < oldEnd)) {
            // Adjust destination because we are about to shift elements
            insertDest = valuePtr + 0x10;
        }
        if (oldEnd != 0) {
            // Destroy the element at oldEnd - 0x10 (the last element)
            FUN_004d3b50(oldEnd - 0x10);
        }
        // Move the element from (oldEnd - 0x10) to (elementPtr)
        FUN_0098b380(elementPtr, oldEnd - 0x10, oldEnd);
        // Construct the new value at the calculated destination
        FUN_004d3e20(insertDest);
        thisPtr[1] = oldEnd + 0x10; // bump end pointer
        return;
    }

    // Need to reallocate (double capacity or at least 1)
    int currentSize = (int)(oldEnd - thisPtr[0]) >> 4; // number of elements (size / 0x10)
    int newCapacity = currentSize == 0 ? 1 : currentSize * 2;
    if (newCapacity == 0) {
        // If doubling overflowed, allocate zero? (likely debug check)
        // This path sets newBegin to 0 and goes to the cleanup? But code jumps to LAB_0098c34a and newBegin is 0? Actually iVar3 = 0, so allocation fails.
        // In practice this shouldn't happen.
        int newBegin = 0;
        goto skipAllocation;
    }
    int newBegin = FUN_0068ab90(newCapacity << 4, "EASTL", 0, 0,
                                "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h", 0xe9);
skipAllocation:
    // Copy elements from begin to insertion point into new memory
    uint oldBegin = thisPtr[0];
    FUN_0098b790(&elementPtr, oldBegin, elementPtr, newBegin, elementPtr);
    // Destroy the element at valuePtr (the original value to insert? or the element being replaced?)
    if (elementPtr != 0) {
        FUN_004d3b50(valuePtr);
    }
    // Copy elements from old end to new memory (after the inserted element)
    FUN_0098b790(&elementPtr, oldEnd, thisPtr[1], elementPtr + 0x10, elementPtr);
    // Destroy all elements in the old range
    FUN_0098b6c0(oldBegin, oldEnd);
    // Free old memory
    if (oldBegin != 0) {
        FUN_009c8f10(oldBegin);
    }
    // Update vector pointers
    thisPtr[1] = elementPtr;          // new end = after inserted element?
    thisPtr[0] = newBegin;            // new begin
    thisPtr[2] = newCapacity * 0x10 + newBegin; // new capacity end
}