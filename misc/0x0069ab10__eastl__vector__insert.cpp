// FUNC_NAME: eastl::vector::insert
// Address: 0x0069ab10
// Inserts an element at the specified position, growing the vector if necessary.
// This is an EASTL vector implementation (see debug string "EASTL/allocator.h").
// The vector structure is: [begin_ptr, end_ptr, capacity_end_ptr].
// Elements are 4 bytes (presumably int32 or pointers).
// Internal helper functions:
//   0x0068ab90 – EASTL memory allocation (operator new / allocator::allocate)
//   0x009c8f10 – EASTL memory deallocation (operator delete / allocator::deallocate)

void __thiscall eastl::vector::insert(int* mBegin, int* mEnd, int* mCapacity)
{
    int* endPtr = mBegin[1];  // current end pointer
    int* capacityPtr = mBegin[2]; // capacity end pointer
  
    if (endPtr != capacityPtr)
    {
        // There is capacity left; shift elements to make room.
        // If the value to insert (mEnd) is within the shifted region, update it.
        if (mBegin <= mEnd && mEnd < endPtr)
        {
            mEnd = mEnd + 1;
        }
        if (endPtr != nullptr)
        {
            *endPtr = *(endPtr - 1); // preserve the element that will be moved? Actually this appears to be a copy to fill the gap? Wait.
            // More typical: the last element is moved one slot forward to make room.
        }
        size_t sizeToMove = (endPtr - 4) - (int)mBegin; // size in bytes of elements after insertion point
        memmove((void*)(endPtr + ((int)sizeToMove >> 2) * -4), mBegin, sizeToMove); // shift memory right
        *mBegin = *mEnd; // insert the value
        mBegin[1] = endPtr + 4; // update end pointer
        return;
    }
    // Need to grow the container.
    int currentSize = (int)(endPtr - mBegin[0]) >> 2; // number of elements currently
    int newCapacity;
    if (currentSize == 0)
    {
        newCapacity = 1;
    }
    else
    {
        newCapacity = currentSize * 2;
    }
    void* newBuffer;
    if (newCapacity == 0)
    {
        newBuffer = nullptr;
        goto LAB_0069abad;
    }
    newBuffer = (void*)FUN_0068ab90(newCapacity * 4, "EASTL", 0, 0, "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h", 0xe9);
  
LAB_0069abad:
    size_t bytesBeforeInsert = (int)mBegin - mBegin[0]; // bytes from begin to insertion point
    void* temp = memmove(newBuffer, (void*)mBegin[0], bytesBeforeInsert); // copy elements before insertion
    int* insertPos = (int*)((int)temp + bytesBeforeInsert); // point to insertion location in new buffer
    if (insertPos != nullptr)
    {
        *insertPos = *mEnd; // insert the value
    }
    int oldEndOffset = mBegin[1] - mBegin[0]; // total bytes currently used
    memmove(insertPos + 1, mBegin, oldEndOffset - (int)mBegin); // copy elements after insertion
    if (mBegin[0] != 0)
    {
        FUN_009c8f10(mBegin[0]); // free old buffer
    }
    mBegin[0] = (int)newBuffer;
    mBegin[1] = (int)((int)temp + bytesBeforeInsert + 4); // update end: old size + 1 element
    mBegin[2] = (int)((int)newBuffer + newCapacity * 4);
    return;
}