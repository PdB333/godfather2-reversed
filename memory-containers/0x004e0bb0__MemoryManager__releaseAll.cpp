// FUNC_NAME: MemoryManager::releaseAll

void MemoryManager::releaseAll() {
    int slotCount = this->slotCount;                // +0x04
    int* slotArray = this->slotArray;              // +0x00, array of pointers to per-slot lists
    int freeCount = this->freeCount;                // +0x0C
    int freeHead = this->freeHead;                  // +0x08
    int allocHead = this->allocHead;                // +0x10

    unsigned int slotIdx = 0;
    if (slotCount != 0) {
        do {
            int nodePtr = slotArray[slotIdx];       // head of this slot's linked list
            if (nodePtr != 0) {
                // Move all nodes from this slot's list to the global free list
                do {
                    int nextNode = *(int*)(nodePtr + 4); // next pointer is at offset +4 in these nodes
                    *(int*)(nodePtr + 4) = freeHead;     // link node to current free head
                    freeCount--;
                    freeHead = nodePtr;
                    nodePtr = nextNode;
                } while (nextNode != 0);
                slotArray[slotIdx] = 0;             // clear the slot list head
            }
            slotIdx++;
        } while (slotIdx < (unsigned int)slotCount);
    }

    // Iterate over the allocation list and free each node
    int* allocNode = (int*)this->allocHead;
    while (allocNode != nullptr) {
        int* nextAlloc = (int*)*allocNode;          // next pointer is at offset +0 in these nodes
        FUN_009c8eb0(allocNode);                    // presumably deallocate the node
        allocNode = nextAlloc;
    }

    this->allocHead = 0;
    this->freeHead = 0;

    return;
}