// FUNC_NAME: VectorBase::reserve
void VectorBase::reserve(uint newCapacity)
{
    // If current capacity is insufficient, reallocate
    if (capacity < newCapacity)
    {
        // Get allocator, use default if none set
        void* allocator = mAllocator;
        if (allocator == nullptr)
        {
            allocator = &gDefaultAllocator;
        }

        // Allocate new buffer via allocator's vtable (+0x00: allocate)
        void* newData = ((void* (*)(uint, void*))(*((void***)allocator)[0]))(newCapacity * 4, allocator);

        // Copy existing elements (element size = 4 bytes)
        if (mData != nullptr && count > 0)
        {
            for (uint i = 0; i < count; i++)
            {
                ((uint*)newData)[i] = ((uint*)mData)[i];
            }

            // Free old buffer via allocator's vtable (+0x04: deallocate)
            ((void (*)(void*, uint))(*((void***)allocator)[1]))(mData, 0);
        }

        // Update buffer pointer and capacity
        mData = newData;
        capacity = newCapacity;
    }
}