// FUNC_NAME: MemoryPool::freeAll
// Function at 0x00448590 - Frees all objects in bucket lists and allocated list, returning them to free list.
// Class layout:
// +0x00: buckets - array of pointers to linked lists (size = bucketCount)
// +0x04: bucketCount - number of buckets
// +0x08: freeListHead - head of free list (nodes linked via offset 0x18)
// +0x0C: freeCount - number of nodes in free list
// +0x10: allocatedListHead - head of list of all allocated nodes (linked via offset 0x00)

void MemoryPool::freeAll()
{
    uint bucketIndex;
    int node;
    int nextNode;
    int *bucketArray;
    int *freeListHead;
    int *nextAllocated;
    int *allocatedNode;

    bucketArray = (int *)this->buckets;
    bucketIndex = 0;
    if (this->bucketCount != 0) {
        do {
            node = *(int *)((int)bucketArray + bucketIndex * 4); // get head of bucket list
            if (node != 0) {
                do {
                    nextNode = *(int *)(node + 0x18);          // save next node in bucket list
                    *(int *)(node + 0x18) = this->freeListHead; // attach to free list
                    this->freeCount = this->freeCount - 1;     // decrease free count (sign? maybe freeListCount)
                    this->freeListHead = node;                  // update free list head
                    node = nextNode;
                } while (nextNode != 0);
                *(int *)((int)bucketArray + bucketIndex * 4) = 0; // clear bucket list head
            }
            bucketIndex = bucketIndex + 1;
        } while (bucketIndex < (uint)this->bucketCount);
    }
    // Free all nodes in the allocated list
    allocatedNode = (int *)this->allocatedListHead;
    while (allocatedNode != (int *)0x0) {
        nextAllocated = (int *)*allocatedNode;        // get next allocated node
        deallocateNode(allocatedNode);                 // free the memory
        allocatedNode = nextAllocated;
    }
    this->allocatedListHead = 0;
    this->freeListHead = 0;
    return;
}