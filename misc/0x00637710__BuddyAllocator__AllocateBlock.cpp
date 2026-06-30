// FUNC_NAME: BuddyAllocator::AllocateBlock
// Address: 0x00637710
// Role: Allocate a block of power-of-two size from a buddy allocator.
// The allocator state: first int is total remaining size or current offset? 
// Structure: [0x00] m_totalSize (int) -- original total capacity
//            [0x04] m_freeSlots[] (int array) -- sizes of free blocks per level?
// Parameters: this (ECX), int baseAddress (param_1), int* pSize (param_2), int* pOffset (param_3)
// Returns: void, but modifies pSize to the allocated block bitmask and pOffset to the offset from baseAddress.
// The algorithm finds the smallest power-of-two block that fits in a contiguous free region.
// On success, pSize is set to 1 << level, pOffset is set to the offset within the pool.
// On failure, pSize is set to 0.

struct BuddyAllocator {
    int m_totalSize;       // +0x00
    int m_freeSlots[1];    // +0x04 - actually variable length based on levels
};

void __thiscall BuddyAllocator::AllocateBlock(BuddyAllocator* this, int baseAddress, int* pSize, int* pOffset)
{
    // piVar1 = pSize (original pointer)
    int* piVar1 = pSize;
    // iVar4 = this->m_totalSize (current free size status)
    int iVar4 = this->m_totalSize;
    // iVar2 = (iVar4 != 0) ? 0 : -1; init to best-fit level
    int iVar2 = (iVar4 != 0) - 1;
    // iVar3 = *pSize (requested size? or total capacity)
    int iVar3 = *pSize;

    // Overwrite pSize pointer with the current offset? (confusing; probably means we're walking the free list)
    pSize = (int*)iVar4;

    // If current free space is less than total capacity, search for a block
    if (iVar4 < iVar3) {
        iVar3 = 0; // level index
        int* piVar5 = &this->m_freeSlots[0]; // pointer to free slot array
        do {
            int blockSize = 1 << (iVar3 & 0x1f); // power-of-two at this level
            // If total capacity < blockSize, can't allocate, break
            if (*piVar1 < blockSize) break;
            // If this free slot is used (size > 0) and current cumulative free size <= blockSize
            if ((0 < *piVar5) && 
                (iVar4 = iVar4 + *piVar5, blockSize <= iVar4)) {
                iVar2 = iVar3 + 1; // record this level
                pSize = (int*)iVar4; // update pointer to current cumulative free offset
            }
            piVar5++; // next free slot
            iVar3++;
        } while (iVar4 < *piVar1); // continue until we've scanned all possible slots up to total capacity
    }

    // Compute offset from base address
    *pOffset = baseAddress - (int)pSize;
    if (iVar2 != -1) {
        // Success: set pSize to the allocated block bitmask
        *piVar1 = 1 << (iVar2 & 0x1f);
        return;
    }
    // Failure: set pSize to 0
    *piVar1 = 0;
}