// FUNC_NAME: 0x007e8b40 Pool::cleanup
// Function address: 0x007e8b40
// Role: Cleans up a pool of nodes. Moves all nodes from the slot array to the free list.
// If deallocate is true, also frees all nodes in the master list and resets the pool.

struct PoolNode {
    PoolNode* next; // +0x00 (next pointer in linked list)
    // other data follows, but only next is used here
};

struct Pool {
    PoolNode** slotArray; // +0x00: array of pointers to linked lists (one per slot)
    int slotCount;        // +0x04: number of slots
    PoolNode* freeList;   // +0x08: head of free list (available nodes)
    int usedCount;        // +0x0C: number of nodes currently in use
    PoolNode* allNodes;   // +0x10: head of master list of all nodes (for deallocation)
};

// External function to deallocate a single node (likely free memory)
extern void deallocateNode(PoolNode* node); // FUN_009c8eb0

void __thiscall Pool::cleanup(Pool* this, bool deallocate) {
    unsigned int slotIndex = 0;

    // Move all nodes from the slot arrays to the free list
    if (this->slotCount != 0) {
        do {
            PoolNode* node = this->slotArray[slotIndex];
            if (node != nullptr) {
                do {
                    PoolNode* nextNode = node->next; // save next
                    node->next = this->freeList;     // link to free list
                    this->usedCount--;                // one less node in use
                    this->freeList = node;            // update free list head
                    node = nextNode;
                } while (nextNode != nullptr);
                this->slotArray[slotIndex] = nullptr; // clear slot
            }
            slotIndex++;
        } while (slotIndex < (unsigned int)this->slotCount);
    }

    // If deallocate is true, free all nodes in the master list
    if (deallocate) {
        PoolNode* current = this->allNodes;
        while (current != nullptr) {
            PoolNode* next = current->next; // save next before freeing
            deallocateNode(current);
            current = next;
        }
        this->freeList = nullptr;
        this->allNodes = nullptr;
    }
}