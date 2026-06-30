// FUNC_NAME: Heap::deallocate
void __thiscall Heap::deallocate(void *block)
{
    uint *puVar1;      // Pointer to next block header
    int *nextFreePrev; // Next block's free list prev pointer? Actually used for removal
    int *nextFreeNext; // Next block's free list next pointer
    uint sizeAndFlags; // Size and flags of current block
    undefined4 uVar5;  // Temporary for some value
    char cVar6;        // Return value from some check function
    int in_EAX;        // Block to free (passed in EAX register)
    uint alignedSize;  // Aligned size without flags
    uint *blockBase;   // Base of block (header start)
    uint uVar9;        // Aligned size or new size before adjustment

    if (in_EAX == 0) {
        return;
    }

    // Block structure:
    // offset 0: size of previous block (or other data) - used for coalescing
    // offset 4: sizeAndFlags (lower 3 bits: bit0=allocated, bit1=prevBlockFree)
    // offset 8: free list next pointer (when free)
    // offset 12: free list prev pointer (when free)
    blockBase = (uint *)(in_EAX - 8);
    sizeAndFlags = *(uint *)(in_EAX - 4);
    alignedSize = sizeAndFlags & 0x7ffffff8;

    // Check if block belongs to the initial contiguous region (heap area #1)
    if ((alignedSize <= *(uint *)(this + 4)) &&
        (*(uint **)(this + 0x468) == (uint *)0x0 || (blockBase < *(uint **)(this + 0x468)))) {
        // Special path: block is from the initial pool (often the "top chunk")
        // Mark the block as free and connect it to the free list
        *(uint *)(this + 4) |= 1; // Set a flag indicating we have a free block here?
        uVar5 = *(undefined4 *)(this + (alignedSize >> 3) * 4);
        *(uint *)(in_EAX - 4) |= 0x80000004; // Set additional flags
        *(undefined4 *)(in_EAX + 4) = uVar5;
        *(uint **)(this + (alignedSize >> 3) * 4) = blockBase;
        return;
    }

    // Check if previous block is free (bit 1 of sizeAndFlags)
    if ((sizeAndFlags & 2) == 0) {
        // Previous block is NOT free - try to coalesce with neighbor blocks
        puVar1 = (uint *)((int)blockBase + alignedSize); // Pointer to next block
        uVar7 = *(uint *)((int)blockBase + alignedSize + 4) & 0x7ffffff8; // Size of next block

        // If this block is also free? Actually bit 0 (allocated flag) should be 0 for free
        if ((sizeAndFlags & 1) == 0) {
            // Coalesce with previous block (prev block is free, since its bit 1 is set for this block)
            // *blockBase contains the size of the previous block (footer)
            alignedSize = alignedSize + *blockBase;
            blockBase = (uint *)((int)blockBase - *blockBase);
            // Update size field of the merged block
            blockBase[1] = alignedSize | 1;
            *puVar1 = alignedSize;
            // Remove the previous block from the free list
            *(uint *)(blockBase[2] + 0xc) = blockBase[3];
            *(uint *)(blockBase[3] + 8) = blockBase[2];
        }

        // If next block is also free (bit 0 of its size field = 0)
        if ((*(char *)((int)puVar1 + uVar7 + 4) & 1) == 0) {
            // Coalesce with next block
            *(uint *)(puVar1[2] + 0xc) = puVar1[3];
            *(uint *)(puVar1[3] + 8) = puVar1[2];
            alignedSize = alignedSize + uVar7;
            // Update size fields
            blockBase[1] = alignedSize | 1;
            *(uint *)((int)blockBase + alignedSize) = alignedSize;
        } else {
            // Next block is not free - mark its previous-block free flag as false
            puVar1[1] = puVar1[1] & 0xfffffffe;
            *puVar1 = alignedSize;
        }

        // Insert the merged block into the appropriate free list
        if ((blockBase == *(uint **)(this + 0x440)) || (puVar1 == *(uint **)(this + 0x440))) {
            // Block touches the low boundary - update the boundary and possibly trim
            *(uint **)(this + 0x440) = blockBase;
            heapTrim(this); // FUN_00644ae0
        } else if (*(char *)(this + 0x46e) == '\0') {
            // Use a "best fit" insertion strategy
            insertIntoFreeList(this, blockBase); // FUN_00646c60
        } else {
            // Use a simple "stack" insertion (at the head of the small block list)
            blockBase[2] = this + 0x30;
            blockBase[3] = *(uint *)(this + 0x3c);
            *(uint **)(this + 0x3c) = blockBase;
            *(uint **)(*(uint *)(this + 0x3c) + 8) = blockBase;
        }

        // Check if we should trigger heap compaction
        if (((0xffff < alignedSize) &&
             (cVar6 = hasTrimmedRecently(), cVar6 != '\0')) &&
            (*(uint *)(this + 0x4c8) <= alignedSize)) {
            performTrim(this, *(undefined4 *)(this + 0x4cc)); // FUN_006484b0
        }
    } else {
        // Previous block IS free - this block is already free (double free anomaly)
        // Remove it from free list and return memory to OS
        uVar4 = *blockBase; // Size of previous block? Actually *blockBase is size field
        nextFreeNext = (int *)((int)blockBase + alignedSize + 8); // next block's free next pointer
        nextFreePrev = (int *)((int)blockBase + alignedSize + 12); // next block's free prev pointer
        // Remove the block from the free list (unlink)
        *(int *)(*nextFreeNext + 0xc) = *nextFreePrev;
        *(int *)(*nextFreePrev + 8) = *nextFreeNext;
        // Update statistics
        *(int *)(this + 0x48c) -= (uVar4 + 0x10 + alignedSize);
        *(int *)(this + 0x488) += -1;
        // Release memory to OS
        VirtualFree((LPVOID)((int)blockBase - uVar4), 0, MEM_RELEASE);
    }
    return;
}