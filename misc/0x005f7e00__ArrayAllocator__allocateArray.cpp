// FUNC_NAME: ArrayAllocator::allocateArray
void* __fastcall ArrayAllocator::allocateArray(void* this) {
    // Read object count from first member (offset 0x00)
    int count = *(int*)this;

    // Get allocator function pointer from offset 0x10
    // This function is expected to allocate memory with a given size and allocation info
    using AllocatorFunc = void* (*)(int size, void* allocInfo);
    AllocatorFunc allocFunc = *(AllocatorFunc*)((char*)this + 0x10);

    // Allocation info structure (12 bytes, zeroed)
    struct AllocHint { int field0, field4, field8; } hint = {0, 0, 0};

    // Allocate memory for 'count' objects of 12 bytes each
    void* buffer = allocFunc(count * 12, &hint);

    // Zero out the allocated memory
    memset(buffer, 0, count * 12);
    return buffer;
}