// FUNC_NAME: PacketPool::reset
void __thiscall PacketPool::reset(PacketPool* this) {
    // Clear all hash buckets (0x400 slots, each stores a linked list head)
    for (int i = 0; i < 0x400; ++i) {
        Node* bucketHead = *(Node**)((uint8_t*)this + 0x30 + i * 4);
        if (bucketHead != nullptr) {
            // Walk the chain and clear internal links (bucket chain uses offset +0x30 for next)
            Node* node = bucketHead;
            while (node != nullptr) {
                Node* next = *(Node**)((uint8_t*)node + 0x30);
                *(int*)((uint8_t*)node + 0x30) = 0;  // Clear next
                *(int*)((uint8_t*)node + 0x34) = 0;  // Clear auxiliary field
                node = next;
            }
            // Clear the bucket head itself
            *(Node**)((uint8_t*)this + 0x30 + i * 4) = nullptr;
        }
    }

    // Move all nodes from the pending release list (offset +0x14) to the free list (offset +0x10)
    Node* pendingHead = *(Node**)((uint8_t*)this + 0x14);
    while (pendingHead != nullptr) {
        Node* nextPending = *(Node**)pendingHead;       // Save next in pending list
        // Insert pendingHead at the front of the free list (doubly linked with prev at +0x04, next at +0x00)
        *(int*)((uint8_t*)pendingHead + 4) = 0;        // Clear prev (will be head's prev = 0)
        *(Node**)pendingHead = *(Node**)((uint8_t*)this + 0x10);  // pendingHead->next = freeListHead
        Node* freeHead = *(Node**)((uint8_t*)this + 0x10);
        if (freeHead != nullptr) {
            *(Node**)((uint8_t*)freeHead + 4) = pendingHead;  // freeListHead->prev = pendingHead
        }
        *(int*)((uint8_t*)this + 0x1c) += 1;            // Increment free count
        *(Node**)((uint8_t*)this + 0x10) = pendingHead; // Update free list head
        pendingHead = nextPending;
    }

    // Clear all auxiliary counters and lists
    *(int*)((uint8_t*)this + 0x18) = 0;  // Some usage count
    *(int*)((uint8_t*)this + 0x14) = 0;  // Pending head
    *(int*)((uint8_t*)this + 0x2c) = 0;  // Unused field
    *(int*)((uint8_t*)this + 0x28) = 0;  // Unused field
    // Clear pool statistics at offsets 0x1030 through 0x1040
    *(int*)((uint8_t*)this + 0x1040) = 0;
    *(int*)((uint8_t*)this + 0x103c) = 0;
    *(int*)((uint8_t*)this + 0x1038) = 0;
    *(int*)((uint8_t*)this + 0x1034) = 0;
    *(int*)((uint8_t*)this + 0x1030) = 0;
}