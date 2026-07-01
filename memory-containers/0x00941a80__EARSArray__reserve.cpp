// FUNC_NAME: EARSArray::reserve

void EARSArray::reserve(unsigned int newCapacity) {
    // Object layout:
    // +0x00: mData (void*) - pointer to element array
    // +0x04: mSize (int) - number of elements currently stored
    // +0x08: mCapacity (unsigned int) - allocated capacity
    // +0x0C: mAllocatorData (void*) - custom allocator data, if null use default
    // +0x10: mAllocator (Allocator*) - pointer to allocator object with vtable at offset 0

    const unsigned int ElementSize = 0x30; // 48 bytes per element

    if (mCapacity >= newCapacity) {
        return; // already large enough
    }

    // Resolve allocator data (default global if none provided)
    void* allocData = mAllocatorData;
    if (allocData == nullptr) {
        allocData = &gDefaultAllocatorData; // DAT_01218a14
    }

    // Allocate new block via allocator vtable (first virtual function)
    // Signature: void* allocate(unsigned int size, void* allocData)
    AllocatorVTable* vtable = *(AllocatorVTable**)mAllocator;
    void* newData = vtable->allocate(newCapacity * ElementSize, allocData);

    // Copy existing elements
    if (mData != nullptr && mSize > 0) {
        char* src = static_cast<char*>(mData);
        char* dst = static_cast<char*>(newData);
        for (unsigned int i = 0; i < static_cast<unsigned int>(mSize); i++) {
            // Each element is copied as 6 qwords (48 bytes)
            *reinterpret_cast<unsigned long long*>(dst) = *reinterpret_cast<unsigned long long*>(src);
            *reinterpret_cast<unsigned long long*>(dst + 8) = *reinterpret_cast<unsigned long long*>(src + 8);
            *reinterpret_cast<unsigned long long*>(dst + 16) = *reinterpret_cast<unsigned long long*>(src + 16);
            *reinterpret_cast<unsigned long long*>(dst + 24) = *reinterpret_cast<unsigned long long*>(src + 24);
            *reinterpret_cast<unsigned long long*>(dst + 32) = *reinterpret_cast<unsigned long long*>(src + 32);
            *reinterpret_cast<unsigned long long*>(dst + 40) = *reinterpret_cast<unsigned long long*>(src + 40);
            src += ElementSize;
            dst += ElementSize;
        }

        // Free old block via allocator vtable (second virtual function)
        // Signature: void deallocate(void* ptr, int flag)
        vtable->deallocate(mData, 0);
    }

    // Update pointers and capacity
    mData = newData;
    mCapacity = newCapacity;
}