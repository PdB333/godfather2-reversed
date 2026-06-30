// FUNC_NAME: EARSArray::growCapacity
// Reconstructed C++ for function 0x006f4410 – EARS engine dynamic array grow implementation
// Class layout:
// +0x00: mData (int*) – pointer to element array
// +0x04: mSize (uint) – number of elements
// +0x08: mCapacity (uint) – allocated capacity (in elements)
// +0x0C: mAllocatorHint (void*) – optional hint for allocator
// +0x10: mAllocator (AllocatorVTable*) – pointer to allocator function table
//   AllocatorVTable layout:
//   +0x00: allocate(size, hint) -> void*
//   +0x04: deallocate(ptr, size)

void __thiscall EARSArray::growCapacity(int* thisPtr, uint newCapacity)
{
    void* (*allocate)(size_t, void*);
    void  (*deallocate)(void*, size_t);

    // Only grow if requested capacity exceeds current
    if (thisPtr[2] < newCapacity) {
        // Determine allocator hint; use global default if null
        void* hint = (void*)thisPtr[3];
        if (hint == nullptr) {
            hint = &DAT_01218a14;  // global default allocator hint
        }

        // Retrieve the allocator function table
        AllocatorVTable* allocator = (AllocatorVTable*)thisPtr[4];
        allocate = (void* (*)(size_t, void*))allocator[0];
        deallocate = (void (*)(void*, size_t))allocator[1];

        // Allocate new buffer (size = newCapacity * sizeof(int))
        void* newData = (*allocate)(newCapacity * 4, hint);

        // Copy existing elements to new buffer
        if (thisPtr[0] != 0) {
            uint i = 0;
            int* dest = (int*)newData;
            int* src = (int*)thisPtr[0];
            while (i < thisPtr[1]) {
                if (dest != nullptr) {
                    dest[i] = src[i];
                }
                i++;
            }
            // Deallocate old buffer
            (*deallocate)(src, 0);
        }

        // Update members
        thisPtr[0] = (int)newData;
        thisPtr[2] = newCapacity;
    }
}