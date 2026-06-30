// FUNC_NAME: StreamManager::releaseStreamBuffer
void StreamManager::releaseStreamBuffer(void)
{
    uint newCurrent;
    int* memMgr;
    int currentAlloc;
    int size;
    char streamType;

    // Set flags: mark as busy/active (bit 2)
    *(uint *)(this + 0x110) |= 4;

    // Conditional on bit 3 (stream loading state) set/clear bit 4 (stream processed)
    if ((*(uint *)(this + 0x110) >> 3) & 1) {
        *(uint *)(this + 0x110) |= 0x10; // Set processed flag
    } else {
        *(uint *)(this + 0x110) &= ~0x10; // Clear processed flag
    }
    // Clear the loading state bit 3
    *(uint *)(this + 0x110) &= ~8;
    // Reset an execution counter or buffer offset
    *(undefined4 *)(this + 0xd4) = 0;

    // Get stream type from associated data object (+0x1c -> +0x20)
    streamType = *(char *)(*(int *)(this + 0x1c) + 0x20);
    // Thread-local memory manager (EARS linear allocator)
    memMgr = (int *)TlsGetValue(g_MemoryManagerTlsIndex);
    currentAlloc = memMgr[8];   // +0x08: current allocation pointer
    size = streamType * 0x40 + 0x10; // 64*type + header
    newCurrent = currentAlloc + size;
    if (newCurrent > (uint)memMgr[0xb]) { // +0x2c: pool limit
        // Allocate from heap via manager's alloc function
        currentAlloc = ((int (*)(int))(*memMgr + 0x14))(size);
    } else {
        // Allocate from linear pool
        memMgr[8] = newCurrent;
    }
    // Store allocated scratch buffer
    *(int *)(this + 0x118) = currentAlloc;

    // Perform stream processing (flush/commit)
    FUN_00560670();

    // Retrieve buffer pointer again
    int bufferPtr = *(int *)(this + 0x118);
    memMgr = (int *)TlsGetValue(g_MemoryManagerTlsIndex);
    // Rewind the linear allocator to this buffer position
    memMgr[8] = bufferPtr;
    // If buffer is at end of pool, free it via manager's free function
    if (bufferPtr == memMgr[10]) { // +0x28: pool end
        ((void (*)(int))(*memMgr + 0x18))(bufferPtr);
    }
    // Clear buffer pointer
    *(undefined4 *)(this + 0x118) = 0;
}