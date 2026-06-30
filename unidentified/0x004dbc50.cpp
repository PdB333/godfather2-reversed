// FUN_004dbc50: ShortArray::insert
int* __thiscall ShortArray::insert(uint index, const short* source, uint sourceIndex, uint numElements)
{
    // No-op if inserting nothing
    if (numElements == 0)
        return this;

    uint oldCount = count;
    if (oldCount == 0)
    {
        // Array is empty – delegate to a function that creates a new array from the source
        // FUN_004dbb10 is assumed to return a pointer to a new ShortArray
        return (int*)FUN_004dbb10((int)source, sourceIndex, numElements);
    }

    // If index is at or beyond the end, delegate to append logic
    if (index >= oldCount)
    {
        // FUN_004dbd90 handles appending
        return (int*)FUN_004dbd90((int)source, sourceIndex, numElements);
    }

    // Insertion in the middle
    uint newCount = oldCount + numElements;
    uint newCapacityBytes = newCount * 2;          // each short is 2 bytes
    uint oldCapacityBytes = capacity;             // capacity stored in bytes

    if (newCapacityBytes > oldCapacityBytes)
    {
        // Not enough room – allocate a new buffer
        // FUN_004db5c0 allocates memory; assumed to take size in bytes and return void*
        void* newBuffer = allocateMemory(newCapacityBytes);

        // Copy elements before the insertion point
        memcpy(newBuffer, data, index * 2);

        // Insert the new elements
        memcpy((char*)newBuffer + index * 2,
               (const char*)source + sourceIndex * 2,
               numElements * 2);

        // Copy the remaining elements after the insertion point
        // The array is null-terminated, so copy until a zero short is encountered
        short* src = (short*)((char*)data + index * 2);
        short* dst = (short*)((char*)newBuffer + (index + numElements) * 2);
        do {
            *dst = *src;
            src++;
            dst++;
        } while (*(dst - 1) != 0);  // the zero terminator is copied as well

        // Free the old buffer using the stored deallocator
        if (data != nullptr)
            deallocator(data);

        // Update the object fields
        data = (short*)newBuffer;
        count = newCount;
        capacity = newCapacityBytes;
        deallocator = defaultDeallocator;  // thunk_FUN_009c8eb0 – standard deallocator
    }
    else
    {
        // Enough capacity – shift existing data and insert in place
        memmove((char*)data + (index + numElements) * 2,
                (char*)data + index * 2,
                (oldCount - index) * 2);

        memcpy((char*)data + index * 2,
               (const char*)source + sourceIndex * 2,
               numElements * 2);

        count = newCount;

        // Write a null terminator at the new end
        *(short*)((char*)data + newCount * 2) = 0;
    }

    return this;
}