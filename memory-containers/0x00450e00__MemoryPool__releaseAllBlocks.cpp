// FUNC_NAME: MemoryPool::releaseAllBlocks
void __thiscall MemoryPool::releaseAllBlocks(void)
{
    uint bucketIndex;
    BucketNode* node;
    BucketNode* nextNode;
    OtherNode* otherNode;
    OtherNode* nextOther;

    // Iterate over all bucket lists
    if (this->numBuckets != 0) {
        for (bucketIndex = 0; bucketIndex < this->numBuckets; bucketIndex++) {
            node = this->bucketArray[bucketIndex];  // +0x08: array of bucket heads
            if (node != nullptr) {
                do {
                    // Move each node to the free list (next pointer at +0x14)
                    nextNode = *(BucketNode**)((char*)node + 0x14);
                    *(void**)((char*)node + 0x14) = this->freeListHead;  // +0x0C: free list head
                    this->freeListCount--;  // +0x10: free list count (decremented when moving to free list)
                    this->freeListHead = node;
                    node = nextNode;
                } while (node != nullptr);
                this->bucketArray[bucketIndex] = nullptr;
            }
        }
    }

    // Free the separate linked list (head at +0x14, next at +0x00)
    otherNode = this->otherListHead;  // +0x14
    while (otherNode != nullptr) {
        nextOther = otherNode->next;  // +0x00
        FUN_009c8eb0(otherNode);      // Free or destructor call
        otherNode = nextOther;
    }

    this->otherListHead = nullptr;
    this->freeListHead = nullptr;
}