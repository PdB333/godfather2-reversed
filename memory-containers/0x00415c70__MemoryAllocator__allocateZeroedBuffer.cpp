// FUNC_NAME: MemoryAllocator::allocateZeroedBuffer
// Address: 0x00415c70
// Role: Allocates a zeroed block of 0x408 bytes using a vtable-based allocator from the object's memory manager.
// The allocator's vtable pointer is stored at offset +0x4 of the object (this).
void* MemoryAllocator::allocateZeroedBuffer()
{
    // Dummy local memory passed to the allocator (possibly for alignment or info)
    int dummy[3] = {0, 0, 0};

    // Call the first virtual function (allocate) with size 0x408 and pointer to dummy.
    // The vtable at this+0x4 holds the function pointer.
    void* buffer = (*(void* (__thiscall**)(int, int*))(*(int*)(this + 4)))(0x408, dummy);

    // Zero out the allocated buffer
    memset(buffer, 0, 0x408);

    return buffer;
}