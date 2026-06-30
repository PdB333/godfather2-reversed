// FUNC_NAME: EAString::operator=
// 0x004d3d90 - EA String assignment operator (custom allocator-aware string class)
// Class structure (offsets):
//   +0x00: char* mBuffer
//   +0x04: uint32_t mLength
//   +0x08: uint32_t mCapacity
//   +0x0C: void (*mDeallocator)(void*)
// Custom heap: FUN_009c8e50 = allocate, thunk_FUN_009c8eb0 = free

int* __thiscall EAString::operator=(const char* source)
{
    // If source is null or empty, clear the string
    if (source == nullptr || *source == '\0')
    {
        mLength = 0;
        if (mBuffer != nullptr)
        {
            mBuffer[0] = '\0';
        }
        return this;
    }

    // Avoid self-assignment: if source is same as buffer, do nothing
    if (source == mBuffer)
    {
        return this;
    }

    // Compute source length
    const char* p = source;
    while (*p != '\0')
        p++;
    uint32_t newLen = (uint32_t)(p - source); // length without null terminator

    // Check if reallocation is needed
    if (mCapacity <= newLen)
    {
        // Free old buffer using custom deallocator
        if (mBuffer != nullptr)
        {
            mDeallocator(mBuffer);
        }

        // Allocate new buffer (newLen+1 bytes)
        mBuffer = (char*)allocate(newLen + 1); // FUN_009c8e50
        mCapacity = newLen;
        mDeallocator = (void(*)(void*))freeFunc; // thunk_FUN_009c8eb0
    }

    // Copy string (including null terminator)
    memcpy(mBuffer, source, newLen);
    mBuffer[newLen] = '\0';
    mLength = newLen;

    return this;
}