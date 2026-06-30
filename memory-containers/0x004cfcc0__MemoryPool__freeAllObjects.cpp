// FUNC_NAME: MemoryPool::freeAllObjects

void MemoryPool::freeAllObjects()
{
    // +0x00: buckets pointer (array of PoolNode*)
    // +0x04: bucketCount (int)
    // +0x08: freeList (PoolNode*)
    // +0x0C: allocatedCount (int)
    // +0x10: extraList (PoolNode*)

    uint i = 0;
    if (this->bucketCount != 0) {
        do {
            // Get head of bucket i
            PoolNode* node = this->buckets[i];
            if (node != nullptr) {
                do {
                    // Save next before we modify node
                    PoolNode* nextNode = reinterpret_cast<PoolNode*>(reinterpret_cast<int*>(node)[2]); // next at +0x08
                    // Move node to free list
                    reinterpret_cast<int*>(node)[2] = reinterpret_cast<int>(this->freeList);
                    this->allocatedCount--; // +0x0C
                    this->freeList = node;      // +0x08
                    node = nextNode;
                } while (nextNode != nullptr);
                // Clear bucket head
                this->buckets[i] = nullptr;
            }
            i++;
        } while (i < static_cast<uint>(this->bucketCount));
    }

    // Process extra list (next pointer at offset 0x00)
    PoolNode* extraNode = this->extraList; // +0x10
    while (extraNode != nullptr) {
        PoolNode* nextExtra = reinterpret_cast<PoolNode*>(*reinterpret_cast<int*>(extraNode)); // next at +0x00
        // Call destructor/deallocator for this node
        FUN_009c8eb0(extraNode);
        extraNode = nextExtra;
    }

    // Reset tracking pointers
    this->extraList = nullptr; // +0x10
    this->freeList = nullptr;  // +0x08
}