// FUNC_NAME: MemoryManager::validateBlock
int MemoryManager::validateBlock(uint blockPtr) {
    // +0x4e8: pointer to a critical section (or custom lock with debug info)
    LPCRITICAL_SECTION criticalSection = *(LPCRITICAL_SECTION*)(this + 0x4e8);
    if (criticalSection != nullptr) {
        EnterCriticalSection(criticalSection);
        // Manipulate debug info as a counter: increment the debug block's type field
        criticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&criticalSection[1].DebugInfo->Type + 1);
    }

    uint headerSize = *(uint*)(blockPtr + 4) & 0x7ffffff8; // +4: block size field, lower 3 bits flags
    uint* blockEnd = (uint*)(headerSize + blockPtr);           // pointer to the end of the block (next block's header)
    int errorCounter = FUN_00644d30(blockPtr);                 // initial error count from helper

    // Check flag at next block's header (offset blockPtr+headerSize+4, bit0)
    errorCounter += (*(byte*)((*(uint*)(blockPtr + 4) & 0x7ffffff8) + 4 + blockPtr) & 1);
    // Check flag in current block (bit1 of size field)
    errorCounter += (*(uint*)(blockPtr + 4) >> 1 & 1);

    if (headerSize < 16) {
        // For small blocks, only check if size >4
        errorCounter += (uint)(4 < headerSize);
    } else {
        int iVar6;
        // Check if this is the sentinel block (+0x440)
        if (blockPtr == *(uint*)(this + 0x440)) {
            iVar6 = 0;
        } else {
            // Check the next block's next block flag (free?)
            if ((*(byte*)((blockEnd[1] & 0x7ffffff8) + 4 + (int)blockEnd) & 1) != 0)
                iVar6 = 0;
            else
                iVar6 = 1;
        }

        uint prevBlock = *(uint*)(blockPtr + 8);  // +8: previous block pointer
        uint nextBlock = *(uint*)(blockPtr + 0xc); // +0xc: next block pointer

        // Various integrity checks
        errorCounter += (uint)((blockPtr & 7) != 0);                      // alignment?
        errorCounter += (uint)(*blockEnd != headerSize);                  // boundary size mismatch
        errorCounter += (uint)((byte)~*(byte*)(blockPtr + 4) & 1);       // complement of flag?
        errorCounter += iVar6;
        errorCounter += (uint)(*(uint*)(nextBlock + 8) != blockPtr);     // next->prev != blockPtr
        errorCounter += (uint)(*(uint*)(prevBlock + 0xc) != blockPtr);   // prev->next != blockPtr

        if (blockPtr == nextBlock || blockPtr == prevBlock) {
            // Self-referential list; add check for prev==next
            errorCounter += (uint)(prevBlock != nextBlock);
            // Add check for not being the sentinel
            errorCounter += (uint)(blockPtr != *(uint*)(this + 0x440));
        }
    }

    if (criticalSection != nullptr) {
        // Decrement the debug info counter (restore)
        criticalSection[1].DebugInfo = 
            (PRTL_CRITICAL_SECTION_DEBUG)((int)&criticalSection[1].DebugInfo[-1].SpareWORD + 1);
        LeaveCriticalSection(criticalSection);
    }

    return errorCounter;
}