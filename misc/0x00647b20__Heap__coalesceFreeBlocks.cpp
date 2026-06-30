// FUNC_NAME: Heap::coalesceFreeBlocks
void __thiscall Heap::coalesceFreeBlocks(Heap* this)
{
    uint* pBlock;
    uint uFlags;
    uint* pNext;
    int* ppBinHead;
    uint uBinMask;
    uint uBlockSize;
    bool bContinue;

    uBinMask = *(uint*)(this + 4); // +0x4: bitmask of non-empty bins
    if (uBinMask == 0) {
        // If no bins used, initialize allocator? (call to FUN_00644120)
        FUN_00644120(0, 0, 1, 0, 0, 0);
        return;
    }
    ppBinHead = (int*)(this + 8); // +0x8: array of bin heads (indexed by bin number)
    do {
        pBlock = (uint*)*ppBinHead;
        if (pBlock != (uint*)0x0) {
            *ppBinHead = 0; // Clear bin head, will reinsert coalesced blocks later
            do {
                // Clear the "in-use" flag (bit 2) from block flags
                pBlock[1] = pBlock[1] & 0x7ffffffb; // - BIT(2) field
                pNext = (uint*)pBlock[3]; // +0xC: pointer to next block in list

                // Compute offset to user data? Actually uVar6 = pBlock[1] & 0x7ffffff8
                uBlockSize = pBlock[1] & 0x7ffffff8; // Block size (aligned to 8 bytes?)
                uint* pRightBlock = (uint*)((int)pBlock + uBlockSize); // Pointer to block's right neighbor

                // Check if the left neighbor (previous block) is free
                if ((pBlock[1] & 1) == 0) { // Bit 0 indicates previous block free
                    // Merge with left block
                    uBlockSize = uBlockSize + *pBlock; // *pBlock is left block's size?
                    pBlock = (uint*)((int)pBlock - *pBlock); // Move to left block
                    pBlock[1] = uBlockSize | 1; // Mark previous as used? (OR 1)
                    *pRightBlock = uBlockSize; // Store size in right block's header?
                    // Update doubly linked list: remove left block from list
                    *(uint*)(pBlock[2] + 0xc) = pBlock[3]; // prev->next = next
                    *(uint*)(pBlock[3] + 8) = pBlock[2]; // next->prev = prev
                }

                // Check if the right neighbor (next block) is free
                if ((*(byte*)((int)pRightBlock + 4) & 1) == 0) { // Right block's flags have bit 0 free?
                    // Remove right block from list
                    *(uint*)(pRightBlock[2] + 0xc) = pRightBlock[3];
                    *(uint*)(pRightBlock[3] + 8) = pRightBlock[2];
                    uBlockSize = uBlockSize + *(uint*)((int)pRightBlock + 4) & 0x7ffffff8; // Add right block's size
                    pBlock[1] = uBlockSize | 1; // update size
                    *(uint*)((int)pBlock + uBlockSize) = uBlockSize; // Store size at end of block
                } else {
                    pRightBlock[1] = pRightBlock[1] & 0xfffffffe; // Mark right block as not free (clear bit 0)
                    *pRightBlock = uBlockSize; // Store current size in right block's first field?
                }

                // Check if this block is the "special" last block (at +0x440)
                if ((pBlock == *(uint**)(this + 0x440)) || (pRightBlock == *(uint**)(this + 0x440))) {
                    *(uint**)(this + 0x440) = pBlock; // Update last block pointer
                    // Make block a circular list (only itself)
                    pBlock[3] = (uint)pBlock;
                    pBlock[2] = (uint)pBlock;
                    pBlock[1] = uBlockSize | 1;
                    *(uint*)((int)pBlock + uBlockSize) = uBlockSize;
                    if (*(char*)(this + 0x46c) == '\0') {
                        // +0x468: pointer used for linear search? Compute from block size
                        *(uint*)(this + 0x468) = 
                            (*(uint*)(*(int*)(this + 0x440) + 4) >> 1 & 0x3ffffffc) +
                            *(int*)(this + 0x440);
                    }
                } else {
                    // Insert block into the general free list (circular doubly linked list at +0x30)
                    uint* listHead = *(uint**)(this + 0x3c); // +0x3c: head of free list
                    pBlock[2] = (uint)(this + 0x30); // prev = &this->freeList
                    pBlock[3] = (uint)listHead; // next = old head
                    *(uint**)(this + 0x3c) = pBlock; // update head
                    *(uint**)(listHead + 8) = pBlock; // old head->prev = new block
                }

                pBlock = pNext; // Advance to next block in the bin
            } while (pNext != (uint*)0x0);
        }
        // Move to next bin
        bContinue = (ppBinHead != (int*)(this + (uBinMask >> 3) * 4)); // Until we've processed all bins
        ppBinHead = ppBinHead + 1;
    } while (bContinue);

    // Clear the "non-empty bin" mask
    *(uint*)(this + 4) = *(uint*)(this + 4) & 0xfffffffe; // Clear bit 0? Or the entire mask?
    return;
}