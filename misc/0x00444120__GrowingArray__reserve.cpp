// FUNC_NAME: GrowingArray::reserve
// Address: 0x00444120
// Role: Ensures the array has at least the given capacity; if current capacity < requested, reallocate and copy elements.

void __thiscall GrowingArray::reserve(uint requestedCapacity)
{
    // Member offsets (relative to this):
    // +0x00: void* mData (pointer to element buffer)
    // +0x04: uint mSize (number of elements)
    // +0x08: uint mCapacity (allocated capacity in elements)
    // +0x0C: void* mAllocator (pointer to allocator, or null => use default)
    // +0x10: void* mVTable (pointer to memory vtable with at least 2 functions:
    //          vtable[0] = allocate(size, allocator)
    //          vtable[4] = deallocate(ptr, allocator) )

    if (mCapacity >= requestedCapacity)
        return;

    // Use custom allocator or fallback to default (DAT_01218a14)
    void* allocator = mAllocator;
    if (allocator == nullptr)
        allocator = &sDefaultAllocator;  // DAT_01218a14

    // Get allocate function from vtable
    auto allocFunc = (void* (*)(uint, void*))((void***)mVTable)[0][0]; // vtable[0] is a function pointer

    // Allocate new buffer: each element is 0x14 (20) bytes
    uint newBufSize = requestedCapacity * 20;
    void* newBuffer = allocFunc(newBufSize, allocator);

    // Copy existing elements if present
    if (mData != nullptr)
    {
        uint count = mSize;
        if (count > 0)
        {
            // Element size is 20 bytes; copy elements byte by byte? Structure suggests 5 dwords per element.
            // The loop copies 5 dwords (20 bytes) per element.
            for (uint i = 0; i < count; i++)
            {
                // Source: old buffer + i*20
                uint srcOffset = i * 20;
                // Destination: new buffer + i*20
                uint dstOffset = i * 20;
                // Copy 5 dwords (20 bytes)
                ((uint*)((char*)newBuffer + dstOffset))[0] = ((uint*)((char*)mData + srcOffset))[0];
                ((uint*)((char*)newBuffer + dstOffset))[1] = ((uint*)((char*)mData + srcOffset))[1];
                ((uint*)((char*)newBuffer + dstOffset))[2] = ((uint*)((char*)mData + srcOffset))[2];
                ((uint*)((char*)newBuffer + dstOffset))[3] = ((uint*)((char*)mData + srcOffset))[3];
                ((uint*)((char*)newBuffer + dstOffset))[4] = ((uint*)((char*)mData + srcOffset))[4];
            }
        }

        // Free old buffer using vtable[4]
        auto deallocFunc = (void (*)(void*, void*))((void***)mVTable)[0][1]; // offset +4 in vtable (second pointer)
        deallocFunc(mData, allocator);
    }

    mData = newBuffer;
    mCapacity = requestedCapacity; // param_1 (which is originally the requested capacity)
}