// FUNC_NAME: ObjectPool::getEntry
// Returns a pointer to a pool entry by index, or null if out of range (max 4096 entries, each 0x38 bytes).
// Base address of the pool is at DAT_011a0f28.
uint8_t* ObjectPool::getEntry(uint32_t index) {
    if (index < 0x1000) {
        // Each entry is 0x38 bytes
        return &DAT_011a0f28 + index * 0x38;
    }
    return nullptr;
}