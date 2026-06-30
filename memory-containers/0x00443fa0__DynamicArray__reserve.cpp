// FUNC_NAME: DynamicArray::reserve
// Function at 0x00443fa0: Reallocate internal buffer to new capacity (element size = 8 bytes)
void DynamicArray::reserve(uint newCapacity)
{
    // Structure offsets (this = ESI):
    // +0x00: mData (void*)
    // +0x04: mSize (uint)
    // +0x08: mCapacity (uint)
    // +0x0C: mpContextAllocator (Allocator* - can be null, then uses default)
    // +0x10: mpAllocator (Allocator* - object with vtable for allocate/free)

    if (mCapacity < newCapacity)
    {
        // Determine allocator context: use member pointer or default global allocator
        Allocator* context = mpContextAllocator;
        if (context == nullptr)
        {
            // Default global allocator (e.g., gDefaultAllocator at 0x01218a14)
            context = &gDefaultAllocator;
        }

        // Call vtable allocate function (first entry) : allocate(size, context)
        void* newData = mpAllocator->vtable->allocate(newCapacity * 8, context);

        // Copy existing elements if old buffer exists
        if (mData != nullptr)
        {
            uint count = mSize;
            for (uint i = 0; i < count; i++)
            {
                // Each element is 8 bytes (two ints)
                ((int*)newData)[i * 2]     = ((int*)mData)[i * 2];
                ((int*)newData)[i * 2 + 1] = ((int*)mData)[i * 2 + 1];
            }

            // Free old buffer via vtable free function (second entry) : free(ptr, 0)
            mpAllocator->vtable->free(mData, 0);
        }

        // Update pointers and capacity
        mData = newData;
        mCapacity = newCapacity;
    }
}