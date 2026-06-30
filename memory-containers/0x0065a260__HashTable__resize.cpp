// FUNC_NAME: HashTable::resize
void __cdecl HashTable::resize(unsigned int newBucketCount) {
    int* bucketArray = g_hashTableBuckets;  // DAT_01205a38
    unsigned int oldBucketCount = g_hashTableBucketCount; // DAT_01205a3c
    int* nodeArray = g_hashTableNodeArray; // DAT_01205a34 (array of pointers to HashNode)
    int freeListHead = 0;

    // Collect all nodes from old buckets into a free list
    if (oldBucketCount != 0) {
        for (unsigned int i = 0; i < oldBucketCount; ++i) {
            int nodeIndex = bucketArray[i]; // bucket stored first field of node (which is the node's index? see comment below)
            while (nodeIndex != 0) {
                int* nodePtr = (int*)(nodeArray + nodeIndex * 4); // nodeArray is array of pointers? Actually nodeArray[i] gives address of node, but here nodeArray is cast to int*, so nodeArray + nodeIndex*4 gives an int*, then *(int*)(that) = nodePtr? Wait, line: iVar1 = *(int *)(iVar4 + iVar3 * 4); means nodeArray[iVar3] (an int) is the actual pointer to node. So nodePtr is the pointer value.
                // More accurately:
                int nodePtr = *(int*)(nodeArray + nodeIndex * 4); // get pointer to HashNode
                int nextIndex = *(int*)(nodePtr + 4); // node->next (offset 4) is an index
                *(int*)(nodePtr + 4) = freeListHead; // set node->next to current free list head
                freeListHead = nodeIndex; // move node to free list head
                nodeIndex = nextIndex; // continue with previous next
            }
        }
    }

    // Reallocate bucket array to new size
    int* newBuckets = (int*)_realloc(g_hashTableBuckets, newBucketCount * 4);
    g_hashTableBuckets = newBuckets;
    g_hashTableBucketCount = newBucketCount;

    // Zero new bucket array
    if (newBucketCount != 0) {
        for (unsigned int i = 0; i < newBucketCount; ++i) {
            newBuckets[i] = 0;
        }
    }

    // Reinsert all nodes from free list using new hash
    while (freeListHead != 0) {
        int* nodePtr = *(int**)(nodeArray + freeListHead * 4); // get pointer to HashNode
        int nextFree = nodePtr[1]; // save next free list node index
        unsigned int key = (unsigned int)nodePtr[2]; // key at offset 8
        unsigned int bucketIndex = key % newBucketCount;
        nodePtr[1] = newBuckets[bucketIndex]; // node->next = old bucket value
        newBuckets[bucketIndex] = nodePtr[0]; // bucket = node->data (first field)
        freeListHead = nextFree;
    }
}