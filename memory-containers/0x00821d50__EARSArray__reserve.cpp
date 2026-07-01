// FUNC_NAME: EARSArray::reserve
// Function at 0x00821d50: Grows the internal array capacity to at least newCapacity.
// Each element is 0x130 bytes. Uses a custom allocator with vtable.
// Members: data (offset 0), count (offset 4), capacity (offset 8),
//          fallbackAllocator (offset 12), allocator (offset 16).
// The allocator object has vtable: allocate(size, hint) at vtable[0],
// deallocate(ptr, size) at vtable[4].

void __thiscall EARSArray::reserve(int* thisPtr, uint newCapacity)
{
    int* data = (int*)thisPtr[0]; // +0x00
    uint count = (uint)thisPtr[1]; // +0x04
    uint capacity = (uint)thisPtr[2]; // +0x08
    void* fallbackAlloc = (void*)thisPtr[3]; // +0x0C
    void* allocator = (void*)thisPtr[4]; // +0x10

    if (newCapacity <= capacity)
        return;

    // Use fallback allocator if allocator is null
    if (allocator == nullptr)
        allocator = &DAT_01218a14; // global default allocator

    // Allocate new block via allocator vtable[0]
    int* newData = (int*)(*(void* (__thiscall**)(void*, size_t, void*))(*((int*)allocator)))(allocator, newCapacity * 0x130, fallbackAlloc);

    if (data != nullptr && count != 0)
    {
        int* src = data;
        int* dst = newData;
        for (uint i = 0; i < count; i++)
        {
            // Copy construct element at dst from src
            elementCopyConstruct((undefined4*)dst, (undefined4*)src);
            // Destroy old element (call vtable[0] with 0)
            (*(void (__thiscall**)(int*, int))(*((int*)src)))(src, 0);
            src += 0x130 / 4;
            dst += 0x130 / 4;
        }
        // Deallocate old block via allocator vtable[4]
        (*(void (__thiscall**)(void*, void*, size_t))(*((int*)allocator) + 4))(allocator, data, 0);
    }

    thisPtr[0] = (int)newData;
    thisPtr[2] = newCapacity;
}