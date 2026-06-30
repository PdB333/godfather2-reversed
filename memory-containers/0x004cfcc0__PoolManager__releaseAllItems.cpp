// FUNC_NAME: PoolManager::releaseAllItems

void __thiscall PoolManager::releaseAllItems(void) {
    // This function releases all items from active pools and pending free lists.
    // The structure (this) contains:
    // +0x00 itemArrays: pointer to array of pointers to linked list heads
    // +0x04 arrayCount: number of arrays
    // +0x08 freeListHead: head of reusable items (free list)
    // +0x0C usedCount: number of items currently allocated from arrays
    // +0x10 pendingFreeHead: head of items awaiting destruction

    uint i = 0;
    if (this->arrayCount != 0) {
        do {
            void* listHead = *(this->itemArrays + i * 4); // get array entry (pointer to first node)
            if (listHead != 0) {
                do {
                    void* nextNode = *(void**)((char*)listHead + 8); // next pointer at offset +8
                    *(void**)((char*)listHead + 8) = this->freeListHead; // link to free list
                    this->usedCount -= 1; // decrement active count
                    this->freeListHead = listHead; // add to free list
                    listHead = nextNode;
                } while (nextNode != 0);
                *(this->itemArrays + i * 4) = 0; // clear array entry
            }
            i += 1;
        } while (i < (uint)this->arrayCount);
    }

    // Destroy all nodes in the pending free list
    void* pendingNode = this->pendingFreeHead;
    while (pendingNode != 0) {
        void* nextPending = *(void**)pendingNode; // first word is next pointer
        this->deallocateNode(pendingNode); // call custom deallocation (FUN_009c8eb0)
        pendingNode = nextPending;
    }

    this->pendingFreeHead = 0;
    this->freeListHead = 0;
}