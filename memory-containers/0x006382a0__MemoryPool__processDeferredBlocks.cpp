// FUNC_NAME: MemoryPool::processDeferredBlocks
// Function address: 0x006382a0
// Purpose: Moves blocks from a pending list (head at +0x48) to a free list (head at +0x0C of object at +0x10),
//          copying 8 bytes from the block's source pointer to the block itself, then marking the block as free.
//          Iteration stops when the block's source pointer is below a threshold (passed in EDI by caller).

void __fastcall MemoryPool::processDeferredBlocks(int thisPtr)
{
    // Node structure layout (each node is a pool block):
    // +0x00: next pointer (linked list)
    // +0x04: flags/size (byte at +0x04 is set to 10 here; byte at +0x05 is cleared)
    // +0x08: source pointer (to data to copy)
    // +0x0C: data copy destination (first 4 bytes of copied data)
    // +0x10: second 4 bytes of copied data
    // Total node size: 0x14 (20 bytes) likely

    // MemoryPool object layout:
    // +0x00: unknown
    // +0x10: pointer to a central allocator (struct with free list head at +0x0C)
    // +0x48: head of pending list (deferred blocks to process)

    PoolBlock* currentBlock = *(PoolBlock**)(thisPtr + 0x48);
    
    // unaff_EDI is a threshold address set by the caller (likely a high watermark)
    // This loop only processes blocks whose source pointer is >= threshold.
    while (currentBlock != nullptr && (PoolBlock* threshold = ???; currentBlock->source >= threshold))
    {
        // Copy 8 bytes from source pointer into the block's data area
        currentBlock->data[0] = *(unsigned int*)currentBlock->source;
        currentBlock->data[1] = *(unsigned int*)(currentBlock->source + 4);
        // Update the source pointer to point to the start of the copied data
        currentBlock->source = currentBlock->data;

        // Remove currentBlock from the pending list (advance head to next)
        *(PoolBlock**)(thisPtr + 0x48) = currentBlock->next;

        // Insert currentBlock into the free list of the central allocator
        // Central allocator is at *(thisPtr+0x10), its free list head is at +0x0C
        void* centralAlloc = *(void**)(thisPtr + 0x10);
        PoolBlock* freeListHead = *(PoolBlock**)((int)centralAlloc + 0x0C);
        currentBlock->next = freeListHead;
        *(PoolBlock**)((int)centralAlloc + 0x0C) = currentBlock;

        // Mark the block as free: clear byte at +0x05, set byte at +0x04 to 10 (maybe size class or flags)
        *(unsigned char*)((int)currentBlock + 5) = 0;
        *(unsigned char*)(currentBlock + 1) = 10; // +0x04

        // Advance to next block in pending list (the head was already updated above)
        currentBlock = *(PoolBlock**)(thisPtr + 0x48);
    }
}