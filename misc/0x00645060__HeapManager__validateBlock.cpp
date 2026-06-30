// FUNC_NAME: HeapManager::validateBlock
// Function address: 0x00645060
// Role: Validates a memory block in the heap, checking integrity and flags.
// Uses a critical section for thread safety.
// Offsets: this+0x4e8 = critical section pointer, this+0x440 = heap base pointer.

int HeapManager::validateBlock(int *blockPtr) {
    LPCRITICAL_SECTION criticalSection = *(LPCRITICAL_SECTION *)(this + 0x4e8);
    if (criticalSection != nullptr) {
        EnterCriticalSection(criticalSection);
        // Increment lock count (debug info)
        criticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&(criticalSection[1].DebugInfo)->Type + 1);
    }

    int result = checkBlock(blockPtr); // FUN_00644d30 - checks block validity
    if (result == 0 && (blockPtr[1] & 2) == 0) {
        // Compute next block address: current block + size (masked)
        int nextBlock = (blockPtr[1] & 0x7ffffff8) + (int)blockPtr;
        // Check low bit of next block's size field (byte at offset 4)
        uint flag = (~(*(byte *)(nextBlock + 4)) & 1);
        if ((blockPtr[1] & 1) == 0) {
            // If current block is free, check if it points back to itself (coalescing?)
            int *prevCheck = (int *)((int)blockPtr + ((*(uint *)((int)blockPtr + (4 - *blockPtr)) & 0x7ffffff8) - *blockPtr));
            flag += (prevCheck != blockPtr);
        }
        result = checkBlock(nextBlock) + flag;
        if (result == 0 && nextBlock == *(int *)(this + 0x440)) {
            // If next block is the heap base, check its size and flag
            result = ((*(uint *)(nextBlock + 4) & 0x7ffffff8) < 0x10) + (~(*(byte *)(nextBlock + 4)) & 1);
        }
    }

    if (criticalSection != nullptr) {
        // Decrement lock count
        criticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&criticalSection[1].DebugInfo[-1].SpareWORD + 1);
        LeaveCriticalSection(criticalSection);
    }
    return result;
}