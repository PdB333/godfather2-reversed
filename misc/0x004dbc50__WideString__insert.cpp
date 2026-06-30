// FUNC_NAME: WideString::insert
// Address: 0x004dbc50
// Insert a range of shorts (wide characters) into a null-terminated array.
// The container is a dynamic array of shorts with a null terminator, similar to a wide string.
// Structure (int* this):
//   [0] data (short*) – pointer to buffer
//   [1] size (uint) – current length (excluding null terminator)
//   [2] capacity (uint) – allocated count (shorts)
//   [3] deallocator (void(*)(void*)) – function to free buffer

int* __thiscall WideString::insert(int* this_, uint insertIndex, int source, int sourceOffsetIndex, int count)
{
    short s;
    uint oldSize;
    uint newSize;
    size_t byteSize;
    void* newBuffer;
    short* pSrc;
    short* pDst;

    if (count == 0) {
        return this_;
    }

    oldSize = this_[1]; // current number of shorts (excluding null)
    if (oldSize == 0) {
        // Empty string: delegate to assign function (equivalent to constructing from source)
        return (int*)FUN_004dbb10(source, sourceOffsetIndex, count);
    }
    if (oldSize <= insertIndex) {
        // Insert at or beyond end: delegate to append function
        return (int*)FUN_004dbd90(source, sourceOffsetIndex, count);
    }

    // Insert in the middle
    newSize = (oldSize + count) * 2; // needed capacity in shorts (second multiplication is for 2 bytes per short)
    if ((uint)this_[2] <= newSize) {
        // Not enough capacity; reallocate
        newBuffer = (void*)FUN_004db5c0(); // allocate new buffer
        byteSize = insertIndex * 2; // bytes before insertion point
        _memcpy(newBuffer, (void*)*this_, byteSize);
        _memcpy((void*)((int)newBuffer + byteSize), (void*)(source + sourceOffsetIndex * 2), count * 2);
        pSrc = (short*)(*this_ + byteSize);
        pDst = (short*)((int)newBuffer + (insertIndex + count) * 2);
        // Copy the remainder, including null terminator (stops when zero short encountered)
        do {
            s = *pSrc;
            *pDst = s;
            pSrc++;
            pDst++;
        } while (s != 0);

        if (*this_ != 0) {
            (*(void (*)(void*))this_[3])((void*)*this_); // free old buffer
        }
        this_[1] = this_[1] + count; // update size
        this_[2] = newSize; // update capacity
        *this_ = (int)newBuffer;
        this_[3] = (int)thunk_FUN_009c8eb0; // set deallocator (likely free)
        return this_;
    }
    else {
        // Capacity sufficient: shift tail and insert
        _memmove((void*)(*this_ + (insertIndex + count) * 2),
                 (void*)(*this_ + insertIndex * 2),
                 (oldSize - insertIndex) * 2);
        _memcpy((void*)(*this_ + insertIndex * 2),
                (void*)(source + sourceOffsetIndex * 2),
                count * 2);
        this_[1] = this_[1] + count; // update size
        *(short*)(*this_ + this_[1] * 2) = 0; // write null terminator at new end
    }
    return this_;
}