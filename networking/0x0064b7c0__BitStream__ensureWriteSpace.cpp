// FUNC_NAME: BitStream::ensureWriteSpace
uint __fastcall BitStream::ensureWriteSpace(int this, int numBits) {
    int currentAllocatedSize; // eax
    void* newBuffer;
    uint newAllocatedSize;

    // Calculate new required size in bytes: ((numBits + 7 + mWriteOffsetBits) >> 3) + 0x5DC (MTU overhead)
    newAllocatedSize = (numBits + 7 + *(uint*)(this + 0x30) >> 3) + 0x5DC;

    if (*(uint*)(this + 0x10) < newAllocatedSize) {
        // Need to grow if allowed
        if (*(char*)(this + 0x14) != 0) {
            // Allow reallocation
            *(uint*)(this + 0x10) = newAllocatedSize;
            newBuffer = _realloc(*(void**)(this + 0xC), newAllocatedSize);
            *(void**)(this + 0xC) = newBuffer;
            // Update both bit capacities to new value (bytes * 8)
            *(int*)(this + 0x2C) = newAllocatedSize * 8;
            *(int*)(this + 0x30) = newAllocatedSize * 8;
            return CONCAT31((int3)((uint)(newAllocatedSize * 8) >> 8), 1);
        }
    } else {
        // No reallocation needed, just update allocated size
        *(uint*)(this + 0x10) = newAllocatedSize;
    }
    // Set some flag (perhaps "needsSync" or similar)
    *(char*)(this + 0x1C) = 1;
    // Return current bit capacity with lower byte cleared
    return *(uint*)(this + 0x30) & 0xFFFFFF00;
}