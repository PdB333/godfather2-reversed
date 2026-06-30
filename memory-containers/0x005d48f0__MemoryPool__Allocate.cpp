// FUNC_NAME: MemoryPool::allocate
// Address: 0x005d48f0
// Allocates a fixed-size block from the pool. Iterates over buckets of free blocks.
// If no block is available and the allocator is allowed to grow, a new bucket is allocated.
// Returns pointer to allocated block, or nullptr on failure.

#include <cstdint>

// Forward declaration of the allocator class and internal node/bucket structures.
class MemoryPool;

// A single block in the free list. First word is pointer to next free block.
struct FreeBlock {
    FreeBlock* next; // +0x00
};

// A bucket that holds a free list of blocks of a specific size.
// The bucket itself is part of a singly-linked list of buckets.
struct Bucket {
    Bucket* next;                      // +0x04 (next bucket in the allocator list)
    FreeBlock* freeListHead;           // +0x08 (pointer to the head of the free list)
    int32_t allocatedCount;            // +0x10 (number of blocks allocated from this bucket)
};

// The main allocator class.
// Note: offsets are as observed in the decompiled function.
class MemoryPool {
public:
    // +0x04: flag indicating whether the allocator is allowed to grow.
    bool canGrow;                     // offset 0x04
    // +0x14: maximum number of buckets allowed. 0 means no limit.
    int32_t maxBuckets;               // offset 0x14
    // +0x1c: head of the bucket list (singly linked via Bucket::next).
    Bucket* bucketList;               // offset 0x1c

    // Allocates a new bucket (by calling the system allocator) and returns its pointer.
    Bucket* allocateBucket(); // FUN_005d4800

    // Allocate one block from the pool.
    // Returns null if out of memory.
    void* allocate() {
        int32_t newBucket;
        Bucket* bucket;

        while (true) {
            // Try to pop a free block from any existing bucket.
            for (bucket = bucketList; bucket != nullptr; bucket = bucket->next) {
                FreeBlock* block = bucket->freeListHead;
                if (block != nullptr) {
                    // Remove block from free list.
                    bucket->freeListHead = block->next;
                    // Mark block as allocated by setting its next pointer to the address of the freeListHead variable?
                    // This might be used for debugging or double-free detection.
                    block->next = reinterpret_cast<FreeBlock*>(&bucket->freeListHead);
                    // Increment allocation counter.
                    bucket->allocatedCount++;
                    return block;
                }
            }

            // No block available. Check if we should try to allocate a new bucket.
            // Condition: if (maxBuckets != 0 && canGrow == false) stop; or if allocateBucket fails, stop.
            if ((maxBuckets != 0 && !canGrow) || (newBucket = reinterpret_cast<int32_t>(allocateBucket()), newBucket == 0))
                break;

            // Insert new bucket at the front of the bucket list.
            if (bucketList != nullptr) {
                // The first word of the old head? Actually, this writes the bucket pointer
                // into the freeListHead field? The code: **(int**)(in_EAX+0x1c) = iVar2;
                // That sets bucketList->freeListHead = newBucket? That seems odd.
                // Possibly it is writing the new bucket pointer into the free list head location?
                // But the new bucket hasn't been inserted yet. Let's re-evaluate.
            }
        }

        // No block could be allocated.
        return nullptr;
    }
};

// Note: The exact behavior of inserting the new bucket is complex.
// The decompiled code shows:
//   if (*(int **)(in_EAX + 0x1c) != (int *)0x0) {
//       **(int **)(in_EAX + 0x1c) = iVar2;
//   }
//   *(undefined4 *)(iVar2 + 4) = *(undefined4 *)(in_EAX + 0x1c);
//   *(int *)(in_EAX + 0x1c) = iVar2;
// This writes into the memory pointed by bucketList (the freeListHead of the first bucket?)
// It sets that to the new bucket pointer. Then sets newBucket->next = old bucketList, then bucketList = newBucket.
// This seems to corrupt the first bucket's freeListHead? Possibly the first bucket is a sentinel?
// To be faithful to the decompilation, we'll replicate it exactly.
// However, for clarity, the intended operation is likely:
//   if (bucketList) bucketList->freeListHead = (FreeBlock*)newBucket; // miswrite?
//   newBucket->next = bucketList;
//   bucketList = (Bucket*)newBucket;
// This might be a bug in the original code or misinterpretation.
// We'll keep the original logic.

// Actual reconstructed function with original logic preserved:

void* MemoryPool::allocate() {
    Bucket* bucket;
    int32_t temp;

    while (true) {
        // Scan all buckets for a free block.
        for (bucket = bucketList; bucket != nullptr; bucket = bucket->next) {
            FreeBlock* block = bucket->freeListHead;
            if (block != nullptr) {
                // Unlink from the free list.
                bucket->freeListHead = block->next;
                // Mark block as allocated (maybe store pointer to freeListHead location).
                block->next = reinterpret_cast<FreeBlock*>(&bucket->freeListHead);
                bucket->allocatedCount++;
                return block;
            }
        }

        // No free blocks: check if we should allocate a new bucket.
        // Stop if (maxBuckets != 0 and canGrow is false) OR if allocateBucket fails.
        if ((maxBuckets != 0 && !canGrow) ||
            (temp = reinterpret_cast<int32_t>(allocateBucket()), temp == 0)) {
            break;
        }

        // Insert the new bucket at the head of the bucket list.
        // The following code matches the decompiled output, though it appears to overwrite
        // the freeListHead of the first bucket (if it exists) to point to the new bucket.
        if (bucketList != nullptr) {
            // Write the new bucket address into bucketList->freeListHead
            bucketList->freeListHead = reinterpret_cast<FreeBlock*>(static_cast<intptr_t>(temp));
        }
        // Set new bucket's next to the old head.
        reinterpret_cast<Bucket*>(temp)->next = bucketList;
        // Update the head.
        bucketList = reinterpret_cast<Bucket*>(temp);
    }

    return nullptr;
}