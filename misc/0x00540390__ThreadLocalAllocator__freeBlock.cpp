// FUNC_NAME: ThreadLocalAllocator::freeBlock
void ThreadLocalAllocator::freeBlock(void* block) {
    // Call debug/validation function
    debugCheck();

    if (block == nullptr) {
        return;
    }

    // Get thread-local storage for this allocator
    ThreadLocalAllocator* tlsData = (ThreadLocalAllocator*)TlsGetValue(gTlsIndex); // DAT_01139810

    // Check if free list is full (currentCount >= maxCount)
    if (tlsData->currentCount <= tlsData->maxCount) { // +0x9c <= +0x34
        // Error: free list overflow or double free
        assertOrError(0xc, block, 0xd); // FUN_00aa21e0
        return;
    }

    // Increment count and push block onto free list
    tlsData->currentCount++; // +0x9c
    *(void**)block = tlsData->freeListHead; // +0x98: next pointer stored at block start
    tlsData->freeListHead = block; // +0x98
}