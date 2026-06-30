// FUNC_NAME: MemoryBuffer::resizeToDefault
void MemoryBuffer::resizeToDefault(BufferInfo* pInfo) {
    // pInfo has two fields:
    //   +0x00: void* pData   (pointer to element array)
    //   +0x04: int   count   (number of elements, each 8 bytes)

    void* oldData = pInfo->pData;          // Original data pointer
    int   oldCount = pInfo->count;         // Original element count (stored as int, not pointer)

    // Allocate new buffer of 0x20 bytes (default capacity: 4 elements x 8 bytes)
    // FUN_0064b810(size, &ptr) updates the pointer to a new allocation
    FUN_0064b810(0x20, &pInfo->pData);

    // If no data existed, use a static empty buffer
    if (oldData == nullptr) {
        oldData = &DAT_0120546e;           // Default empty data (likely a global empty container)
    }

    // Copy old content into the new buffer (size = oldCount * 8 bytes)
    // FUN_0064b810(size, src) copies from src to the newly allocated buffer (destination is assumed known)
    FUN_0064b810(oldCount * 8, oldData);
}