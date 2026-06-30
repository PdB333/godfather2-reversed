// FUNC_NAME: HashTable::resizeDenseArrayWithRehash
// Address: 0x00637a50
// Role: Resizes the dense array (8-byte entries) and rehashes buckets into a new bucket table.
// The class has:
//   +0x07: byte log2BucketCount (power-of-two bucket count = 1 << log2BucketCount)
//   +0x0c: int* denseArray (8-byte entries, each maybe {int key, int value})
//   +0x10: BucketEntry* bucketTable (20-byte entries: {int hash, int key, int value, int next, int?} starting at offset 8? Actually offset 0x10 points to entire array, but bucket struct has 20 bytes, and the code accesses bucketTable + index * 20 + 8 to get the first int of the struct)
//   +0x1c: int denseCount (current number of valid dense entries)
// The function takes a MemoryManager (param_1) and a flag (param_3) for initialization.

void HashTable::resizeDenseArrayWithRehash(int newDenseSize, int initFlags)
{
    int oldDenseCount = this->denseCount;          // +0x1c
    byte bucketShift = this->log2BucketCount;       // +0x07
    BucketEntry* oldBucketBase = this->bucketTable; // +0x10

    BucketEntry stackBucketStorage; // 20-byte temporary bucket for empty table

    // If bucket count is zero, use stack storage as a single bucket
    if (bucketShift == 0) {
        // Copy 16 bytes from the old bucket table start? Actually *oldBucketBase is the first bucket (20 bytes)
        // But we copy only 16 bytes (four ints) into stack vars: local_1c, local_14, uStack_10, local_c
        // Then set oldBucketBase to point to stack copy.
        *(uint64*)(&stackBucketStorage) = *(uint64*)oldBucketBase;                // first 8 bytes
        *(uint32*)(((char*)&stackBucketStorage) + 8) = *(uint32*)((char*)oldBucketBase + 8);
        *(uint32*)(((char*)&stackBucketStorage) + 12) = *(uint32*)((char*)oldBucketBase + 12);
        oldBucketBase = &stackBucketStorage;

        // Reset some counters in the memory manager (param_1) - likely used size tracking
        *(int*)(*(int*)(param_1 + 0x10) + 0x40) = 0;
        *(int*)(*(int*)(param_1 + 0x10) + 0x48) = 0;
    }

    // Ensure dense array capacity
    if (oldDenseCount < newDenseSize) {
        growDenseArray(newDenseSize);              // FUN_00637910
    }

    // Initialize new dense entries (e.g., set to null)
    initDenseEntries(param_1, initFlags);          // FUN_00637960

    // Shrink dense array if needed: move remaining entries to new location
    if (newDenseSize < oldDenseCount) {
        int entriesToMove = oldDenseCount - newDenseSize;
        this->denseCount = newDenseSize;
        int srcOffset = newDenseSize * 8; // each dense entry is 8 bytes
        do {
            int* srcEntry = (int*)(*(int*)(this->denseArray) + srcOffset);
            if (*srcEntry != 0) {
                // Allocate/acquire a new 8-byte slot (maybe from a pool)
                int* destEntry = (int*)getFreeSlot();             // FUN_00637f10
                if (destEntry == &DEFAULT_SLOT_SENTINEL) {       // DAT_00e2a93c
                    destEntry = (int*)getSlotFromManager(param_1); // FUN_00637d60
                }
                destEntry[0] = srcEntry[0];
                destEntry[1] = srcEntry[1];
            }
            srcOffset += 8;
            entriesToMove--;
        } while (entriesToMove != 0);

        // Reallocate the dense array block to new size
        this->denseArray = (int*)reallocateBlock(oldDenseCount * 8, newDenseSize * 8); // FUN_006279a0
    }

    // Rehash bucket entries: move each bucket's data to a new allocation
    int bucketCount = 1 << (bucketShift & 0x1f);
    int index = bucketCount - 1;
    if (index >= 0) {
        // Iterate buckets in reverse order
        BucketEntry* bucketPtr = (BucketEntry*)((int)oldBucketBase + index * 20 + 8); // offset 8: first field of bucket struct
        do {
            int* bucketData = (int*)bucketPtr; // points to first int of bucket (offset 0 within bucket struct)
            if (*bucketData != 0) {
                int* newSlot = (int*)getBucketSlotFromManager(param_1); // FUN_00638020
                newSlot[0] = bucketData[0];
                newSlot[1] = bucketData[1];
            }
            index--;
            bucketPtr = (BucketEntry*)((char*)bucketPtr - 20); // move to previous bucket (each 20 bytes)
        } while (index >= 0);
    }

    // Free old bucket table memory if it was not the stack copy
    if ((bucketShift != 0) && (oldBucketBase != nullptr)) {
        (*deallocateBucketTable)(oldBucketBase); // DAT_012059e0
    }

    // Update bucket memory usage tracker in the manager
    if (param_1 != nullptr) {
        int* usedSize = (int*)(*(int*)(param_1 + 0x10) + 0x24);
        *usedSize = *usedSize - (bucketCount * 20);
    }

    return;
}