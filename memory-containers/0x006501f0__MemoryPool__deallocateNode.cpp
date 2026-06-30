// FUNC_NAME: MemoryPool::deallocateNode

struct PoolNode {
    int32_t key;              // +0x00
    int32_t freeIndex;        // +0x04
    uint32_t flags;           // +0x08
    PoolNode* prev;           // +0x0C
    PoolNode* next;           // +0x10
    PoolNode* hashNext;       // +0x18
    // size 0x20? (0x8+0x18)
};

// Pool object assumed to be in EDI; node to free in ESI (this)
// Offset 0x218 in pool object: Pointer to hash table (PoolNode*[1024])
void MemoryPool::deallocateNode(PoolNode* node, MemoryPool* pool) {
    node->flags |= 0x10; // mark as freed

    if (node->freeIndex == 0) {
        node->freeIndex = -1;
        // add node to free list (FUN_0064d4a0)
        addNodeToFreeList(node);
    }

    int32_t key = node->key;
    if (key != 0) {
        // Remove from doubly-linked list (allocated list)
        // Head of list is at node->key (a PoolNode*)
        if (node->next == nullptr) {
            // node is tail; update head's back pointer (+0x1C)
            *(PoolNode**)((uint8_t*)key + 0x1C) = node->prev;
        } else {
            node->next->prev = node->prev;
        }
        if (node->prev != nullptr) {
            node->prev->next = node->next;
        }

        // Remove from hash bucket
        uint32_t bucketIdx = (key / 0x34) & 0x3FF;
        PoolNode** bucket = &pool->hashTable[bucketIdx];
        PoolNode* curr = *bucket;
        while (curr != nullptr) {
            if (curr == node) {
                *bucket = node->hashNext;
                break;
            }
            bucket = &curr->hashNext;
            curr = curr->hashNext;
        }

        // Clear node links
        node->prev = nullptr;
        node->next = nullptr;
        node->key = 0;
    }
}