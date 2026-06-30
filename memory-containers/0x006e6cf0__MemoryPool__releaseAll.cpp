// FUNC_NAME: MemoryPool::releaseAll
void MemoryPool::releaseAll()
{
    uint32 slotIndex = 0;

    // Free all nodes from each bucket back to the free list
    if (bucketCount != 0) {
        do {
            int32* node = buckets[slotIndex];
            if (node != nullptr) {
                do {
                    int32* nextNode = reinterpret_cast<int32*>(node[1]); // +0x04 next pointer
                    node[1] = reinterpret_cast<int32>(freeListHead);     // attach to free list
                    freeCount--;
                    freeListHead = node;
                    node = nextNode;
                } while (node != nullptr);
                buckets[slotIndex] = nullptr; // clear bucket head
            }
            slotIndex++;
        } while (slotIndex < bucketCount);
    }

    // Free all spare blocks (chunks) separately
    int32* spareBlock = spareListHead;
    while (spareBlock != nullptr) {
        int32* nextSpare = reinterpret_cast<int32*>(*spareBlock);
        deallocateBlock(spareBlock); // FUN_009c8eb0
        spareBlock = nextSpare;
    }
    spareListHead = nullptr;
    freeListHead = nullptr;
}