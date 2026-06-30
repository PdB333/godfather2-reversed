// FUNC_NAME: MemoryPool::clearBucket
// Function at 0x0066dfe0: Removes all nodes from a given bucket and returns them to the free list.
// Assumes bucket is a pointer into the bucket array at pool+0x122a8.
// Bucket size: 8 ints (32 bytes). Array has 0x90 (144) entries.
// Pool node structure: { next (0), unknown1 (1), unknown2 (2), size (3) } (4 ints).

struct PoolNode {
    PoolNode* next;       // +0x00
    int unknown1;         // +0x04
    int unknown2;         // +0x08
    int size;             // +0x0C
};

struct Bucket {
    int unknown0;         // +0x00
    int unknown1;         // +0x04
    int unknown2;         // +0x08
    int totalSize;        // +0x0C
    int count;            // +0x10
    PoolNode* head;       // +0x14
    int unknown6;         // +0x18
    int unknown7;         // +0x1C
};

class MemoryPool {
public:
    int totalBuckets;          // +0x00
    int totalPoolSize;         // +0x04
    short activeNodeCount;     // +0x08
    // ... other fields ...
    PoolNode* freeListHead;    // +0x14 (5*4)
    // ... up to +0x122a8 ...
    Bucket buckets[144];       // +0x122a8, each 32 bytes => total 0x1200 bytes
};

void __fastcall MemoryPool::clearBucket(void* ecx, void* edx) {
    // ecx = this (pool)
    // edx = bucket pointer (edx)
    MemoryPool* pool = (MemoryPool*)ecx;
    Bucket* bucket = (Bucket*)edx;

    // Find the bucket in the array to confirm it's valid (optional, but done in original)
    Bucket* search = &pool->buckets[0];
    for (uint32_t i = 0; i < 144; i++) {
        if (search == bucket) {
            // Found matching bucket - remove all nodes from its list
            PoolNode* node = bucket->head; // start at head of list
            while (node != nullptr) {
                PoolNode* nextNode = node->next; // save next before unlinking

                // Update global counters
                pool->totalPoolSize -= node->size;
                bucket->totalSize -= node->size;
                bucket->count -= 1;

                // Return node to free list
                node->next = pool->freeListHead;
                node->unknown1 = 0;   // clear
                node->size = 0;       // could be redundant
                pool->activeNodeCount--;
                pool->freeListHead = node;

                node = nextNode; // continue iteration
            }

            // Clear bucket fields (zero out except possibly unknown7)
            bucket->unknown0 = 0;
            bucket->unknown2 = 0;
            bucket->totalSize = 0;
            bucket->count = 0;
            bucket->head = nullptr;
            bucket->unknown6 = 0;
            bucket->unknown1 = 0; // order matters? all zeroed anyway
            bucket->unknown7 = 0; // not zeroed in original? but we do for safety

            // Decrement total bucket count
            pool->totalBuckets--;

            return;
        }
        search++;
    }
    // If bucket not found in array, nothing happens (should not occur)
}