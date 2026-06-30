// FUNC_NAME: PoolManager::reset
void __thiscall PoolManager::reset(void)
{
    uint bucketIndex;
    int *bucketHead;
    int *node;
    int *nextNode;
    int *allocBlock;
    int *nextBlock;

    // Iterate over all buckets
    for (bucketIndex = 0; bucketIndex < *(uint *)(this + 4); bucketIndex++) {
        bucketHead = *(int **)(*(int *)(this + 8) + bucketIndex * 4);
        if (bucketHead != 0) {
            do {
                // Save next node (offset +0x8)
                nextNode = *(int **)(bucketHead + 2); // +0x8
                // Move node to free list (head at +0xc)
                *(int **)(bucketHead + 2) = *(int **)(this + 0xc); // node->next = freeListHead
                *(int *)(this + 0x10) = *(int *)(this + 0x10) - 1; // decrement usedCount
                *(int **)(this + 0xc) = bucketHead; // freeListHead = node
                bucketHead = nextNode;
            } while (nextNode != 0);
            // Clear bucket head
            *(int **)(*(int *)(this + 8) + bucketIndex * 4) = 0;
        }
    }

    // Free all allocated blocks (linked list at +0x14, next at offset 0)
    allocBlock = *(int **)(this + 0x14);
    while (allocBlock != 0) {
        nextBlock = *(int **)allocBlock; // next at offset 0
        FUN_009c8eb0(allocBlock); // deallocate block
        allocBlock = nextBlock;
    }

    // Reset lists
    *(int **)(this + 0x14) = 0;
    *(int **)(this + 0xc) = 0;
}