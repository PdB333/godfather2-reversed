// FUNC_NAME: BlockCache::accessBlock
void BlockCache::accessBlock(uint* keyPtr) {
    uint key = *keyPtr;
    uint hashIndex = key & 0x3FF;               // hash table size 1024
    BlockHeader* foundBlock = nullptr;
    BlockHeader* prevInBucket = nullptr;

    // Search for block with matching key in hash table
    for (uint* bucketPtr = &hashBuckets[hashIndex]; *bucketPtr != 0; bucketPtr = &((BlockHeader*)*bucketPtr)->hashNext) {
        BlockHeader* current = (BlockHeader*)*bucketPtr;
        if (current->key == key) {
            foundBlock = current;
            break;
        }
        prevInBucket = current;
    }

    if (foundBlock) {
        // Block found: remove from its current LRU position and move to head
        // Remove from LRU list
        foundBlock->freePrev->freeNext = foundBlock->freeNext;
        foundBlock->freeNext->freePrev = foundBlock->freePrev;
        // Insert at head of LRU list (head sentinel at this+0x8018, tail at this+0x8028)
        foundBlock->freePrev = (BlockHeader*)(this + 0x8018);  // head sentinel
        foundBlock->freeNext = (BlockHeader*)*(uint32*)(this + 0x8028); // old head's next
        *(BlockHeader**)(this + 0x8028) = foundBlock;            // update head to point to foundBlock
        foundBlock->freeNext->freePrev = foundBlock;
    } else {
        // Key not in cache: evict tail block (oldest used)
        BlockHeader* evictBlock = *(BlockHeader**)(this + 0x800C); // tail of LRU list
        // Remove from LRU list
        evictBlock->freePrev->freeNext = evictBlock->freeNext;
        evictBlock->freeNext->freePrev = evictBlock->freePrev;
        // Insert evictBlock at head
        evictBlock->freePrev = (BlockHeader*)(this + 0x8018);
        evictBlock->freeNext = (BlockHeader*)*(uint32*)(this + 0x8028);
        *(BlockHeader**)(this + 0x8028) = evictBlock;
        evictBlock->freeNext->freePrev = evictBlock;

        // Remove evictBlock from its hash bucket chain
        uint evictKey = evictBlock->key;
        uint evictHash = evictKey & 0x3FF;
        uint32* evictBucket = &hashBuckets[evictHash];
        while (*evictBucket != (uint32)evictBlock) {
            if (*evictBucket == 0) break; // not found, shouldn't happen
            evictBucket = &((BlockHeader*)*evictBucket)->hashNext;
        }
        if (*evictBucket == (uint32)evictBlock) {
            *evictBucket = evictBlock->hashNext;
        }

        // Relinquish old key (decrement refcount if it existed)
        if (evictKey != 0) {
            refCountDec(evictKey);          // FUN_0065a440 - decrements global refcount
        }

        // Assign new key to evicted block
        evictBlock->key = key;
        if (key != 0) {
            refCountInc(key);               // FUN_0065a440 but increments? Actually code shows refcount inc at offset+0xe
        }
        evictBlock->flags = 0;              // clear flags
        // Insert evictBlock into hash bucket for new key
        evictBlock->hashNext = hashBuckets[hashIndex];
        hashBuckets[hashIndex] = (uint32)evictBlock;

        foundBlock = evictBlock;
    }

    // Now process the bitmap (global bitmap manager referenced by in_EAX)
    // The in_EAX pointer is the global bitmap manager singleton (g_BlockBitmap)
    uint* bitPosPtr = (uint*)foundBlock->something; // foundBlock[1] is offset 4
    BitmapManager* bitmapMgr = g_BlockBitmap; // in_EAX
    uint bitIndex = bitmapMgr->nextBitPosition; // offset 0x18? Actually bitmapMgr->bitPos
    // Adjust bit index based on something from bitPosPtr? The code does:
    // param_2 = (uint*)foundBlock->something; // puVar14[1]
    // FUN_0064b810(10, &param_2); // modifies param_2
    // param_2 = param_2 combined with foundBlock->flags byte
    // Then sets/clears bit at bitmapMgr->bitmap[bitIndex] based on flags
    uint8 flag = foundBlock->flags;
    // The bit manipulation is complex; simplified: set or clear the bit corresponding to this block
    if (flag == 0) {
        BitfieldClear(bitmapMgr->bitmap, bitIndex); // clear -> block is now invalid?
    } else {
        BitfieldSet(bitmapMgr->bitmap, bitIndex);   // set -> block is valid
    }
    bitmapMgr->bitIndex++;

    // If flag is set, early return (block was being touched? Actually the code returns if cVar11 !=0 after bit set)
    if (flag != 0) {
        return;
    }

    // Block is now invalid (flag==0), so we need to possibly send it to a global allocator?
    // This part appears to allocate a global tracking node (DAT_01223ba0) and link it into a list
    // We'll simplify as a call to insertGlobalTrackerBlock(key, foundBlock)
    insertGlobalTrackerBlock(key, foundBlock);
}

// Helper functions (not shown fully):
void refCountInc(uint key);
void refCountDec(uint key);
void BitfieldSet(uint8* bitmap, uint bitIndex);
void BitfieldClear(uint8* bitmap, uint bitIndex);
void insertGlobalTrackerBlock(uint key, BlockHeader* block); // uses DAT_01223ba0 global free list