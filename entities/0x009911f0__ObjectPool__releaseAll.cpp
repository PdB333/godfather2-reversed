// FUNC_NAME: ObjectPool::releaseAll
void __fastcall ObjectPool::releaseAll(void* this) {
    PoolNode* node;
    PoolNode* nextNode;
    char levelNameBuffer[32];

    // Get head of used list
    node = *(PoolNode**)((char*)this + 0x60);
    nextNode = nullptr;
    if (node != nullptr) {
        int nextPtr = node->next;          // offset +4
        *(int*)((char*)this + 0x60) = nextPtr;
        nextNode = node;
        if (nextPtr == 0) {
            *(int*)((char*)this + 0x64) = 0; // clear tail sentinel?
        } else {
            *(int*)(nextPtr + 8) = 0;       // remove prev link of next node
            node->next = 0;                // detach node
        }
    }

    // Process all nodes from the used list
    while (nextNode != nullptr) {
        // Acquire global lock? (DAT_0112a5a4 is a mutex)
        lockAcquire(&gPoolMutex);

        // Broadcast event? (LAB_00991080 is likely a function pointer or event enum)
        broadcastEvent(this, &poolEventReleaseAll, 1);

        // Build level name from node's level field (short at offset +0x44)
        sprintf(levelNameBuffer, "_level%u", (uint)*(short*)(nextNode + 0x44));

        // Remove node from hash table by name (likely a resource map)
        hashTableRemove(&gResourceHashTable, levelNameBuffer);

        // Release references (e.g., drop two reference counts)
        releaseReference();
        releaseReference();

        // Reset vtable to base destroyed vtable
        nextNode->vtable = &baseDestroyedVtable;

        // Unlink children? (offset +0x3C and +0x38 are child pointers)
        int child1 = *(int*)((char*)nextNode + 0x3C);
        if (child1 != 0) {
            *(int*)(child1 + 8) = 0;
            *(int*)((char*)nextNode + 0x3C) = 0;
        }
        int child2 = *(int*)((char*)nextNode + 0x38);
        if (child2 != 0) {
            *(int*)(child2 + 8) = 0;
            *(int*)((char*)nextNode + 0x38) = 0;
        }

        // Prepend node to free list
        nextNode->vtable = *(int*)((char*)this + 0x5C);
        *(int*)((char*)this + 0x38) -= 1; // decrement used count
        *(int*)((char*)this + 0x34) += 1; // increment free count
        *(int*)((char*)this + 0x5C) = (int)nextNode;

        // Get next node from used list
        node = *(PoolNode**)((char*)this + 0x60);
        nextNode = nullptr;
        if (node != nullptr) {
            int nextPtr = node->next;
            *(int*)((char*)this + 0x60) = nextPtr;
            nextNode = node;
            if (nextPtr == 0) {
                *(int*)((char*)this + 0x64) = 0;
            } else {
                *(int*)(nextPtr + 8) = 0;
                node->next = 0;
            }
        }
    }

    // Final cleanup
    *(int*)((char*)this + 0x84) = 0; // clear some state
    performCleanup1();                // FUN_005c0b00
    *(int*)((char*)this + 0x10) = 0;
    *(int*)((char*)this + 0x14) = 0;
    performCleanup2();                // FUN_005c08f0
}