// FUNC_NAME: PoolManager::popFromFreeList

// Function: 0x0042c5d0
// Role: Pops an element from a free list in a memory pool. If the list is empty,
//       attempts to allocate a new block using a fallback allocator.
// The pool descriptor is stored at offset 0x3A00 from 'this'.
// The free list is a singly linked list of nodes.
// Each node structure:
//   +0x00: next pointer (FreeListNode*)
//   +0x04: ? (unused here)
//   +0x08: field (used to set to node+0x14 on allocation)
//   +0x14: start of node data? (size 0x14 per node? offset used for fallback head)

struct FreeListNode {
    FreeListNode* next;       // +0x00
    int unused;               // +0x04
    FreeListNode* initPtr;    // +0x08 – set to (this + 0x14) on pop
};

struct PoolDescriptor {
    FreeListNode* freeListHead;  // +0x08
    int allocParam1;             // +0x0C – argument for fallback allocator
    int allocParam2;             // +0x10 – argument for fallback allocator
    int freeCount;               // +0x14
    int minFreeCount;            // +0x18
    FallbackAllocator* fallback; // +0x1C – pointer to allocator object with vtable
};

struct FallbackAllocator {
    void** vtable;               // +0x00
    // vtable[1] = allocate function (index 4 bytes)
};

extern int g_lastError; // Global error flag (set to 0x14 on allocation failure)

void __thiscall PoolManager::popFromFreeList(void* this) {
    PoolDescriptor* pool = *(PoolDescriptor**)((char*)this + 0x3A00);

    if (pool->freeCount != 0) {
        // Pop the head node from the free list
        FreeListNode* node = pool->freeListHead;
        pool->freeCount--;
        pool->freeListHead = node->next; // next is at offset 0

        // Update the minimum free count seen
        if (pool->freeCount < pool->minFreeCount) {
            pool->minFreeCount = pool->freeCount;
        }

        // Initialize node field at offset 8 to node+0x14 (likely for internal tracking)
        node->initPtr = (FreeListNode*)((char*)node + 0x14);
    } else {
        // Free list empty – attempt to allocate a new block
        if (pool->fallback != nullptr) {
            // Call the fallback allocator's allocate method (vtable entry at index 1)
            // Parameters come from pool->allocParam1 and pool->allocParam2
            void* newBlock = pool->fallback->vtable[1](pool->allocParam1, pool->allocParam2);
            // Set the free list head to the first free node inside the new block (offset 0x14 from block start)
            pool->freeListHead = (FreeListNode*)((char*)newBlock + 0x14);
        } else {
            // No fallback allocator – set global error code
            g_lastError = 0x14;
        }
        // Note: after allocating, the function does NOT pop a node.
        // The caller is expected to retry popFromFreeList or use the head directly.
    }
}