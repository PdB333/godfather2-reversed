// FUNC_NAME: DynamicArray::resize
// Reconstructed from 0x0088beb0
// This function resizes the dynamic array to hold 'newSize' elements of 0x50 bytes each.
// It handles both expansion (reallocation with copy) and shrinking (truncation).
// The array header is a three-int structure:
//   +0x00: begin (pointer to allocated buffer)
//   +0x04: end (pointer past last used element)
//   +0x08: capacityEnd (pointer past allocated buffer)
// Element size is 0x50 (80 bytes). Parameter 0xFFFFFFFF means "no change".

void __thiscall DynamicArray::resize(int *this, uint newSize)
{
    int oldBegin;
    int oldEnd;
    int newBuffer;
    int usedCount;
    int newEnd;
    
    // If newSize is the "no change" sentinel, skip entirely
    if (newSize != 0xffffffff)
    {
        // Check if newSize exceeds current capacity (capacity = (end - begin) / elementSize)
        if ( (uint)((this[1] - *this) / 0x50) < newSize )
        {
            // Need to grow: allocate new buffer
            // FUN_00889840 likely does: reallocate(newSize, oldBegin, oldEnd) and returns new buffer
            newBuffer = FUN_00889840(newSize, *this, this[1]);
            if (*this != 0)
            {
                FUN_009c8f10(*this);      // free old buffer
            }
            oldBegin = *this;
            *this = newBuffer;                       // update begin
            // The used portion remains the same count; copy across old end pointer
            this[1] = ((this[1] - oldBegin) / 0x50) * 0x50 + newBuffer;  // new end = newBegin + usedBytes
            this[2] = newSize * 0x50 + newBuffer;   // new capacityEnd
            return;
        }
    }
    
    // Shrinking case: if newSize is smaller than current used count, truncate used
    if (newSize < (uint)((this[1] - *this) / 0x50))
    {
        FUN_0088b360(newSize);     // likely sets used count to newSize
    }
    
    // Swap the internal pointers with stack variables (probably to handle reallocation of header itself)
    FUN_008897b0(this);           // likely exchanges *this, this[1], this[2] with local_10, local_c, local_8
    
    local_10 = *this;   // these locals appear after call? Actually in decomp they are used after call.
    local_c = this[1];
    local_8 = this[2];
    
    oldBegin = *this;
    *this = local_10;
    this[1] = local_c;
    this[2] = local_8;
    if (oldBegin != 0)
    {
        FUN_009c8f10(oldBegin);   // free old buffer if any
    }
    return;
}