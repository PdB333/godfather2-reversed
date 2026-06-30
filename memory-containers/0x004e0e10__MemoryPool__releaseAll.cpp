// FUNC_NAME: MemoryPool::releaseAll

class MemoryPool {
public:
    void** buckets;        // +0x00: array of bucket heads (linked list per bucket)
    int bucketCount;       // +0x04: number of buckets
    void* freeListHead;    // +0x08: head of free list (reusable nodes)
    int freeCount;         // +0x0C: count of free nodes (decremented when moved)
    void* pendingListHead; // +0x10: head of pending destruction list
};

// External: node destructor / deallocator
extern void destroyNode(void* node);

// __thiscall
void MemoryPool::releaseAll() {
    uint bucketIndex = 0;

    // Step 1: Move all nodes from each bucket's linked list into the free list
    if (this->bucketCount != 0) {
        do {
            void* node = this->buckets[bucketIndex];
            if (node != nullptr) {
                do {
                    // The node's next pointer is at offset +0x08
                    void* nextNode = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(node) + 0x8);
                    // Detach and add to free list
                    *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(node) + 0x8) = this->freeListHead;
                    this->freeCount--;
                    this->freeListHead = node;
                    node = nextNode;
                } while (nextNode != nullptr);
                // Clear the bucket head
                this->buckets[bucketIndex] = nullptr;
            }
            bucketIndex++;
        } while (bucketIndex < static_cast<uint>(this->bucketCount));
    }

    // Step 2: Destroy all nodes in the pending destruction list
    void* pendingNode = this->pendingListHead;
    while (pendingNode != nullptr) {
        void* nextPending = *reinterpret_cast<void**>(pendingNode); // next pointer at +0x00 in pending list?
        destroyNode(pendingNode);
        pendingNode = nextPending;
    }

    // Reset free list and pending list
    this->pendingListHead = nullptr;
    this->freeListHead = nullptr;
}