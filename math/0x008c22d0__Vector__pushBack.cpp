// FUNC_NAME: Vector::pushBack
void __thiscall Vector::pushBack(int* thisPtr, const void* element) {
    int* data = (int*)thisPtr[0];      // +0x00: pointer to element array
    int size = thisPtr[1];             // +0x04: current number of elements
    int capacity = thisPtr[2];         // +0x08: allocated capacity

    // Grow if full
    if (size == capacity) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        // Internal resize/reallocate (FUN_008be170)
        resize(newCapacity);
        // After resize, update local pointers (though thisPtr is modified by resize)
        data = (int*)thisPtr[0];
        capacity = thisPtr[2];
    }

    // Element size is 12 bytes (0xC)
    const int elementSize = 0xC;
    char* dest = (char*)data + size * elementSize;
    thisPtr[1] = size + 1; // increment size

    if (dest != nullptr) {
        // Copy 12 bytes: first 8 bytes as uint64, then 4 bytes as uint32
        *(uint64_t*)dest = *(uint64_t*)element;
        *(uint32_t*)(dest + 8) = *(uint32_t*)((const char*)element + 8);
    }
}