// FUNC_NAME: ObjectPool::allocateObject
// Address: 0x005d48f0
// Role: Object pool allocation - iterates free list and return freed object

undefined4* __thiscall ObjectPool::allocateObject(void* thisPtr) {
    undefined4* freeNode;
    int currentBucket;
    int allocatedNode;
    int bucketList;
    
    while (true) {
        bucketList = *(int*)(thisPtr + 0x1c);  // +0x1c: head of bucket list
        
        for (currentBucket = bucketList; currentBucket != 0; currentBucket = *(int*)(currentBucket + 4)) {
            freeNode = (undefined4*)**(int**)(currentBucket + 8);  // +8: pointer to free list head in bucket
            
            if (freeNode != (undefined4*)0x0) {
                // Remove first node from free list
                **(undefined4**)(currentBucket + 8) = *freeNode;  // update free list head to next
                *freeNode = *(undefined4*)(currentBucket + 8);    // node->next = old list head? (double linking)
                
                *(int*)(currentBucket + 0x10) = *(int*)(currentBucket + 0x10) + 1;  // +0x10: allocate count
                return freeNode;
            }
        }
        
        // No free nodes found in existing buckets
        if (((*(int*)(thisPtr + 0x14) != 0) && (*(char*)(thisPtr + 4) == '\0')) ||
            (allocatedNode = ObjectPool::allocateNewBucket(thisPtr), allocatedNode == 0)) {
            break;  // Can't allocate new bucket, return null
        }
        
        // Insert new bucket into bucket list
        if (*(int**)(thisPtr + 0x1c) != (int*)0x0) {
            **(int**)(thisPtr + 0x1c) = allocatedNode;  // Link to old head
        }
        *(int*)(allocatedNode + 4) = *(int*)(thisPtr + 0x1c);  // Bucket->next = old head
        *(int*)(thisPtr + 0x1c) = allocatedNode;  // New head of bucket list
    }
    
    return (undefined4*)0x0;  // Allocation failed
}