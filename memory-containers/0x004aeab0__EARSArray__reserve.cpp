// FUNC_NAME: EARSArray::reserve
void __thiscall EARSArray::reserve(uint newCapacity) {
    // Check if reallocation is needed (new capacity > current capacity)
    if (newCapacity > capacity) {
        // Get allocator; if null, use default global allocator (DAT_01218a14)
        void* allocator = allocatorPtr;
        if (allocator == nullptr) {
            allocator = gDefaultAllocator; // Global default allocator
        }

        // Retrieve allocation function from vtable (vtablePtr + 0x00)
        // vtablePtr is at offset +0x10 in the object
        void* vtable = *(void**)vtablePtr;
        AllocateFunc allocFunc = *(AllocateFunc*)vtable; // (uint size, void* allocator)
        int* newData = (int*)allocFunc(newCapacity * 4, allocator);

        // Copy existing elements (size at offset +0x04)
        if (data != nullptr) {
            for (uint i = 0; i < size; i++) {
                newData[i] = data[i];
            }
        }

        // Retrieve deallocation function from vtable (vtablePtr + 0x04)
        DeallocateFunc deallocFunc = *(DeallocateFunc*)((char*)vtable + 4); // (void* ptr, int zero)
        deallocFunc(data, 0); // Free old data

        // Update data pointer and capacity
        data = newData;
        capacity = newCapacity;
    }
}