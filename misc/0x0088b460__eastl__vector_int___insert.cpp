// FUNC_NAME: eastl::vector<int>::insert
// Address: 0x0088b460
// Role: Inserts an element into a dynamic array (EASTL vector), with reallocation if necessary.
// The structure at param_1 is a vector with three int* fields: begin, end, capacity_end.
// param_2 is a pointer to the insertion position within the existing array.
// param_3 is a pointer to the value to insert (may be within the same array, hence self-insertion support).

void __thiscall Vector::insert(int **this, int *insertPos, int *valuePtr)
{
    int *oldEnd = this[1];          // +0x4: current end pointer
    int *capacityEnd = this[2];     // +0x8: capacity end pointer

    if (oldEnd != capacityEnd) {
        // There is room for one more element
        // Handle self-insertion: if the value to insert lies after the insertion point,
        // it will be shifted, so adjust the value pointer accordingly
        if (insertPos <= valuePtr && valuePtr < oldEnd) {
            valuePtr = valuePtr + 1;
        }

        if (oldEnd != nullptr) {
            // Move the last element one slot forward to make room
            *oldEnd = *(oldEnd - 1);
        }

        // Calculate the number of elements to shift right (from insertPos to one before oldEnd)
        size_t shiftCount = (oldEnd - 1) - insertPos;  // in elements
        // Move the block from insertPos to oldEnd-1 to the right by one slot
        _memmove(oldEnd - shiftCount, insertPos, shiftCount * 4);

        // Insert the new value
        *insertPos = *valuePtr;

        // Advance the end pointer
        this[1] = oldEnd + 1;
        return;
    }

    // Need to reallocate: double the capacity (or set to 1 if empty)
    int oldCapacity = oldEnd - this[0];  // element count
    int newCapacity = (oldCapacity == 0) ? 1 : oldCapacity * 2;

    if (newCapacity == 0) {
        // Overflow, but EASTL usually does not handle this; allocate null? (unlikely)
        // The decompiled shows a jump to LAB_0088b4fd with _Dst = 0; but that path is unlikely.
        // We'll skip that edge case as it leads to invalid dereference.
        // Typically newCapacity > 0.
        return;
    }

    // Allocate new buffer (using EASTL allocator with debug info)
    int *newBuffer = (int *)FUN_0068ab90(newCapacity * 4, "EASTL", 0, 0,
                                         "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h", 0xe9);
    // Copy elements before insertion point
    size_t beforeCount = insertPos - this[0];  // elements before insertPos
    int *newPos = (int *)_memmove(newBuffer, this[0], beforeCount * 4);
    int *insertSlot = newPos + beforeCount;  // slot for the new element

    if (insertSlot != nullptr) {
        *insertSlot = *valuePtr;
    }

    // Copy elements after insertion point
    size_t afterCount = this[1] - insertPos;  // elements after insertPos
    int *endPtr = (int *)_memmove(insertSlot + 1, insertPos, afterCount * 4);

    // Free old buffer
    if (this[0] != nullptr) {
        FUN_009c8f10(this[0]);  // operator delete
    }

    // Update pointers
    this[0] = newBuffer;
    this[1] = endPtr + afterCount;  // new end = newBuffer + beforeCount + 1 + afterCount
    this[2] = newBuffer + newCapacity;
}