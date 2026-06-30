// FUNC_NAME: MemoryPool::allocate

// Reconstructed from 0x0056e5e0 - Memory pool allocator with compaction and free list management.
// Offsets relative to this: +0x14: active list head, +0x18: active list tail, +0x10: free list head,
// +0x1c: allocated count, +0x20: block size base, +0x24: total capacity, +0x28: bump offset,
// +0x2c: remnant offset, +0x30: hash bucket array (indexed by node->bucketIndex * 4), +0x1030: free node count.

struct HeapBlockNode {
    HeapBlockNode* nextBlock;        // +0x00
    HeapBlockNode* prevBlock;        // +0x04
    int bucketIndex;                 // +0x08 (used to index into hash table at this+0x30)
    int blockSize;                   // +0x0C
    HeapBlockNode* hashNext;         // +0x10
    HeapBlockNode* hashPrev;         // +0x14
    // There are additional fields at offsets 0x20, 0x24, 0x28 (pointers to attached objects)
    // These are used to check if the block is still referenced.
    void* attachedObject1;           // +0x20
    void* attachedObject2;           // +0x24
    void* attachedObject3;           // +0x28
    // The byte at +9 of each attached object indicates if it is active.
    // ... user data follows
};

int __thiscall MemoryPool::allocate(uint requestedSize, int* outOffset) {
    HeapBlockNode* currentNode;
    int totalFreedSize;
    bool bObj1Active, bObj2Active, bObj3Active;
    int accumulatedSize = 0;

    *outOffset = 0;

    // If current bump offset + requested size exceeds capacity, try to reclaim blocks
    if (mCapacity < (mBumpOffset + requestedSize)) {
        // Only attempt compaction if the current active block has enough free space after it?
        // Actually, the loop walks the active list and moves blocks that are not referenced to the free list.
        // The condition checks if the active list head's end address is <= some threshold.
        if ((uint)(mBlockSizeBase + mBumpOffset) <= ((HeapBlockNode*)mActiveListHead)->blockSize) {
            do {
                currentNode = (HeapBlockNode*)mActiveListHead;
                mActiveListHead = currentNode->nextBlock;
                currentNode->prevBlock = 0;
                // Insert at head of free list
                currentNode->nextBlock = (HeapBlockNode*)mFreeListHead;
                if (mFreeListHead) {
                    ((HeapBlockNode*)mFreeListHead)->prevBlock = currentNode;
                }
                mFreeListHead = currentNode;
                currentNode->prevBlock = 0;
                // Continue until we've passed the area that is beyond the current end
            } while ((uint)(mBlockSizeBase + mBumpOffset) <= ((HeapBlockNode*)mActiveListHead)->blockSize);
        }
        // Reset remnant and bump offset after compaction
        mRemnantOffset = 0;
        mBumpOffset = 0;
    }

    // Now attempt to allocate from the free list by merging and splitting
    if (mRemnantOffset < requestedSize) {
        accumulatedSize = 0;
        do {
            currentNode = (HeapBlockNode*)mActiveListHead;
            // If no active blocks left, or the block's end address doesn't match the bump offset, stop
            if ((currentNode == 0) ||
                ((uint)currentNode->blockSize < (uint)(mBlockSizeBase + mBumpOffset))) break;

            // Check if this block is still in use by any attached objects
            // The three pointers at offsets 0x20,0x24,0x28 point to objects; if any has its +9 byte nonzero, block is in use.
            bObj1Active = (currentNode->attachedObject1 != 0) && (*(char*)((int)currentNode->attachedObject1 + 9) != '\0');
            bObj2Active = (currentNode->attachedObject2 != 0) && (*(char*)((int)currentNode->attachedObject2 + 9) != '\0');
            bObj3Active = (currentNode->attachedObject3 != 0) && (*(char*)((int)currentNode->attachedObject3 + 9) != '\0');
            if (bObj1Active || bObj2Active || bObj3Active) {
                // Block is still referenced; cannot reclaim it yet
                mRemnantOffset += accumulatedSize;
                return 0; // allocation fails
            }

            // Block is unreferenced: move it from active list to free list
            mActiveListHead = (int)currentNode->nextBlock;
            if (currentNode->nextBlock) {
                currentNode->nextBlock->prevBlock = 0;
            }
            mFreeNodeCount--; // offset 0x1030

            // Insert into free list (as head, single list)
            currentNode->nextBlock = (HeapBlockNode*)mFreeListHead;
            currentNode->prevBlock = 0;
            if (mFreeListHead) {
                ((HeapBlockNode*)mFreeListHead)->prevBlock = currentNode;
            }
            mTotalAllocatedCount++; // offset 0x1c
            mFreeListHead = (int)currentNode;

            // Remove from hash bucket chain
            if ((HeapBlockNode*)mHashBuckets[currentNode->bucketIndex] == currentNode) {
                mHashBuckets[currentNode->bucketIndex] = currentNode->hashNext;
            } else {
                if (currentNode->hashNext != 0) {
                    currentNode->hashNext->hashPrev = currentNode->hashPrev;
                }
                if (currentNode->hashPrev != 0) {
                    currentNode->hashPrev->hashNext = currentNode->hashNext;
                }
            }
            accumulatedSize += currentNode->blockSize;
        } while ((uint)(mRemnantOffset + accumulatedSize) < requestedSize);

        if (accumulatedSize != 0) {
            mRemnantOffset = mRemnantOffset + (accumulatedSize - requestedSize);
        }
    } else {
        mRemnantOffset -= requestedSize;
    }

    // Success: set output offset and advance bump pointer
    *outOffset = mBumpOffset;
    mBumpOffset += requestedSize;
    return 1;
}