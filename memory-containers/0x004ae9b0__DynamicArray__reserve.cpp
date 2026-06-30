// FUNC_NAME: DynamicArray::reserve
// Reallocates internal storage to at least newCapacity elements (each element is 4 bytes)
// This is an internal method of a custom dynamic array class (similar to std::vector::reserve)
// Structure layout (this, int*):
//   +0x00: mData       (int*)          - pointer to allocated memory
//   +0x04: mSize       (uint32)        - current number of elements
//   +0x08: mCapacity   (uint32)        - allocated capacity (in elements)
//   +0x0C: mAllocator  (AllocatorVTbl**) - pointer to allocator vtable (may be null -> use default)
//   +0x10: pmAllocator (Allocator*)    - pointer to allocator object (used as context for allocate/deallocate)
// Note: The allocator object at [4] is a struct with a vtable pointer; its vtable has two functions:
//   [0] allocate(size, context) -> void*
//   [4] deallocate(ptr, flag)

struct AllocatorVTbl {
    void* (__thiscall* allocate)(uint size, void* context);
    void  (__thiscall* deallocate)(void* ptr, uint flag);
};

// Global default allocator (used when mAllocator is null)
extern AllocatorVTbl* gDefaultAllocator; // DAT_01218a14

void DynamicArray::reserve(uint newCapacity) {
    // Only expand if the requested capacity exceeds current capacity
    if (mCapacity >= newCapacity) {
        return;
    }

    // Determine allocator: use custom one if set, otherwise fallback to global default
    AllocatorVTbl* allocatorVTbl = mAllocator;
    void* allocatorContext = reinterpret_cast<void*>(pmAllocator); // +0x10
    if (allocatorVTbl == nullptr) {
        allocatorVTbl = gDefaultAllocator;
        allocatorContext = reinterpret_cast<void*>(gDefaultAllocator); // context equals the vtable pointer itself
    }

    // Allocate new memory block (4 bytes per element)
    int* newData = static_cast<int*>(allocatorVTbl->allocate(newCapacity * 4, allocatorContext));

    // Copy existing elements to the new buffer
    if (mData != nullptr && mSize > 0) {
        for (uint i = 0; i < mSize; ++i) {
            newData[i] = mData[i];
        }
    }

    // Free old memory if it exists
    if (mData != nullptr) {
        allocatorVTbl->deallocate(mData, 0);
    }

    // Update internal pointers and capacity
    mData = newData;
    mCapacity = newCapacity;
}