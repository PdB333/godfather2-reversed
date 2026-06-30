// FUNC_NAME: DynamicArray::reserve

void DynamicArray::reserve(uint newCapacity) {
    // Check if we need to grow: current capacity is less than requested.
    if (mCapacity < newCapacity) {
        void* allocator = mAllocator;
        if (allocator == nullptr) {
            allocator = &gDefaultAllocator; // DAT_01218a14
        }

        // Call the allocator's vtable[0] (allocate) function.
        // The allocator object's vtable pointer is stored at mAllocatorVTable (+0x10).
        void* newData = (void*)(*(code**)(*(void**)mAllocatorVTable)[0])(newCapacity * 0x50, allocator);

        // Copy existing elements if there are any.
        if (mData != nullptr && mCount != 0) {
            uint i = 0;
            int srcOffset = 0;
            void* dest = newData;
            do {
                if (dest != nullptr) {
                    void* src = (char*)mData + srcOffset;
                    void* destPtr = dest;
                    // Copy each element: size is 0x50 bytes = 20 dwords.
                    for (int j = 0; j < 20; j++) {
                        *(uint*)destPtr = *(uint*)src;
                        src = (uint*)src + 1;
                        destPtr = (uint*)destPtr + 1;
                    }
                }
                i++;
                srcOffset += 0x50;
                dest = (char*)dest + 0x50;
            } while (i < mCount);
        }

        // Free old buffer using the deallocator (vtable[1]).
        (*(code**)(*(void**)mAllocatorVTable)[1])(mData, 0);

        // Update members.
        mData = newData;
        mCapacity = newCapacity;
    }
}