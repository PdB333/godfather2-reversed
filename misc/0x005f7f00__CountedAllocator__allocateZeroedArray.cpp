// FUNC_NAME: CountedAllocator::allocateZeroedArray
void* __thiscall CountedAllocator::allocateZeroedArray(Allocator* alloc) {
    int count = *(int*)this;                     // +0x00: number of elements to allocate
    // Allocator::allocate(size, alignment/flags) at offset +0x10
    void* buffer = alloc->allocate(count * 12, 0);
    if (buffer) {
        memset(buffer, 0, count * 12);
        return buffer;
    }
    return nullptr;
}