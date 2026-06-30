// FUNC_NAME: ArrayAllocator::resizeBuffer
uint __thiscall ArrayAllocator::resizeBuffer(ArrayAllocator *this) {
    // Fields:
    // +0x0C: data pointer (void*)
    // +0x10: count (uint32)
    uint currentCount = this->count;
    if (currentCount > 0x3FF) {
        // Maximum capacity exceeded: return error (low byte of in_EAX)
        return 0;
    }
    // First allocation/callback: possibly store new size or allocate metadata (size=10)
    FUN_0064b810(10, &currentCount);
    // Second allocation: allocate space for currentCount elements of 8 bytes each
    uint newData = FUN_0064b810(currentCount * 8, this->data);
    return newData;
}