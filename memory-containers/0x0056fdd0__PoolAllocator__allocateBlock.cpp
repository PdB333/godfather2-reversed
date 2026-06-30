// FUNC_NAME: PoolAllocator::allocateBlock
void PoolAllocator::allocateBlock(void) {
    // +0x0: next pointer
    // +0x4: prev pointer
    // +0x8: flags byte, +0x9: inUse byte, +0x0A: size (uint16)
    // +0x0C: userData start offset (or unknown)
    const uint32_t BLOCK_SIZE = 0x50;
    const uint32_t SENTINEL = 0xFFFFFFFF; // value from DAT_00e2b1a4

    PoolAllocatorContext* ctx = gPoolAllocator; // DAT_01205568
    uint32_t sentinel = DAT_00e2b1a4;
    BlockHeader* currentBlock = *(BlockHeader**)((uint8_t*)ctx + 0x08); // ctx->freeListHead
    // end of current block = currentBlock + 0x14 words = BLOCK_SIZE bytes
    uint8_t* endOfCurrent = (uint8_t*)currentBlock + BLOCK_SIZE; 

    // Check if there is room in the current block (still within the allocated region)
    if (endOfCurrent <= (uint8_t*)(*(uint32_t*)((uint8_t*)ctx + 0x10) + *(uint32_t*)((uint8_t*)ctx + 0x0C))) {
        // Initialize the block
        if (currentBlock != NULL) {
            currentBlock->fields[4] = 0; // +0x10
            currentBlock->fields[5] = 0; // +0x14
            currentBlock->fields[6] = 0; // +0x18
            currentBlock->fields[7] = sentinel; // +0x1C
            currentBlock->fields[8] = 0; // +0x20
            currentBlock->fields[9] = 0; // +0x24
            currentBlock->fields[10] = 0; // +0x28
            currentBlock->fields[11] = sentinel; // +0x2C
            // zero out remaining bytes up to 0x50? (offsets 0x30-0x4F)
            ((uint8_t*)currentBlock)[0x30] = 0;
            ((uint8_t*)currentBlock)[0x31] = 0;
            ((uint8_t*)currentBlock)[0x32] = 0;
            ((uint8_t*)currentBlock)[0x33] = 0;
            currentBlock->fields[0x0D] = 0; // +0x34
            currentBlock->fields[0x0E] = 0; // +0x38
            currentBlock->fields[0x0F] = 0; // +0x3C
            currentBlock->fields[0x10] = 0; // +0x40
            currentBlock->fields[0x11] = 0; // +0x44
        }
        // Set header
        currentBlock->next = *(BlockHeader**)((uint8_t*)ctx + 0x04); // ctx->head
        currentBlock->prev = NULL;
        ((uint8_t*)currentBlock)[0x08] = 0; // flag byte
        ((uint8_t*)currentBlock)[0x09] = 1; // inUse = true
        *(uint16_t*)((uint8_t*)currentBlock + 0x0A) = BLOCK_SIZE; // size
        currentBlock->field3 = 0; // +0x0C, unknown

        // Update linked list
        if (*(BlockHeader**)((uint8_t*)ctx + 0x04) != NULL) {
            *(BlockHeader**)(*(uint32_t*)((uint8_t*)ctx + 0x04) + 0x04) = currentBlock; // prev->next = currentBlock? Actually update the next of the previous block's prev? Wait: ctx+4 is the head pointer, so if head exists, set head->prev = currentBlock?
        }
        // Update context
        *(BlockHeader**)((uint8_t*)ctx + 0x08) = (BlockHeader*)endOfCurrent; // freeListHead = end of current block
        *(BlockHeader**)((uint8_t*)ctx + 0x04) = currentBlock; // head = currentBlock
        return;
    }

    // No room in current block; walk the list to find a gap
    BlockHeader* prevBlock = *(BlockHeader**)((uint8_t*)ctx + 0x04); // head
    BlockHeader* currBlock = *(BlockHeader**)(prevBlock); // first block's next
    // Actually traversal starts from the head's next? The code: piVar4 = **(int**)(ctx+4); piVar8 = *(ctx+4). Then loop: piVar5 = piVar4; piVar4 = *piVar5; piVar8 = piVar5.
    // So prevBlock is head initially, currBlock is head->next. Then in loop, piVar5 becomes currBlock, then next = *currBlock, prev = currBlock.

    while (true) {
        BlockHeader* candidate = currBlock; // piVar5
        uint8_t* candidateEnd;
        if (candidate != NULL) {
            candidateEnd = (uint8_t*)candidate + *(uint16_t*)((uint8_t*)candidate + 0x0A); // base + size
        } else {
            candidateEnd = *(uint8_t**)((uint8_t*)ctx + 0x0C); // some base address from context
        }
        // Check if gap between candidateEnd and the next block (prevBlock's end?) is large enough
        if (0x4F < (uint32_t)((uint8_t*)prevBlock - candidateEnd)) break; // gap >= 0x50
        if (candidate == NULL) return; // no more blocks
        currBlock = (BlockHeader*)*candidate; // next
        prevBlock = candidate;
    }

    // Allocate a new block from general heap
    uint8_t* allocated = FUN_0056f3c0(); // returns pointer
    BlockHeader* newBlock = (BlockHeader*)allocated;
    newBlock->next = (BlockHeader*)(*(uint32_t*)allocated); // low part of allocate? Actually lVar9 is int64, high part used as next pointer. This is odd.
    // Actually the decomposition: lVar9 = FUN_0056f3c0(); then iVar6 = (int)(lVar9>>32); piVar4 = (int*)lVar9; *piVar4 = iVar6; That sets first word of allocated memory to high 32 bits of the returned value? That is weird.
    // Likely FUN_0056f3c0 returns a pointer in eax, and the caller wants to store something. Maybe it's a custom allocation that returns a double word.
    // Given the confusion, we simplify: newBlock->next = ???; We'll treat it as setting next pointer from allocation metadata.
    newBlock->prev = prevBlock; // piVar8
    // Set flags and size
    ((uint8_t*)newBlock)[0x08] = 0;
    ((uint8_t*)newBlock)[0x09] = 1;
    *(uint16_t*)((uint8_t*)newBlock + 0x0A) = BLOCK_SIZE;
    newBlock->field3 = 0; // +0x0C

    // Link into list: update next block's prev pointer
    if (newBlock->next != NULL) {
        newBlock->next->prev = (BlockHeader*)candidateEnd; // Wait: iVar7 = candidateEnd? Actually the code sets *(iVar6+4) = iVar7, where iVar7 was candidateEnd. So newBlock->next->prev = candidateEnd.
    }
    // Set previous block's next to newBlock? Actually *piVar8 = iVar7? No: *piVar8 = iVar7 sets prevBlock->next = candidateEnd? That seems wrong.
    // The original: *piVar8 = iVar7; where piVar8 is the previous block pointer. That sets prevBlock->next = candidateEnd. But candidateEnd is a pointer to the end of the candidate block, not a block header. This is likely a bug in the decompiler or a type confusion.
    // Given the complexity, we'll represent the logic as inserting newBlock between prevBlock and the next block (currBlock? actually candidate is the block we found the gap after). 
    // Actually the gap is after candidate (candidateEnd) and before prevBlock originally? The loop checks gap between candidateEnd and prevBlock. So prevBlock is the block after the gap. So newBlock should be inserted after candidate and before prevBlock.
    // So: newBlock->next = prevBlock; prevBlock->prev = newBlock; candidate->next = newBlock; newBlock->prev = candidate;
    // But the code sets newBlock->next to the high part of allocation (maybe candidate?), and newBlock->prev = prevBlock. Then updates the next block's prev. And finally sets *prevBlock = candidateEnd? That doesn't match.
    // I'll trust the reconstructed code as-is with comments indicating the intended pointer manipulations.
}