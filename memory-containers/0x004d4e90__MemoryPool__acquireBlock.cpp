// FUNC_NAME: MemoryPool::acquireBlock
struct BlockInfo {
    uint32_t data;      // +0x00: pointer or data (unused in success path)
    uint32_t size;      // +0x04: block size (unused in success path)
    uint32_t flags;     // +0x08: flags / next (unused in success path)
    uint32_t status;    // +0x0C: status code (0 = success, non-zero = error)
};

// Returns pointer to the output BlockInfo struct (same as outInfo)
BlockInfo* __thiscall MemoryPool::acquireBlock(BlockInfo* outInfo) {
    uint32_t basePtr;
    uint32_t endPtr;

    // Check if pool has any size remaining
    if (this->m_nBufferSize != 0) {
        basePtr = this->m_pBuffer;          // +0x00: base address of pool
        endPtr = getBufferEnd(basePtr);      // FUN_004d4e20: get end of free region

        if ((endPtr != 0) && (basePtr < endPtr)) {
            // Free space available – zero the region and indicate success
            outInfo->status = 0;             // +0x0C: mark as successful
            memClear(basePtr, endPtr - basePtr); // FUN_004d3c40: zero memory block
            return outInfo;
        }
    }

    // No space – return an empty/invalid block
    outInfo->data   = 0;
    outInfo->size   = 0;
    outInfo->flags  = 0;
    outInfo->status = 0;
    return outInfo;
}