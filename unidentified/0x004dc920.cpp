// FUN_004dc920: BufferAllocator::reallocate

uint * BufferAllocator::reallocate() {
    short endMarker;
    uint *globalFreeList;
    uint lastBlock;

    // Only proceed if the buffer is currently allocated (flag at +0x04)
    if (this[1] != 0) {
        // Find the end of a null-terminated list of short IDs (global free list)
        globalFreeList = &DAT_00e36ef4;
        do {
            endMarker = (short)*globalFreeList;
            ++globalFreeList;
        } while (endMarker != 0);

        // Current buffer handle is stored at offset 0
        uint currentHandle = this[0];

        // Try to allocate a new block; keep the last successful allocation
        uint allocResult = FUN_004dc860();
        if (allocResult != 0) {
            do {
                lastBlock = allocResult;
                allocResult = FUN_004dc860();
            } while (allocResult != 0);

            // If a new block was obtained and its handle is larger than current,
            // copy half the difference (likely number of elements) from old to new
            if ((lastBlock != 0) && (currentHandle < lastBlock)) {
                FUN_004dba00(currentHandle, (int)(lastBlock - currentHandle) >> 1);
                return this;
            }
        }
    }

    // Allocation failed or buffer was empty; zero out the three fields
    this[0] = 0;  // +0x00: handle
    this[2] = 0;  // +0x08: reserved
    this[1] = 0;  // +0x04: valid flag
    return this;
}